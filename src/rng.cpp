#include <cstdlib>
#include <ctime>
#include "debug.h"

void init()
{
	srand((unsigned int) time(nullptr));
}

int hits(int n) {
	int ret = 0;
	int r;
	_DEBUG_MSG(2,"=[");
	for(int i =0; i < n;++i)
	{
		r=rand()%6+1;
		_DEBUG_MSG(2,"%d,",r);
		if(r>4)ret++;
	}
	_DEBUG_MSG(2,"]=%d",ret);
	return ret;
}

int sum(int n) {
	int ret = 0;
	int r;
	_DEBUG_MSG(2,"=[");
	for(int i =0; i < n;++i)
	{
		r=rand()%6+1;
		_DEBUG_MSG(2,"%d,",r);
		ret+=r;
	}
	_DEBUG_MSG(2,"]=%d",ret);
	return ret;
}
