#include "mtype.h"
#include "mlib.h"
void mputo(char* s, int n)
{
	mputs(s);
	mputn(n);
	mputc('\n');
}
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
