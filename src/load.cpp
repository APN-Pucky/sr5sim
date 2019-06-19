#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "debug.h"
#include "utils.h"
#include "character.h"
#include "weapon.h"

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
    int index = position3(name,stats_name,num_stat);
    if(index != num_stat)
	chr.stats[index] = val;
    //MAGAdept fix?
    _DEBUG_MSG(5,"-- Loading attribute %s(%i)=%i,%i\n",name.c_str(),index,val,chr.stats[index]);
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
    //_DEBUG_MSG(4,"-- Loading skills\n");
    int base = atoi(node->first_node("base")->value());
    int karma = atoi(node->first_node("karma")->value());
    if(node->first_node("name")) {
    	string name = string(node->first_node("name")->value());
    	int index = position(name,stats_name,num_stat); 
    	if(index != num_stat)
		chr.stats[index] = base+karma;

  	auto t = node->first_node("specs");
	if(t)t=t->first_node("spec");
  	for(;t;t = t->next_sibling())
	{
    		name = string(t->first_node("name")->value());
    		int index = position(name,stats_name,num_stat); 
    		if(index != num_stat) chr.stats[index]=2;
	}
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
    int index = position(name,stats_name,num_stat); 
    if(index != num_stat)
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

  
  node = top->first_node("cyberwares")->first_node("cyberware");
  for(;node;node = node->next_sibling())
  {
    if(strcmp(node->first_node("name")->value(),"Pain Editor")==0)
    {
    	if(false) {
		chr.pain_editor = true;
		chr.stats[intuition]-=1;
		chr.stats[willpower]+=1;
	}
    }
    auto c = node->first_node("children");
    auto cy = c->first_node("cyberware");
    int agi=0,str=0;
    for(;cy;cy=cy->next_sibling())
    {
	string nn = string(cy->first_node("name")->value());	
	if(nn.find("Strength")!= string::npos) {
		str+= atoi(cy->first_node("rating")->value());
	}
	if(nn.find("Agility")!= string::npos) {
		agi+= atoi(cy->first_node("rating")->value());
	}
    }
    if(agi> chr.stats[agility])chr.stats[agility] =agi;
    if(str> chr.stats[strength])chr.stats[strength]= str;
  }


  _DEBUG_MSG(3,"%s has %i UCC\n", chr.name.c_str(),chr.stats[unarmed_combat]);

  int high_base = 0;
  int bonus = 0;
  string plus = "+";
  node = top->first_node("armors")->first_node("armor");
  for(;node;node = node->next_sibling())
  {
    //auto name = node->first_node("name")->value();
    auto val = string(node->first_node("armor")->value());
    //if(strcmp(name,"Generic CCOB")==0) val.insert(0,"+"); //Cyber works as Bonus
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

  
  _DEBUG_MSG(3,"Loading Weapons\n");
  node = top->first_node("weapons")->first_node("weapon");
  for(;node;node=node->next_sibling())
  {
  	
  	Weapon w;
 	auto wname = string(node->first_node("name")->value());
	w.name = wname;
  	_DEBUG_MSG(3,"-- %s\n",w.name.c_str());
	auto us = node->first_node("spec")->value();
	int index = 0;
	if(strcmp(us,"")!=0){
		index = position(string(us),stats_name,num_stat); 
	}
	else{
		auto us3 = node->first_node("useskill")->value();
		if(strcmp(us3,"")!=0){
			index = position(string(us3),stats_name,num_stat); 
		}
		else {
			string us2 = string( node ->first_node("category")->value());
			if(us2.compare("Unarmed")==0)us2="Unarmed Combat";
			index = position(us2,stats_name,num_stat); 
		}
	}
    	if(index != num_stat)
		w.useskill=static_cast<Stat>(index);
	auto c = node->first_node("accuracy")->value();
	if(c[0]=='P'){
		w.accuracy_limit = physical;
	}
	else
	{
		w.accuracy = atoi(node->first_node("accuracy")->value());
	}
	w.rc = atoi(node->first_node("rc")->value());
	w.ap = atoi(node->first_node("ap")->value());
	w.reach = atoi(node->first_node("reach")->value());

	string dmg = string(node->first_node("damage")->value());
	string odmg = dmg;
	_DEBUG_MSG(5,"dmg_data=%s\n",dmg.c_str());
	w.damage_type = (dmg.back()=='P')?phys:(dmg.back()=='S')?stun:custom;
		dmg.pop_back();
		if(dmg.front()=='(') {
			cout << dmg.substr(1,3) << endl;
			int index = position3(dmg.substr(1,3),stats_name,num_stat);
			w.damage_skill = static_cast<Stat>(index);
			dmg = dmg.substr(4,dmg.size()-5);
			cout << dmg << endl;
		}
		if( dmg.size()>0 && dmg.front()!=')'){
			try {
			if(dmg.compare("Grenad")==0){
				w.damage = 0;
				w.launcher = true;
			}else{
			w.damage = stoi(dmg);
			}
			} catch (...) {
				cout << "[WARN] could not parse: " <<  odmg << endl;
				w.damage = 0;
				
			}
		}
	chr.weapons.emplace_back(w); 
	_DEBUG_MSG(5, "dmg=%i,type=%i,skill=%s\n", w.damage,w.damage_type, stats_name[w.damage_skill].c_str());
  }

  node = top->first_node("improvements")->first_node("improvement");
  for(;node;node = node->next_sibling())
  {
    auto a = node->first_node("improvedname")->value();
    auto b = node->first_node("improvementttype")->value();
    string name; 
    if(strcmp(a,"")==0)
    {
    	name = string(b);
    }
    else{
    	name = string(a);
    }
    if(name.compare("UnarmedDV")==0){
    	chr.weapon("Unarmed Attack").damage += 2;
	chr.weapon("Unarmed Attack").damage_type = physical;
    }
    else {
	int val = atoi(node->first_node("val")->value())+atoi(node->first_node("aug")->value()); //aug only when activated
    	int index = position(name,stats_name,num_stat); 
    	if(index != num_stat)
	{
		chr.stats[index] += val;
	}
	else
	{
    		int index = position3(name,stats_name,num_stat); 
    		if(index != num_stat)
			chr.stats[index] += val;
	}
   }
	

  }
  _DEBUG_MSG(3," and %i ARM\n", chr.stats[armor]);


  _DEBUG_MSG(2, "Loaded: %s\n", chr.overview().c_str());
  for(auto w : chr.weapons) {
  	_DEBUG_MSG(2, "|-> %s\n", w.description().c_str());
}

}
