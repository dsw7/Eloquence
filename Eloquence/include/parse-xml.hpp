#pragma once

#include "rapidxml.hpp"
#include <string>

class ParseXMLReport
{
public:
    bool parse_xml_file(const std::string &path_xml_file);
    bool get_stats();

private:
    rapidxml::xml_node<> *root = nullptr;
};
