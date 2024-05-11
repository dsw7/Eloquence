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
