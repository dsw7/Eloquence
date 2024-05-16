#include "parse-runstats.hpp"
#include "utils.hpp"

#include <iomanip>
#include <iostream>
#include <string>

void parse_hosts(xml_node *hosts)
{
    if (hosts == nullptr)
    {
        return;
    }

    xml_attr *total = hosts->first_attribute("total");
    std::cout << std::setw(30) << std::left << "Number of machines scanned:" << total->value() << '\n';

    xml_attr *down = hosts->first_attribute("down");
    std::cout << std::setw(30) << std::left << "Number of machines down:" << down->value() << '\n';

    xml_attr *up = hosts->first_attribute("up");
    std::cout << std::setw(30) << std::left << "Number of machines up:" << up->value() << '\n';
}

void parse_finished(xml_node *finished)
{
    if (finished == nullptr)
    {
        return;
    }

    xml_attr *timestr = finished->first_attribute("timestr");
    std::cout << std::setw(30) << std::left << "Report collected at:" << timestr->value() << '\n';

    xml_attr *elapsed = finished->first_attribute("elapsed");
    std::cout << std::setw(30) << std::left << "Elapsed time (s):" << elapsed->value() << '\n';
}

void parse_runstats(xml_node *runstats)
{
    if (runstats == nullptr)
    {
        return;
    }

    ::parse_hosts(runstats->first_node("hosts"));
    ::parse_finished(runstats->first_node("finished"));
}

void get_runstats(xml_node *root)
{
    ::separator();
    std::cout << "** Statistics:\n";
    ::parse_runstats(root->first_node("runstats"));
}
