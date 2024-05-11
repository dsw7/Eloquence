#pragma once

#include "rapidxml.hpp"
#include <string>

class ParseXMLReport
{
public:
    ~ParseXMLReport();
    bool parse_xml_file(const std::string &path_xml_file);

private:
    rapidxml::xml_document<> document;
};
