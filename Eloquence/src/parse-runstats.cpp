#include "parse-runstats.hpp"

#include <iostream>
#include <string>

void get_runstats(xml_node *node)
{
    if (node == NULL)
    {
        return;
    }

    xml_node *hosts = node->first_node("hosts");

    xml_attr *up = hosts->first_attribute("up");
    std::cout << "Number of machines up: " << up->value() << '\n';

    xml_attr *down = hosts->first_attribute("down");
    std::cout << "Number of machines down: " << down->value() << '\n';

    xml_attr *total = hosts->first_attribute("total");
    std::cout << "Number of machines scanned: " << total->value() << '\n';
}
