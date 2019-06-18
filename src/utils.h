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
