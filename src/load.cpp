#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "character.h"

using namespace rapidxml;
using namespace std;

void load_character(character & chr, const std::string & filename, bool do_warn_on_missing=true)
{
  file<> xmlFile(filename.c_str());
  xml_document<> doc;
  doc.parse<0>(xmlFile.data());
  xml_node<> *node = doc.first_node("character")->first_node("attributes")->first_node("attribute");
  for(;node;node = node->next_sibling())
  {
    unsigned val = atoi(node->first_node("totalvalue")->value());
    if(strcmp(node->first_node("name")->value(),"BOD")==0) chr.body = val;
    if(strcmp(node->first_node("name")->value(),"AGI")==0) chr.agility = val;
    if(strcmp(node->first_node("name")->value(),"REA")==0) chr.reaction = val;
    if(strcmp(node->first_node("name")->value(),"STR")==0) chr.strength = val;
    if(strcmp(node->first_node("name")->value(),"CHA")==0) chr.charisma = val;
    if(strcmp(node->first_node("name")->value(),"INT")==0) chr.intuiton = val;
    if(strcmp(node->first_node("name")->value(),"LOG")==0) chr.logic = val;
    if(strcmp(node->first_node("name")->value(),"WIL")==0) chr.willpower = val;
    if(strcmp(node->first_node("name")->value(),"EDG")==0) chr.edge = val;
    if(strcmp(node->first_node("name")->value(),"MAG")==0) chr.magic = val;
    if(strcmp(node->first_node("name")->value(),"MAGAdept")==0) chr.magic = val;
    if(strcmp(node->first_node("name")->value(),"RES")==0) chr.resonance = val;
    if(strcmp(node->first_node("name")->value(),"ESS")==0) chr.essence = val;
    if(strcmp(node->first_node("name")->value(),"DEP")==0) chr.depth = val;
  }
}
