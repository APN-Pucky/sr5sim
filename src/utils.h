#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <string>
using namespace std;

template <typename T>
std::string tos( const T & t );

void pppp();

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

	template <typename T>
bool contains(const T &value,const T array[],int size)
{
	for(int i = 0; i < size;i++)
	{
		if(array[i]==value) return true;
	}
	return false;
}

	template <typename T>
int position( const T &value,const T array[],int size)
{
	for(int i = 0; i < size;i++)
	{
		if(array[i]==value) return i;
	}
	return size;
}
inline int position3(const string& value, const string array[], int size)
{
	for(int i = 0; i < size;i++)
	{
		string str = array[i].substr(0,3);
		string str2  = value;
		for (auto & c: str) c = toupper(c);
		for (auto & c: str2) c = toupper(c);
		if(str.compare(str2)==0) return i;
	}
	return size;
}
#endif
