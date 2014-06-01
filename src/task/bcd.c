#include "mlib.h"
void bcd(int n)
{
	int mm;
	int num=0;
	int array[100];
	while(n>0)
	{
		array[num]=mod_u10(n);
		n=div_u10(n);
		num++;
	}
	while(num>0)
	{
		switch(array[num-1])
		{
			case 0: mputs("0000"); break;
			case 1: mputs("0001"); break;
			case 2: mputs("0010"); break;
			case 3: mputs("0011"); break;
			case 4: mputs("0100"); break;
			case 5: mputs("0101"); break;
			case 6: mputs("0110"); break;
			case 7: mputs("0111"); break;
			case 8: mputs("1000"); break;
			case 9: mputs("1001"); break;
		}
		mputc(' ');
		num--;
	}
}
