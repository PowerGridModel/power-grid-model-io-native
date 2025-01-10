// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#include <power_grid_model_io_native_c/basics.h>
#include <power_grid_model_io_native_c/handle.h>
#include <power_grid_model_io_native_c/pgm_vnf_converter.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <span>
#include <string>
#include <vector>

namespace {
using Idx = PGM_IO_Idx;

enum class ErrorCode : int {
    no_error = 0,
    regular_error = 1,
    invalid_arguments = 2,
    io_error = 3,
    unknown_error = 127,
};

// custom deleter
template <auto func> struct DeleterFunctor {
    template <typename T> void operator()(T* arg) const { func(arg); }
};

// memory safety: cleanup is automatically handled by unique_ptr, even if exceptions are thrown
using VNFConverter = std::unique_ptr<PGM_IO_PgmVnfConverter, DeleterFunctor<&PGM_IO_destroy_pgm_vnf_converter>>;
using Handle = std::unique_ptr<PGM_IO_Handle, DeleterFunctor<&PGM_IO_destroy_handle>>;

class PGMIOException : public std::exception {
  public:
    PGMIOException(ErrorCode error_code, std::string msg) : error_code_{error_code}, msg_{std::move(msg)} {}
    char const* what() const noexcept final { return msg_.c_str(); }
    ErrorCode error_code() const noexcept { return error_code_; }

  private:
    ErrorCode error_code_;
    std::string msg_;
};

void check_error(Handle const& handle) {
    if (auto const error_code = PGM_IO_error_code(handle.get()); error_code != PGM_IO_no_error) {
        std::string error_message = PGM_IO_error_message(handle.get());
        PGM_IO_clear_error(handle.get());
        throw PGMIOException{ErrorCode::regular_error, std::move(error_message)};
    }
}

auto read_file(std::filesystem::path const& path) {
    std::ifstream const f{path};
    if (!f) {
        using namespace std::string_literals;
        throw PGMIOException{ErrorCode::io_error, "Could not open file for reading: "s + path.string()};
    }

    std::ostringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

auto write_file(std::filesystem::path const& path, std::string_view contents) {
    std::ofstream f{path};
    if (!f) {
        using namespace std::string_literals;
        throw PGMIOException{ErrorCode::io_error, "Could not open file for writing: "s + path.string()};
    }

    f << contents;
    std::cout << "Wrote file: " << path << "\n";
}

void run(std::filesystem::path const& vnf_file, std::filesystem::path const& pgm_json_file) {
    constexpr auto experimental_feature_flag = PGM_IO_experimental_features_enabled;

    auto const input_file_contents = read_file(vnf_file);

    Handle handle{PGM_IO_create_handle()};
    check_error(handle);

    VNFConverter converter{
        PGM_IO_create_pgm_vnf_converter(handle.get(), input_file_contents.c_str(), experimental_feature_flag)};
    check_error(handle);

    auto const* const json_result = PGM_IO_pgm_vnf_converter_get_input_data(handle.get(), converter.get());
    check_error(handle);
    if (json_result == nullptr) {
        throw PGMIOException{ErrorCode::regular_error, "Conversion failed for an unknown reason"};
    }

    write_file(pgm_json_file, json_result);

    // Cleanup of converter and handle is automatically handled by the wrapper types, even if exceptions are thrown.
    // No need to call PGM_IO_destroy_pgm_vnf_converter(converter.get()) or PGM_IO_destroy_handle(handle.get()).
    // NOTE: If you do not use the wrapper types, you must always call the destroy functions manually.
}

struct Arguments {
    std::filesystem::path vnf_file;
    std::filesystem::path pgm_json_file;
};

Arguments parse_arguments(std::span<char const* const> const& args) {
    using namespace std::string_literals;

    auto program = args.empty() ? "<program>"s : std::filesystem::path{args[0]}.filename().string();
    auto const help_str = "Usage: "s + program + " [-h/--help] <vnf_file> <pgm_json_file>"s;
    if (std::ranges::find_if(args, [](auto const& arg) { return arg == "-h"s || arg == "--help"s; }) != args.end()) {
        throw PGMIOException{ErrorCode::no_error, help_str}; // early exit but not an error
    }
    if (args.size() != 3) {
        throw PGMIOException{ErrorCode::invalid_arguments, help_str};
    }

    return Arguments{args[1], args[2]};
}
Arguments parse_arguments(int argc, char const* const argv[]) {
    return parse_arguments({argv, static_cast<std::size_t>(argc)});
}

// handle errors and exceptions using Lippincott pattern
ErrorCode handle_errors() {
    try {
        std::rethrow_exception(std::current_exception());
    } catch (PGMIOException const& e) {
        if (e.error_code() == ErrorCode::no_error) {
            std::cout << e.what() << "\n";
        } else {
            std::cerr << e.what() << "\n";
        }
        return e.error_code();
    } catch (std::exception const& e) {
        std::cerr << "An unknown error occurred:\n" << e.what() << "\n";
        return ErrorCode::unknown_error;
    }
    return ErrorCode::unknown_error;
}

} // namespace

int main(int argc, char const* const argv[]) noexcept {
    try {
        auto const arguments = parse_arguments(argc, argv);

        run(arguments.vnf_file, arguments.pgm_json_file);

        std::cout << "Conversion successful\n";
        return static_cast<int>(ErrorCode::no_error);
    } catch (...) {
        return static_cast<int>(handle_errors());
    }
}
