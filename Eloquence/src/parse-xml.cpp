#include "parse-xml.hpp"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <iostream>
#include <stdexcept>

bool parse_xml(const std::string &path_xml)
{
    rapidxml::xml_document<> doc;

    try
    {
        rapidxml::file<> xmlFile(path_xml.c_str());
        doc.parse<0>(xmlFile.data());
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Failed to open '" << path_xml << "'\n"
                  << "It's possible the permissions on this file are too restrictive\n"
                  << "Raw message: '" << e.what() << "'\n";

        return false;
    }

    rapidxml::xml_node<> *root = doc.first_node();

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
