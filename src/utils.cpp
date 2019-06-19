#include <sstream>
#include <iostream>
#include <string>
using namespace std;

template <typename T>
string tos( const T & t ) {
	stringstream os;
	os << t;
	return os.str();
}

void pppp() { cout << tos(0) <<endl;}

