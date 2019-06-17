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
	Field(std::initializer_list<Character> chars,SimData& sd) : simdata(sd) {for(auto c : chars)cis.emplace_back(CI(c));}
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

void simulate(SimData& sd,std::initializer_list<Character> chars) 
{
	Field f(chars,sd);
	f.cis[0].uid = 1;
	int rounds = 0;
	while(!f.cis[0].ko() && !f.cis[1].ko() && rounds < 100)
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
	}
	
	f.simdata.res=STALL;
	for(auto a : f.cis)
		if(a.uid==1)f.simdata.res = a.ko()?LOSS:WIN;
}
