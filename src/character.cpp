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
	int s = stats[reaction]+stats[intuition] ;
	_DEBUG_MSG(1, "INIT");
	_DEBUG_MSG(2, " %i+%id6",s,init_dice);
	s+= sum(init_dice);
	_DEBUG_MSG(1, " => %i\n",s);
	return s;
}

int CI::max_phys() {
	return 8+(stats[body]*3+1)/2; // cyberlimbs here
}
int CI::max_ko() {
	return 8+(stats[body]+1)/2; // cyberlimbs here
}
int CI::max_stun() {
	return 8+(stats[willpower]+1)/2; 
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
	enemy.resist_armor_body(eval_net({agility,unarmed_combat},enemy,{reaction,intuition},false));
}

void CI::resist_armor_body(int d){
	_DEBUG_MSG(1,"%s resists %i ",id().c_str(),d);	
	int dmg = max(0,d-eval({armor,body},false));
	take_phys(dmg);
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
		sum+=stats[s];
		_DEBUG_MSG(1,"%s(%i)+",abbrev[s].c_str(),stats[s]);
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
	if(c1.current_initiative() == c2.current_initiative())return c1.stats[edge]>c2.stats[edge];
	return c1.current_initiative() > c2.current_initiative();
}
bool  operator> ( CI& c1, CI& c2) {
	if(c1.has_acted && !c2.has_acted) return true;
	if(c2.has_acted && !c1.has_acted) return false;
	if(c1.current_initiative() == c2.current_initiative())return c1.stats[edge]<c2.stats[edge];
	return c1.current_initiative() < c2.current_initiative();
}
CI& CI::operator= (const CI&& c1) {
	init_dice = c1.init_dice;
	stats = c1.stats;
	uid = c1.uid;
	current_init_roll =c1.current_init_roll;
	stun_dmg =c1.stun_dmg;
	phys_dmg =c1.phys_dmg;
	has_acted =c1.has_acted;
	return *this;
}


string CI::id()
{
	return reference.alias + "#" + tos(uid);
}

string CI::description()
{
	return id()  + ": "+ tos(phys_dmg) + "/" + tos(max_phys()) + " PHYS, " + tos(stun_dmg) + "/" + tos(max_stun()) + " STUN, INIT: " + tos(current_initiative()) + ", ACTIVE: " + tos((int)!has_acted);
}

