#include "parse-xml.hpp"

#include <iostream>
#include <string>

void get_stats(xml_node *node)
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

void traverse_hops(xml_node *hop)
{
    static bool add_arrow = false;

    if (hop == NULL)
    {
        add_arrow = false;
        return;
    }

    xml_attr *ipaddr = hop->first_attribute("ipaddr");

    if (add_arrow)
    {
        std::cout << " -> ";
    }
    else
    {
        add_arrow = true;
    }

    std::cout << ipaddr->value();

    ::traverse_hops(hop->next_sibling("hop"));
}

void get_hosts(xml_node *node)
{
    if (node == NULL)
    {
        return;
    }

    xml_node *node_addr = node->first_node("address");

    if (node_addr)
    {
        xml_attr *addr = node_addr->first_attribute("addr");
        std::cout << "\nTarget: " << addr->value() << '\n';
    }

    xml_node *node_hop = node->first_node("hop");

    if (node_hop)
    {
        ::traverse_hops(node_hop);
    }

    ::get_hosts(node->first_node("trace"));
    ::get_hosts(node->next_sibling("host"));
}
