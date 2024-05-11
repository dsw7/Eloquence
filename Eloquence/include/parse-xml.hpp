#pragma once

#include "rapidxml.hpp"

class ParseXMLReport
{
public:
    ParseXMLReport(rapidxml::xml_node<> *root);
    bool get_stats();

private:
    rapidxml::xml_node<> *root = nullptr;
};
