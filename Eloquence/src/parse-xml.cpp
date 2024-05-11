#include "parse-xml.hpp"

#include "rapidxml_utils.hpp"
#include <iostream>
#include <stdexcept>

ParseXMLReport::~ParseXMLReport()
{
    this->document.clear();
}

bool ParseXMLReport::parse_xml_file(const std::string &path_xml_file)
{
    try
    {
        rapidxml::file<> xml_file(path_xml_file.c_str());
        this->document.parse<0>(xml_file.data());
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

    return true;
}

bool ParseXMLReport::get_stats()
{
    rapidxml::xml_node<> *root = this->document.first_node("nmaprun");
    if (root == NULL)
    {
        std::cerr << "Not a valid Nmap XML report. Missing 'nmaprun' node!" << '\n';
        return false;
    }

    rapidxml::xml_node<> *runstats = root->first_node("runstats");
    if (root == NULL)
    {
        std::cerr << "Missing 'runstats' node!" << '\n';
        return false;
    }

    rapidxml::xml_node<> *hosts = runstats->first_node("hosts");
    rapidxml::xml_attribute<> *up = hosts->first_attribute("up");
    std::cout << up->value();

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
