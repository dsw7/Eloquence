#include "parse-xml.hpp"

#include "rapidxml_utils.hpp"
#include <iostream>
#include <stdexcept>

bool ParseXMLReport::parse_xml_file(const std::string &path_xml_file)
{
    rapidxml::xml_document<> document;

    try
    {
        rapidxml::file<> xml_file(path_xml_file.c_str());
        document.parse<0>(xml_file.data());
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Failed to open '" << path_xml_file << "'\n"
                  << "It's possible the permissions on this file are too restrictive\n"
                  << "Raw message: '" << e.what() << "'\n";

        return false;
    }
    catch (const rapidxml::parse_error &e)
    {
        std::cerr << "Failed to parse '" << path_xml_file << "'\n" << e.what() << '\n';
        return false;
    }

    this->root = document.first_node("nmaprun");

    if (this->root == NULL)
    {
        std::cerr << "Not a valid Nmap XML report. Missing 'nmaprun' node!" << '\n';
        return false;
    }

    return true;
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
