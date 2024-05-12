#include "parse-hosts.hpp"
#include "parse-runstats.hpp"
#include "utils.hpp"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <cstring>
#include <filesystem>
#include <iostream>

void help_messages()
{
    std::string name = std::string(PROJECT_NAME);
    std::string doc = "\033[1mNAME:\033[0m\n"
                      "  \033[4m" +
                      name +
                      "\033[0m\n\n"
                      "\033[1mDESCRIPTION:\033[0m\n"
                      "  A command line program for parsing Nmap XML files. To be used as\n"
                      "  part of a larger workflow. See \033[4mhttps://github.com/dsw7/GPTifier\033[0m\n"
                      "  for more information.\n\n"
                      "\033[1mSYNOPSIS:\033[0m\n"
                      "  \033[4melo\033[0m [-h | --help] </path/to/xml>\n\n"
                      "\033[1mOPTIONS:\033[0m\n"
                      "  \033[2m-h, --help\033[0m\n"
                      "    Print help information and exit.\n\n";
    std::cout << doc;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        ::help_messages();
        return EXIT_FAILURE;
    }

    if (::strcmp(argv[1], "-h") == 0 or ::strcmp(argv[1], "--help") == 0)
    {
        ::help_messages();
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

    xml_node *root = document.first_node("nmaprun");

    if (root == NULL)
    {
        std::cerr << "Not a valid Nmap XML report. Missing 'nmaprun' node!" << '\n';
        return EXIT_FAILURE;
    }

    ::separator();
    ::get_runstats(root->first_node("runstats"));
    ::separator();
    ::get_hosts(root->first_node("host"));
    ::separator();

    return EXIT_SUCCESS;
}
