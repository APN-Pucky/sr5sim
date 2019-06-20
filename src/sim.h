#include <vector>
#include <iostream>
#include <string>
#include <initializer_list>
#include "character.h"
#include "debug.h"

using namespace std;


struct SimulationData 
{
	int wins=0;
	int stalls=0;
	int losses=0;
	vector<int> data;
	
	SimulationData& operator+=(const SimulationData& sim) {
		_DEBUG_ASSERT(sim.data.size()==data.size());
		wins +=  sim.wins;
		stalls +=  sim.stalls;
		losses +=  sim.losses;
		for(int i = 0; i < sim.data.size();++i)
			data[i] += sim.data[i];
		return *this;
	}
	void reset() {
		wins  =0;
		losses  =0;
		stalls=0;
		data.clear();
	}
};

using SimData = SimulationData;


void simulate(SimData& sd,std::vector<Character> chars, bool data =false);

