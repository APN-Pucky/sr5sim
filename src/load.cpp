#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "character.h"

using namespace rapidxml;
using namespace std;

const Character load_character(const std::string & filename, bool do_warn_on_missing=true)
{
  Character chr;
  file<> xmlFile(filename.c_str());
  xml_document<> doc;
  doc.parse<0>(xmlFile.data());
  xml_node<> *node = doc.first_node("character");

  chr.alias = string(node->first_node("alias")->value());
  chr.name = string(node->first_node("name")->value());

  node = node->first_node("attributes")->first_node("attribute");
  for(;node;node = node->next_sibling())
  {
    unsigned val = atoi(node->first_node("totalvalue")->value());
    if(strcmp(node->first_node("name")->value(),"BOD")==0) chr.stats[Stat::body] = val;
    if(strcmp(node->first_node("name")->value(),"AGI")==0) chr.stats[Stat::agility] = val;
    if(strcmp(node->first_node("name")->value(),"REA")==0) chr.stats[Stat::reaction] = val;
    if(strcmp(node->first_node("name")->value(),"STR")==0) chr.stats[Stat::strength] = val;
    if(strcmp(node->first_node("name")->value(),"CHA")==0) chr.stats[Stat::charisma] = val;
    if(strcmp(node->first_node("name")->value(),"INT")==0) chr.stats[Stat::intuition] = val;
    if(strcmp(node->first_node("name")->value(),"LOG")==0) chr.stats[Stat::logic] = val;
    if(strcmp(node->first_node("name")->value(),"WIL")==0) chr.stats[Stat::willpower] = val;
    if(strcmp(node->first_node("name")->value(),"EDG")==0) chr.stats[Stat::edge] = val;
    if(strcmp(node->first_node("name")->value(),"MAG")==0) chr.stats[Stat::magic] = val;
    if(strcmp(node->first_node("name")->value(),"MAGAdept")==0) chr.stats[Stat::magic] = val;
    if(strcmp(node->first_node("name")->value(),"RES")==0) chr.stats[Stat::resonance] = val;
    if(strcmp(node->first_node("name")->value(),"ESS")==0) chr.stats[Stat::essence] = val;
    if(strcmp(node->first_node("name")->value(),"DEP")==0) chr.stats[Stat::depth] = val;
  }
  return chr;
}
