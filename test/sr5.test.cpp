#include <iostream>
#include "catch.hpp"
#include "sr5.h"

using namespace std;

TEST_CASE("SR5 test const", "[sr5]") {
	cout << "Stats:" << endl;
	for(int s = body; s!=num_stat; s++) {
		cout << s << ": " << stats_name[s] << " aka " << stats_abbrev[s] <<  " in" << statgroups_name[group[s]] << endl;	
	}
	cout << "Statgroups:" << endl;
	for(int s = body; s!=num_statgroup; s++) {
		cout << s << ": " << statgroups_name[s] << endl;	
	}
}
