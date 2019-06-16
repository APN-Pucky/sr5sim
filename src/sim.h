#include <vector>
#include <string>
#include <initializer_list>
#include "character.h"

using namespace std;
enum Result {
	LOSS,WIN,STALL,
};

struct GeneralData
{
	vector<int> ints;
	vector<string> strings;
};

struct SimulationData 
{
	Result res;
	vector<GeneralData> data;
};

using SimData = SimulationData;


void simulate(SimData& sd,std::initializer_list<Character> chars);

