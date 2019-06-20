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

int CI::current_initiative() const{
	return current_init_roll-mali();
}

int CI::initiative() const{
	int s = stat(reaction)+stat(intuition) ;
	_DEBUG_MSG(1, "INIT");
	_DEBUG_MSG(2, " %i+%id6",s,init_dice + stat(initiative_dice));
	s += sum(init_dice+stat(initiative_dice));
	_DEBUG_MSG(1, " => %i\n",s);
	return s;
}
int CI::limit(Limit l) const {return l==physical?physical_limit():l==mental?mental_limit():l==social?social_limit():0;}
int CI::physical_limit() const{ return (stat(strength)*2+stat(body)+stat(reaction)+2)/3;}
int CI::mental_limit() const{ return (stat(logic)*2+stat(intuition)+stat(willpower)+2)/3;}
int CI::social_limit() const{ return (stat(charisma)*2+stat(willpower)+stat(essence)+2)/3;}

int CI::max_phys() const{
	return 8+(stat(body)*3+1)/2+stat(physicalcm); 
}
int CI::max_ko() const{
	return 8+(stat(body)+1)/2+stat(physicalcm); 
}
int CI::max_stun() const{
	return 8+(stat(willpower)+1)/2; 
}

int CI::mali() const{
	return reference.pain_editor?0:(phys_dmg/3+stun_dmg/3);
}
bool CI::ko() const{
	if(reference.pain_editor)return !alive();
	return max_stun()<=stun_dmg || max_ko()<=phys_dmg;
}
bool CI::alive() const
{
	return max_phys()>phys_dmg;
}

void CI::act(vector<CI>& cis) {
	_DEBUG_MSG(1,"TURN: %s\n", description().c_str());
	has_acted = true;
	if(ko())return;
	if(uid()==1) {
		for(CI& c : cis)
		{
			if(c.uid()!=1 && !c.ko()) {
				current_weapon = reference.weapon("Ares Alpha");
				current_weapon.bullets = 6;
				current_weapon.use +=1; //scope simple action
				current_weapon.use -=2 ;//vitals
				current_weapon.damage +=2;
				current_weapon.ap += -4; //APDS
				attack_weapon(c);
				current_weapon.ap -= -4; //APDS
				current_weapon.use -=1;
				current_weapon.use +=2;
				current_weapon.damage -=2;
				return;
			}
		}
	}
	else {
		for(CI& c : cis)
		{
			if(c.uid()==1 && !c.ko()) {
				current_weapon = reference.weapon("Altmayr SPX2");
				attack_weapon(c);
			}
		}
		
	}
	//attack_unarmed_combat(cis[1]);
}

void CI::attack_weapon(CI& enemy) {
	if(ko())return;
	const Weapon w(current_weapon);
	int net = 0;
	if(w.useskill==close_combat || group[w.useskill] == close_combat) {
		int dreach = enemy.stat(reach)+enemy.current_weapon.reach-w.reach-stat(reach);
		//enemy.mod_stats[reach] += dreach;
		net = eval_net({w.useattr,w.useskill},w.accuracy?w.accuracy:physical_limit(),enemy,{reaction,intuition},enemy.physical_limit(),true,true,0+w.use,dreach); //Mali for dodge
		//enemy.mod_stats[reach] -=dreach;
	}
	else{
		int bm =  (1-w.bullets);
		int bb = min(0,enemy.stat(intuition)+enemy.stat(reaction)-(w.bullets-1));
		net = eval_net({w.useattr,w.useskill},w.accuracy?w.accuracy:physical_limit(),enemy,{reaction,intuition},enemy.physical_limit(),true, true,-bb+w.use,bm); //Mali for dodge
	}
	if(net >0){
		enemy.resist_armor_body(w.damage+stat(w.damage_skill)+net,w.ap,w.damage_type==stun);
	}
	else {
		_DEBUG_MSG(1,"%s dodged\n",enemy.id().c_str());
	}
}

void CI::attack_unarmed_combat(CI& enemy) {
	/*attack_weapon(enemy,reference.weapon("Unarmed Attack"));
	if(ko())return;
	int net = eval_net({agility,unarmed_combat,reach},physical_limit(),enemy,{reaction,intuition},enemy.physical_limit(),false);
	if(net >0){
		enemy.resist_armor_body(stat(strength)+net,0,true);
	}
	else {
		_DEBUG_MSG(1,"%s dodged\n",enemy.id().c_str());
	}*/
}

void CI::resist_armor_body(int d, int ap, bool stun){
	_DEBUG_MSG(1,"%s resists %i with %i AP ",id().c_str(),d,ap);	
	mod_stats[armor]+=ap;
	int dmg = max(0,d-eval({armor,body, damage_resistance},0,false));
	if(stun || dmg < stat(armor)){
		take_stun(dmg);
	}
	else
	{
		take_phys(dmg);
	}
	mod_stats[armor]-=ap;
}



void CI::take_stun(int stun) {
	_DEBUG_MSG(1," => -%i STUN\n",stun);
	if(stun_dmg + stun >max_stun()) {
		stun -= max_stun()-this->stun_dmg;
		this->stun_dmg = max_stun();
		take_phys(stun);
	}
	else {
		//normal
		this->stun_dmg += stun;
	}
}
void CI::take_phys(int dmg){
	_DEBUG_MSG(1," => -%i HP\n",dmg);
	this->phys_dmg += dmg;
}

void CI::init() {
	current_init_roll = initiative();
	has_acted = false;
}


int CI::eval_net( std::initializer_list<Stat> stats1,int limit1, CI& enemy, std::initializer_list<Stat> stats2,int limit2, bool apply_enemy_mali,bool apply_own_mali, int own_bonus,int enemy_bonus){
	_DEBUG_MSG(1,"(");
	auto first = eval(stats1,limit1,apply_own_mali,own_bonus);
	_DEBUG_MSG(1,") vs (");
	auto second = enemy.eval(stats2,limit2,apply_enemy_mali,enemy_bonus);
	_DEBUG_MSG(1,")=%i ", first-second);
	return first-second;
}


int CI::eval(std::initializer_list<Stat> statslist,int limit, bool apply_mali, int bonus) 
{
	int sum=0;
	_DEBUG_MSG(1,"[");
	for(auto s : statslist) {
		sum+=stat(s);
		_DEBUG_MSG(1,"%s(%i)+",stats_abbrev(s).c_str(),stat(s));
	}
	if(bonus) {
		_DEBUG_MSG(1,"(%i)+",bonus);
		sum +=bonus;
	}
	int mal = this->mali();
	if(apply_mali && mal)
	{
		_DEBUG_MSG(1,"%s(-%i)","MAL",mal);
		sum-=mal;
	}
	_DEBUG_MSG(1,"]");
	int h = hits(sum);
	if(limit && h>limit) {
		h = limit;
		_DEBUG_MSG(1,">%i=%i",limit,limit);
	}
	return h;
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


int Character::uid() const
{
	return uuid;
}
int CI::uid() const{return reference.uid();}

string CHR::id() const
{
	stringstream ss;
	ss << alias << "#" << uid();
	return ss.str();
}
string CI::id() const
{
	return reference.id();
}

string CHR::description() const
{
	stringstream ss;
	ss << id();
	return ss.str();
}
string CI::description() const
{
	stringstream ss;
	ss << reference.description()  << ": "<< phys_dmg << "/" << max_phys() << " PHYS, " << stun_dmg << "/" << max_stun() << " STUN, INIT: " <<current_initiative()<< ", ACTIVE: " << !has_acted;
	return ss.str();
}

int CHR::stat(int s) const{
	return stats[s] + stats[group[s]] + stats[skill[s]];
}
int CI::stat(int s) const{
	return reference.stat(s) + mod_stats[s] +mod_stats[group[s]] + mod_stats[skill[s]];
}
string CI::overview() const
{
	stringstream ss;
	ss << description();
	for (int skill = body; skill!=num_stat;skill++)
	{
		ss << endl <<stats_abbrev(skill) << ": " << stat(skill);	
	}
	return ss.str();
}

string CHR::overview() const
{
	stringstream ss;
	ss << description();
	for (int skill = body; skill!=num_stat;skill++)
	{
		ss << endl <<stats_abbrev(skill) << ": " << stat(skill);	
	}
	return ss.str();
}

Weapon& CHR::weapon(string name) 
{
	for(Weapon& w : weapons)
	{
		if(w.name.compare(name)==0)return w;
	}
	return *(new Weapon());
}
