#include <cassert>
#include <sstream>
#include <string>
#include <initializer_list>
#include <algorithm>
#include "debug.h"
#include "character.h"
#include "rng.h"
#include "utils.h"

using namespace std;

int CI::current_initiative() {
	return current_init_roll-mali();
}

int CI::initiative() {
	int s = stat(reaction)+stat(intuition) ;
	_DEBUG_MSG(1, "INIT");
	_DEBUG_MSG(2, " %i+%id6",s,init_dice);
	s+= sum(init_dice);
	_DEBUG_MSG(1, " => %i\n",s);
	return s;
}

int CI::max_phys() {
	return 8+(stat(body)*3+1)/2; // cyberlimbs here
}
int CI::max_ko() {
	return 8+(stat(body)+1)/2; // cyberlimbs here
}
int CI::max_stun() {
	return 8+(stat(willpower)+1)/2; 
}

int CI::mali() {
	return phys_dmg/3+stun_dmg/3;
}
bool CI::ko() {
	return max_stun()<stun_dmg || max_ko()<phys_dmg;
}
bool CI::alive() {
	return max_phys()>phys_dmg;
}

void CI::act(vector<CI>& cis) {
	_DEBUG_MSG(1,"TURN: %s\n", description().c_str());
	has_acted = true;
	if(ko())return;
	attack_unarmed_combat(cis[1]);
}

void CI::attack_unarmed_combat(CI& enemy) {
	if(ko())return;
	int net = eval_net({agility,unarmed_combat},enemy,{reaction,intuition},false);
	if(net >0){
		enemy.resist_armor_body(stat(strength)+net,true);
	}
	else {
		_DEBUG_MSG(1,"%s dodged\n",enemy.id().c_str());
	}
}

void CI::resist_armor_body(int d, int ap, bool stun){
	_DEBUG_MSG(1,"%s resists %i with %i AP ",id().c_str(),d,ap);	
	stats[armor]+=ap;
	int dmg = max(0,d-eval({armor,body},false));
	if(stun || dmg < stat(armor)){
		take_stun(dmg);
	}
	else
	{
		take_phys(dmg);
	}
	stats[armor]-=ap;
}



void CI::take_stun(int stun) {
	_DEBUG_MSG(1," => -%i STUN\n",stun);
	this->stun_dmg += stun;
}
void CI::take_phys(int dmg){
	_DEBUG_MSG(1," => -%i HP\n",dmg);
	this->phys_dmg += dmg;
}

void CI::init() {
	current_init_roll = initiative();
	has_acted = false;
}


int CI::eval_net( std::initializer_list<Stat> stats1, CI& enemy, std::initializer_list<Stat> stats2, bool apply_enemy_mali,bool apply_own_mali){
	_DEBUG_MSG(1,"(");
	auto first = eval(stats1,apply_own_mali);
	_DEBUG_MSG(1,") vs (");
	auto second = enemy.eval(stats2,apply_enemy_mali);
	_DEBUG_MSG(1,")=%i ", first-second);
	return first-second;
}

int CI::eval(std::initializer_list<Stat> statslist, bool apply_mali) {
	int sum=0;
	_DEBUG_MSG(1,"[");
	for(auto s : statslist) {
		sum+=stat(s);
		_DEBUG_MSG(1,"%s(%i)+",stats_abbrev[s].c_str(),stat(s));
	}
	int mal = this->mali();
	if(apply_mali && mal)
	{
		_DEBUG_MSG(1,"%s(-%i)","MAL",mal);
		sum-=mal;
	}
	_DEBUG_MSG(1,"]");
	return hits(sum);
}

bool  operator< ( CI& c1, CI& c2) {
	if(c1.has_acted && !c2.has_acted) return false;
	if(c2.has_acted && !c1.has_acted) return true;
	if(c1.current_initiative() == c2.current_initiative())return c1.stat(edge)>c2.stat(edge);
	return c1.current_initiative() > c2.current_initiative();
}
bool  operator> ( CI& c1, CI& c2) {
	if(c1.has_acted && !c2.has_acted) return true;
	if(c2.has_acted && !c1.has_acted) return false;
	if(c1.current_initiative() == c2.current_initiative())return c1.stat(edge)<c2.stat(edge);
	return c1.current_initiative() < c2.current_initiative();
}


int Character::uid()
{
	return uuid;
}
int CI::uid(){return reference.uid();}

string CHR::id() {
	stringstream ss;
	ss << alias << "#" << uid();
	return ss.str();
}
string CI::id()
{
	return reference.id();
}

string CHR::description() {
	stringstream ss;
	ss << id();
	return ss.str();
}
string CI::description()
{
	stringstream ss;
	ss << reference.description()  << ": "<< phys_dmg << "/" << max_phys() << " PHYS, " << stun_dmg << "/" << max_stun() << " STUN, INIT: " <<current_initiative()<< ", ACTIVE: " << !has_acted;
	return ss.str();
}

int CI::stat(int s) {
	return stats[s] + statgroups[group[s]];
}
int CHR::stat(int s) {
	return stats[s] + statgroups[group[s]];
}
string CI::overview()
{
	stringstream ss;
	ss << description();
	for (int skill = body; skill!=num_stat;skill++)
	{
		ss << endl <<stats_abbrev[skill] << ": " << stat(skill);	
	}
	return ss.str();
}

string CHR::overview()
{
	stringstream ss;
	ss << description();
	for (int skill = body; skill!=num_stat;skill++)
	{
		ss << endl <<stats_abbrev[skill] << ": " << stat(skill);	
	}
	return ss.str();
}

