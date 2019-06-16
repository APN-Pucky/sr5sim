#include <cassert>
#include <sstream>
#include <string>
#include <initializer_list>
#include "debug.h"
#include "character.h"
#include "rng.h"
#include "utils.h"

using namespace std;


void CI::resist_armor_body(int d)
{
	assert(d >=0);
	_DEBUG_MSG(1,"%s resists %d ",id().c_str(),d);	
	int dmg = max(0,d-eval({armor,body}));
	reduce_health(dmg);
}

void CI::reduce_health(int dmg)
{
	_DEBUG_MSG(1," => -%d HP\n",dmg);
	this->health -= dmg;
}
int CI::eval_net( std::initializer_list<Stat> stats1, CI* enemy, std::initializer_list<Stat> stats2){
	return eval(stats1) - enemy->eval(stats2);
}

int CI::eval(std::initializer_list<Stat> stats) {
	int sum=0;
	_DEBUG_MSG(1,"[");
	for(auto s: stats) {
		sum+=this->chr.stats[s];
		_DEBUG_MSG(1,"%s(%d)+",abbrev[s].c_str(),this->chr.stats[s]);
	}
	_DEBUG_MSG(1,"]");
	return roll(sum);
}


string CI::id()
{
	return reference.alias + "#" + tos(uid);
}

string CI::description()
{
	return "";
}

