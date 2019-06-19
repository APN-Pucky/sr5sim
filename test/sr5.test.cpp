#include <iostream>
#include "catch.hpp"
#include "sr5.h"

using namespace std;

TEST_CASE("SR5 test const", "[sr5]") {
	cout << "Stats:" << endl;
	for(int s = body; s!=num_stat; s++) {
		cout << s << ": SPC:" << stats_name[s] << " GRP: " << stats_name[group[s]] <<  " SKL: " << stats_name[skill[s]] << endl;	
	}

	SECTION("Stat Existing") {
		for(int s = body; s!=num_stat; s++) {
			REQUIRE(stats_name[s].compare(""));
		}
	}
	SECTION("Stat Consistency") {
		for(int s = body; s!=num_stat; s++) {
			if(skill[s]!=zero) {
				REQUIRE( group[s]==group[skill[s]]);
			}
		}
	}
	
}
