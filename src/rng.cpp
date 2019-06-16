#include <stdlib.h>
#include <time.h>
#include "debug.h"

void init()
{
	srand(time(NULL));
}

int roll(int n)
{
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

