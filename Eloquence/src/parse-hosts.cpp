#include "parse-hosts.hpp"
#include "utils.hpp"

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

void traverse_hosts(xml_node *host)
{
    if (host == nullptr)
    {
        return;
    }

    xml_node *node_hop = host->first_node("hop");

    if (node_hop)
    {
        ::traverse_hops(node_hop);
    }

    ::traverse_hosts(host->first_node("trace"));
    ::traverse_hosts(host->next_sibling("host"));
}

void get_hosts(xml_node *root)
{
    ::separator();
    std::cout << "** Network:\n";
    ::traverse_hosts(root->first_node("host"));
}
