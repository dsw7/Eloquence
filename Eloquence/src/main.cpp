#include "parse-xml.hpp"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <filesystem>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: $ " << argv[0] << " /path/to/xml\n";
        return EXIT_FAILURE;
    }

    std::string path_xml = std::string(argv[1]);
    if (not std::filesystem::exists(path_xml))
    {
        std::cerr << "Could not find '" << path_xml << "'\n";
        return EXIT_FAILURE;
    }

    rapidxml::xml_document<> document;
    rapidxml::file<> xml_file(path_xml.c_str());

    try
    {
        document.parse<0>(xml_file.data());
    }
    catch (const rapidxml::parse_error &e)
    {
        std::cerr << "Failed to parse '" << path_xml << "'\n" << e.what() << '\n';
        return EXIT_FAILURE;
    }

    rapidxml::xml_node<> *root = document.first_node("nmaprun");

    if (root == NULL)
    {
        std::cerr << "Not a valid Nmap XML report. Missing 'nmaprun' node!" << '\n';
        return EXIT_FAILURE;
    }

    ParseXMLReport parser(root);
    parser.get_stats();

    return EXIT_SUCCESS;
}
