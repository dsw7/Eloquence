#include "parse-xml.hpp"

#include <iostream>

ParseXMLReport::ParseXMLReport(rapidxml::xml_node<> *root)
{
    this->root = root;
}

bool ParseXMLReport::get_stats()
{
    rapidxml::xml_node<> *runstats = this->root->first_node("runstats");

    if (runstats == NULL)
    {
        std::cerr << "Missing 'runstats' node!" << '\n';
        return false;
    }

    rapidxml::xml_node<> *hosts = runstats->first_node("hosts");

    rapidxml::xml_attribute<> *up = hosts->first_attribute("up");
    std::cout << "Number of machines up: " << up->value() << '\n';

    rapidxml::xml_attribute<> *down = hosts->first_attribute("down");
    std::cout << "Number of machines down: " << down->value() << '\n';

    rapidxml::xml_attribute<> *total = hosts->first_attribute("total");
    std::cout << "Number of machines scanned: " << total->value() << '\n';

    return true;
}

/*
{
    rapidxml::xml_node<> *root = this->document.first_node();

    for (rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling())
    {
        if (node->name() != std::string("host"))
        {
            continue;
        }

        rapidxml::xml_attribute<> *address = nullptr;

        for (rapidxml::xml_node<> *host = node->first_node(); host; host = host->next_sibling())
        {
            if (host->name() != std::string("address"))
            {
                continue;
            }

            address = host->first_attribute("addr");
            std::cout << node->name() << '\n';
            std::cout << address->value() << "\n\n";
            break;
        }
    }

    return true;
}
*/
