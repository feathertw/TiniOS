#include "mtype.h"
void *imemcpy(void *dest, void *src, uint n)
{
	uint *d = dest;
	const uint *s = src;
	uint i;
	for(i=0;i<n;i++)
	{
		d[i]=s[i];
	}
}
