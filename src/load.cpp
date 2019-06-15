#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "rapidxml.hpp"
#include "character.h"
using namespace rapidxml;

bool parse_file(const std::string & filename, std::vector<char>& buffer, xml_document<>& doc, bool do_warn_on_missing=true)
{
    std::ifstream cards_stream(filename, std::ios::binary);
    if (!cards_stream.good())
    {
        if (do_warn_on_missing)
        {
            std::cerr << "WARNING: The file '" << filename << "' does not exist. Proceeding without reading from this file.\n";
        }
        buffer.resize(1);
        buffer[0] = 0;
        doc.parse<0>(&buffer[0]);
        return false;
    }
    // Get the size of the file
    cards_stream.seekg(0,std::ios::end);
    std::streampos length = cards_stream.tellg();
    cards_stream.seekg(0,std::ios::beg);
    buffer.resize(length + std::streampos(1));
    cards_stream.read(&buffer[0],length);
    // zero-terminate
    buffer[length] = '\0';
    try
    {
        doc.parse<0>(&buffer[0]);
        return true;
    }
    catch(rapidxml::parse_error& e)
    {
        std::cerr << "Parse error exception.\n";
        std::cout << e.what();
        throw(e);
    }
}

void load_character(character & chr, const std::string & filename, bool do_warn_on_missing=true)
{

}
