#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "character.h"


void load_character(character & chr, const std::string & filename, bool do_warn_on_missing=true)
{
  rapidxml::file<> xmlFile(filename);
  rapidxml::xml_document<> doc;
  doc.parse<0>(xmlFile.data());
}
