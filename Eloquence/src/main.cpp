#include "parse-xml.hpp"

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
    std::cout << "Loading '" << path_xml << "'\n";

    if (not std::filesystem::exists(path_xml))
    {
        std::cerr << "Could not find '" << path_xml << "'\n";
        return EXIT_FAILURE;
    }

    ParseXMLReport parser;

    if (not parser.parse_xml_file(path_xml))
    {
        return EXIT_FAILURE;
    }

    parser.get_stats();

    return EXIT_SUCCESS;
}
