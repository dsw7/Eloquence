#include "parse-xml.hpp"

#include <iostream>

void get_stats(rapidxml::xml_node<> *node)
{
    if (node == NULL)
    {
        return;
    }

    rapidxml::xml_node<> *hosts = node->first_node("hosts");

    rapidxml::xml_attribute<> *up = hosts->first_attribute("up");
    std::cout << "Number of machines up: " << up->value() << '\n';

    rapidxml::xml_attribute<> *down = hosts->first_attribute("down");
    std::cout << "Number of machines down: " << down->value() << '\n';

    rapidxml::xml_attribute<> *total = hosts->first_attribute("total");
    std::cout << "Number of machines scanned: " << total->value() << '\n';
}

void get_hosts(rapidxml::xml_node<> *node)
{
    if (node == NULL)
    {
        return;
    }

    std::cout << node->name() << '\n';
    ::get_hosts(node->next_sibling("host"));
}
