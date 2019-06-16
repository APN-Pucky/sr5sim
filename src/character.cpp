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

int CI::init() {
	return stats[reaction]+stats[intuition] + sum(init_dice) - mali();
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
	return phys_dmg/3+stun_dmg+3;
}
bool CI::ko() {
	return max_stun()<stun_dmg || max_ko()<phys_dmg;
}
bool CI::alive() {
	return max_phys()>phys_dmg;
}

void CI::attack_unarmed_combat(CI* enemy) {
	enemy->resist_armor_body(eval_net({agility,unarmed_combat},{reaction,intuition}),false)
}

void CI::resist_armor_body(int d){
	_DEBUG_MSG(1,"%s resists %i ",id().c_str(),d);	
	int dmg = max(0,d-eval({armor,body},false));
	take_dmg(dmg);
}

void CI::take_stun(int stun) {
	_DEBUG_MSG(1," => -%i STUN\n",dmg);
	this->stun_dmg += dmg;
}
void CI::take_dmg(int dmg){
	_DEBUG_MSG(1," => -%i HP\n",dmg);
	this->health_dmg += dmg;
}
int CI::eval_net( std::initializer_list<Stat> stats1, CI* enemy, std::initializer_list<Stat> stats2, bool apply_enemy_mali=true,bool apply_own_mali=true){
	return eval(stats1,apply_enemy_mali) - enemy->eval(stats2,apply_enemy_mali);
}

int CI::eval(std::initializer_list<Stat> stats, bool apply_mali=true) {
	int sum=0;
	_DEBUG_MSG(1,"[");
	for(auto s: stats) {
		sum+=this->chr.stats[s];
		_DEBUG_MSG(1,"%s(%i)+",abbrev[s].c_str(),this->chr.stats[s]);
	}
	int mal = this->mali();
	if(mal)
	{
		_DEBUG_MSG(1,"%s(-%i)","MAL",mal);
		sum-=mal;
	}
	_DEBUG_MSG(1,"]");
	return hits(sum);
}


string CI::id()
{
	return reference.alias + "#" + tos(uid);
}

string CI::description()
{
	return "";
}

