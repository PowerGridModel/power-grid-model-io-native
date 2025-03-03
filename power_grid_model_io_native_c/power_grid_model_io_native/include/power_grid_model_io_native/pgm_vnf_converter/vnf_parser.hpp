// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_IO_NATIVE_C_VNF_PARSER_HPP
#define POWER_GRID_MODEL_IO_NATIVE_C_VNF_PARSER_HPP

#include <power_grid_model_io_native/common/common.hpp>

#include <power_grid_model/auxiliary/input.hpp>
#include <power_grid_model/container.hpp>

#include <iostream>
#include <map>
#include <regex>

namespace power_grid_model_io_native {
using VisionGUID = std::string;

struct VnfNode {
    VisionGUID guid{"nan"};
    double u_nom{nan};
};

using VnfGrid = pgm::Container<VnfNode>;
template <typename Identifier> using IdentifierLookup = std::unordered_map<Identifier, ID>;
using VisionGUIDLookup = IdentifierLookup<VisionGUID>;

class PgmVnfParser {
  public:
    explicit(false) PgmVnfParser(std::string_view vnf_data);

    void parse_input();
    VisionGUIDLookup get_id_lookup() const;
    VnfGrid get_parsed_data() const;

  private:
    VisionGUIDLookup vision_guid_lookup_;
    std::string_view vnf_data_;
    VnfGrid vnf_parsed_data_;
    ID id_count_{0};

    std::string_view find_node_block() const;
    void parse_node_input();
};

inline PgmVnfParser::PgmVnfParser(std::string_view vnf_data) : vnf_data_(vnf_data) {}

inline void PgmVnfParser::parse_input() {
    // parse each component individually and finish constructing the container
    parse_node_input();
    this->vnf_parsed_data_.set_construction_complete();
}

inline std::string_view PgmVnfParser::find_node_block() const {
    // obtain the whole string block for nodes
    std::regex const nodes_regex{R"(\[NODE\]([\s\S]*?)\[\])"};
    std::match_results<std::string_view::const_iterator> nodes_match;

    std::regex_search(this->vnf_data_.begin(), this->vnf_data_.end(), nodes_match, nodes_regex);
    assert(nodes_match.size() > 1);
    auto const& nodes = nodes_match[1]; // the first group is the nodes data
    std::string_view const nodes_block{nodes.first, nodes.second};

    return nodes_block;
}

inline void PgmVnfParser::parse_node_input() {
    // extract guids and unoms from the string nodes block,
    // fill the vnf_parsed_data and id lookup
    using svmatch = std::match_results<std::string_view::const_iterator>;
    using svregex_iterator = std::regex_iterator<std::string_view::const_iterator>;

    std::string_view const nodes_block = find_node_block();

    std::regex const node_regex{R"#(#General GUID:'\{([^\}]*)\}'.*?Unom:([\d\.]+))#"};

    for (svregex_iterator it{nodes_block.begin(), nodes_block.end(), node_regex}, end; it != end; ++it) {
        svmatch const& match = *it;

        assert(match.size() > 2);
        std::string const guid = match[1].str();
        double const unom = std::stod(match[2].str());

        // Find the multiplier for unom
        this->vnf_parsed_data_.emplace<VnfNode>(id_count_, guid, unom);
        this->vision_guid_lookup_.try_emplace(guid, id_count_);

        this->id_count_++;
    }
}

inline VisionGUIDLookup PgmVnfParser::get_id_lookup() const { return this->vision_guid_lookup_; }

inline VnfGrid PgmVnfParser::get_parsed_data() const { return this->vnf_parsed_data_; }

} // namespace power_grid_model_io_native

#endif // POWER_GRID_MODEL_IO_NATIVE_C_VNF_PARSER_HPP
