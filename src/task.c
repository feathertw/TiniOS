#include "mlib.h"

void qsort(int *array, int left, int right);
int  gcd(int m, int n);
void bcd(int n);
void show_array(int *array, int n);

void show_array(int *array, int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		mputc(' ');
		mputn(array[i]);
	}
	mputc('\n');
}
void qsort_task()
{
	mputs("QSORT TASK\n");
	int array[10]={33,11,-3,99,-9,67,11,-1,22,66};
	show_array(array,10);
	qsort(array,0,10-1);
	show_array(array,10);
	mputc('\n');
}
void gcd_task()
{
	int m;
	int n;
	int g;
	mputs("GCD TASK\n");
	mputs("key in number 1:");
	m=mgetn();
	mputs("key in number 2:");
	n=mgetn();
	g=gcd(m,n);
	mputs("gcd number is:");
	mputn(g);
	mputc('\n');
}
void bcd_task()
{
	int m;
	mputs("BCD TASK\n");
	mputs("enter a number:");
	m=mgetn();
	bcd(m);
	mputc('\n');
}
