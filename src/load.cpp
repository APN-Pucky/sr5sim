#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "character.h"
#include "debug.h"
#include "utils.h"

using namespace rapidxml;
using namespace std;

void load_character(Character& chr,const std::string & filename, bool do_warn_on_missing=true)
{
 
  file<> xmlFile(filename.c_str());
  xml_document<> doc;
  doc.parse<0>(xmlFile.data());
  xml_node<> * top = doc.first_node("character");

  chr.alias = string(top->first_node("alias")->value());
  chr.name = string(top->first_node("name")->value());
  
  _DEBUG_MSG(3,"Loading %s aka %s\n", chr.name.c_str(),chr.alias.c_str());
  
  xml_node<> * node = top->first_node("attributes")->first_node("attribute");
  for(;node;node = node->next_sibling())
  {
    int val = atoi(node->first_node("totalvalue")->value());
    string name = string(node->first_node("name")->value());
    int index = position(name,stats_abbrev,num_stat); 
    if(index != num_stat)
	chr.stats[index] = val;
    _DEBUG_MSG(4,"-- Loading attribute %s(%i)=%i,%i\n",name.c_str(),index,val,chr.stats[index]);
    /*if(strcmp(node->first_node("name")->value(),"BOD")==0) chr.stats[Stat::body] = val;
    else if(strcmp(node->first_node("name")->value(),"AGI")==0) chr.stats[Stat::agility] = val;
    else if(strcmp(node->first_node("name")->value(),"REA")==0) chr.stats[Stat::reaction] = val;
    else if(strcmp(node->first_node("name")->value(),"STR")==0) chr.stats[Stat::strength] = val;
    else if(strcmp(node->first_node("name")->value(),"CHA")==0) chr.stats[Stat::charisma] = val;
    else if(strcmp(node->first_node("name")->value(),"INT")==0) chr.stats[Stat::intuition] = val;
    else if(strcmp(node->first_node("name")->value(),"LOG")==0) chr.stats[Stat::logic] = val;
    else if(strcmp(node->first_node("name")->value(),"WIL")==0) chr.stats[Stat::willpower] = val;
    else if(strcmp(node->first_node("name")->value(),"EDG")==0) chr.stats[Stat::edge] = val;
    else if(strcmp(node->first_node("name")->value(),"MAG")==0) chr.stats[Stat::magic] = val;
    else if(strcmp(node->first_node("name")->value(),"MAGAdept")==0) chr.stats[Stat::magic] = val;
    else if(strcmp(node->first_node("name")->value(),"RES")==0) chr.stats[Stat::resonance] = val;
    else if(strcmp(node->first_node("name")->value(),"ESS")==0) chr.stats[Stat::essence] = val;
    else if(strcmp(node->first_node("name")->value(),"DEP")==0) chr.stats[Stat::depth] = val;
    else {};
    */
  }
  
  
  node = top->first_node("newskills")->first_node("skills")->first_node("skill");
  for(;node;node = node->next_sibling())
  {
    _DEBUG_MSG(4,"-- Loading skills\n");
    int base = atoi(node->first_node("base")->value());
    int karma = atoi(node->first_node("karma")->value());
    if(node->first_node("name")) {
    	string name = string(node->first_node("name")->value());
    	int index = position(name,stats_name,num_stat); 
    	if(index != num_stat)
		chr.stats[index] = base+karma;
    }

    //if(strcmp(node->first_node("suid")->value(),"4fcd40cb-4b02-4b7e-afcb-f44d46cd5706")==0) chr.stats[Stat::unarmed_combat] = karma + base;  
	
  }
  node = top->first_node("newskills")->first_node("groups")->first_node("group");
  for(;node;node = node->next_sibling())
  {
    _DEBUG_MSG(4,"-- Loading groups\n");
    int base = atoi(node->first_node("base")->value());
    int karma = atoi(node->first_node("karma")->value());
    string name = string(node->first_node("name")->value());
    int index = position(name,statgroups_name,num_statgroup); 
    if(index != num_statgroup)
	chr.stats[index] = base+karma;

    /*if(strcmp(node->first_node("name")->value(),"Acting")==0) chr.statgroups[acting] += karma+base;
    if(strcmp(node->first_node("name")->value(),"Outdoors")==0) chr.statgroups[outdoors] += karma+base;
    if(strcmp(node->first_node("name")->value(),"Close Combat")==0) chr.statgroups[Stat::close_combat] += karma+base;
    if(strcmp(node->first_node("name")->value(),"Engineering")==0) chr.statgroups[engineering] += karma+base;
    if(strcmp(node->first_node("name")->value(),"Stealth")==0) chr.statgroups[stealth] += karma+base;
    if(strcmp(node->first_node("name")->value(),"Firearms")==0) chr.statgroups[firearms] += karma+base;
    if(strcmp(node->first_node("name")->value(),"Electronics")==0) chr.statgroups[electronics] += karma+base;
    if(strcmp(node->first_node("name")->value(),"Stealth")==0) chr.statgroups[stealth] += karma+base;
    */
  }

  node = top->first_node("improvements")->first_node("improvement");
  for(;node;node = node->next_sibling())
  {
    auto a = node->first_node("improvedname");
    if(a && strcmp(a->value(),"Unarmed Combat")==0) chr.stats[Stat::unarmed_combat] += 2;
  }
  node = top->first_node("cyberwares")->first_node("cyberware");
  for(;node;node = node->next_sibling())
  {
    if(strcmp(node->first_node("name")->value(),"Reflex Recorder")==0)
    {
    	auto a = node->first_node("extra");
	if(a && strcmp(a->value(),"Close Combat")==0) chr.stats[Stat::unarmed_combat] +=1;

    }
  }


  _DEBUG_MSG(3,"%s has %i UCC", chr.name.c_str(),chr.stats[unarmed_combat]);

  int high_base = 0;
  int bonus = 0;
  string plus = "+";
  node = top->first_node("armors")->first_node("armor");
  for(;node;node = node->next_sibling())
  {
    auto name = node->first_node("name")->value();
    auto val = string(node->first_node("armor")->value());
    if(strcmp(name,"Generic CCOB")==0) val.insert(0,"+"); //Cyber works as Bonus
    if(val.rfind(plus,0)==0){
    	bonus += stoi(val.substr(1,val.length()-1));
    }
    else
    {
		if(stoi(val)>high_base)
		{
			high_base = stoi(val);
		}
    }
  }
  chr.stats[Stat::armor] = high_base+bonus;
  
  _DEBUG_MSG(3," and %i ARM\n", chr.stats[armor]);
  _DEBUG_MSG(4, "Loaded:\n %s\n", chr.overview().c_str());
}
