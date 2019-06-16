#include <vector>
#include <initializer_list>
#include <map>
#include <algorithm>
#include "sim.h"

class Field
{
public:
	SimData& simdata;
	vector<CI> cis;
	Field(std::initializer_list<Character> chars,SimData& sd) : simdata(sd) {for(auto c : chars)cis.emplace_back(CI(c));}
};


void new_init_round(Field& f)
{
	//new initiative
	for(auto ci : f.cis)
	{
		ci.init();
	}
}

void simulate(SimData& sd,std::initializer_list<Character> chars) 
{
	Field f(chars,sd);
	f.cis[0].uid = 1;
	new_init_round(f);
	sort(f.cis,greater<CI>);
	
	while(!f.cis[0].has_acted && f.cis[0].current_initiative()>0)
	{
		f.cis[0].act(f.cis);
		f.cis[0].current_init_roll -=10;
		sort(f.cis.begin(),f.cis.end(),greater<CI>);		
	}
	
	f.simdata.res=STALL;
	for(auto a : f.cis)
		if(a.uid==1)f.simdata.res = a.ko()?LOSS:WIN;
};