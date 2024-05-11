#pragma once

#include "rapidxml.hpp"

class ParseXMLReport
{
public:
    ParseXMLReport(rapidxml::xml_node<> *root);
    void get_stats();
    void get_hosts();

private:
    rapidxml::xml_node<> *root = nullptr;
};
