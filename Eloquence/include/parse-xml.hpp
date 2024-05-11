#pragma once

#include "rapidxml.hpp"

typedef rapidxml::xml_node<> xml_node;
typedef rapidxml::xml_attribute<> xml_attr;

void get_stats(xml_node *node);
void get_hosts(xml_node *node);
