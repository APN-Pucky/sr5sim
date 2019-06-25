#include <vector>
#include <iostream>
#include <initializer_list>
#include <map>
#include <algorithm>
#include "sim.h"
#include "debug.h"

class Field
{
public:
	SimData& simdata;
	vector<CI> cis;
	Field(std::vector<Character> chars,SimData& sd) : simdata(sd) {
		for(auto c : chars){
			cis.emplace_back(CI(c));
		}
	}
};


void new_init_round(Field& f)
{
	//new initiative
	for(CI& ci : f.cis)
	{
		ci.init();
	}
}

void next_round(Field& f)
{
	//new initiative
	for(CI& ci : f.cis)
	{
		ci.has_acted =false;
	}
}

void simulate(SimData& sd,std::vector<Character> chars,bool data) 
{
	Field f(chars,sd);
	//f.cis[0].reference.uid = 1;
	int rounds = 0;
	bool done = false;
	while(!done && rounds < 100)
	{
		rounds++;
		new_init_round(f);
		sort(f.cis.begin(),f.cis.end());
		while(f.cis[0].current_initiative()>0)
		{
			_DEBUG_MSG(2,"ROUND:\n");
			while(!f.cis[0].has_acted )
			{
				if(f.cis[0].current_initiative()>0 ) {
					f.cis[0].act(f.cis);
					f.cis[0].current_init_roll -=10;
				}
				else
				{
					f.cis[0].has_acted = true;
				}
				//move back -> faster sort?
				f.cis.emplace_back(f.cis[0]);
				f.cis.erase(f.cis.begin());
				sort(f.cis.begin(),f.cis.end());		
			}
			next_round(f);
			// and re-sort
			sort(f.cis.begin(),f.cis.end());		
		}
		bool tdone = true;
		for (auto c : f.cis) {
			if(c.uid()==1 && c.ko())done = true;
			if(c.uid()!=1 && !c.ko())tdone = false;
		}
		if(tdone)done = true;
	}
	
	f.simdata.reset();
	for(auto a : f.cis) {
		if(a.uid()==1){
			if(a.ko()){
				f.simdata.losses =1;
			}
			else{
				f.simdata.wins = 1;
			}
			if(data) {
				f.simdata.data.emplace_back(a.stun_dmg);
				f.simdata.data.emplace_back(a.max_stun());
				f.simdata.data.emplace_back(a.phys_dmg);
				f.simdata.data.emplace_back(a.max_phys());
			}
		}
	}
	if(!f.simdata.losses && !f.simdata.wins)f.simdata.stalls = 1;
}
