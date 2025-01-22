// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_IO_NATIVE_C_CONVERTER_PARSER_HPP
#define POWER_GRID_MODEL_IO_NATIVE_C_CONVERTER_PARSER_HPP

#include <power_grid_model_io_native/common/common.hpp>

#include <power_grid_model/auxiliary/input.hpp>
#include <power_grid_model/container.hpp>

#include <map>
#include <iostream>
#include <regex>

namespace power_grid_model_io_native {
using ID = pgm::ID;

class PgmVnfParser{
  public:
    PgmVnfParser(std::string_view const vnf_data);
    
    using InputData = pgm::Container<pgm::NodeInput>;
    InputData converted_data;

    template <typename Identifier>
    using IdentifierLookup = std::map<Identifier, ID>;

    using VisionGUID = std::string;
    using VisionGUIDLookup = IdentifierLookup<VisionGUID>;
    VisionGUIDLookup vision_guid_lookup;

    void parse_input();

  private:
    std::string_view vnf_data_;
    ID id_count_; 

    std::string_view find_node_block();
    void parse_node_input();
};

inline PgmVnfParser::PgmVnfParser(
    std::string_view const vnf_data) : vnf_data_(vnf_data), id_count_(0) {}


inline void PgmVnfParser::parse_input() {
    parse_node_input();
}

inline std::string_view PgmVnfParser::find_node_block(){
    std::regex const nodes_regex{R"(\[NODE\]([\s\S]*?)\[\])"};
    std::match_results<std::string_view::const_iterator> nodes_match;

    std::regex_search(this->vnf_data_.begin(), this->vnf_data_.end(), nodes_match, nodes_regex);
    auto const& nodes = nodes_match[1]; // the first group is the nodes data
    std::string_view const nodes_block{nodes.first, nodes.second};

    return nodes_block;
}

inline void PgmVnfParser::parse_node_input() {
    using svmatch = std::match_results<std::string_view::const_iterator>;
    using svregex_iterator = std::regex_iterator<std::string_view::const_iterator>;

    std::string_view const nodes_block = find_node_block();

    std::regex const node_regex{
        R"#(#General GUID:'\{([^\}]*)\}'\s+CreationTime:([\d\.]+)(?:\s+Name:'([^']*)')?\s+Unom:([\d\.]+))#"};

    svregex_iterator it{nodes_block.begin(), nodes_block.end(), node_regex};
    svregex_iterator const end;

    while (it != end) {
        svmatch const match = *it;

        std::cout << "GUID: " << match[1].str() << "\n";
        std::cout << "CreationTime: " << match[2].str() << "\n";
        std::cout << "Name: " << match[3].str() << "\n";
        std::cout << "Unom: " << match[4].str() << "\n\n";
        double unom = std::stod(match[4].str());
        std::string guid = match[1].str();

        //Find the multiplier for unom
        this->converted_data.emplace<pgm::NodeInput>(id_count_, id_count_, unom);
        this->vision_guid_lookup.emplace(guid, id_count_);

        this->id_count_++;
        ++it;
    }
}

} // namespace power_grid_model_io_native

#endif // POWER_GRID_MODEL_IO_NATIVE_C_CONVERTER_PARSER_HPP
