#include "parse-runstats.hpp"

#include <iomanip>
#include <iostream>
#include <string>

void parse_hosts(xml_node *node_hosts)
{
    if (node_hosts == NULL)
    {
        return;
    }

    xml_attr *total = node_hosts->first_attribute("total");
    std::cout << std::setw(30) << std::left << "Number of machines scanned:" << total->value() << '\n';

    xml_attr *down = node_hosts->first_attribute("down");
    std::cout << std::setw(30) << std::left << "Number of machines down:" << down->value() << '\n';

    xml_attr *up = node_hosts->first_attribute("up");
    std::cout << std::setw(30) << std::left << "Number of machines up:" << up->value() << '\n';
}

void parse_finished(xml_node *node_finished)
{
    if (node_finished == NULL)
    {
        return;
    }

    xml_attr *timestr = node_finished->first_attribute("timestr");
    std::cout << std::setw(30) << std::left << "Report collected at:" << timestr->value() << '\n';

    xml_attr *elapsed = node_finished->first_attribute("elapsed");
    std::cout << std::setw(30) << std::left << "Elapsed time (s):" << elapsed->value() << '\n';
}

void get_runstats(xml_node *node)
{
    if (node == NULL)
    {
        return;
    }

    ::parse_hosts(node->first_node("hosts"));
    ::parse_finished(node->first_node("finished"));
}
