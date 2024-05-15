#include "parse-hosts.hpp"

#include <iostream>
#include <string>

void traverse_hops(xml_node *hop)
{
    static bool add_arrow = false;

    if (hop == nullptr)
    {
        add_arrow = false;
        std::cout << '\n';
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
    if (node == nullptr)
    {
        return;
    }

    xml_node *node_addr = node->first_node("address");

    if (node_addr)
    {
        xml_attr *addr = node_addr->first_attribute("addr");
        std::cout << "Target: " << addr->value() << '\n';
    }

    xml_node *node_hop = node->first_node("hop");

    if (node_hop)
    {
        ::traverse_hops(node_hop);
    }

    ::get_hosts(node->first_node("trace"));
    ::get_hosts(node->next_sibling("host"));
}
