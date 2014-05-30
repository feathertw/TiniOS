int  mgetn();
void mputs(char*);
void qsort_task();
void gcd_task();
void bcd_task();
int mod_u10(int n);
#define SYSTICK_CONTROL 	*(volatile int *)(0x0E100000)
#define SYSTICK_RELOAD_VALUE 	*(volatile int *)(0x0E100004)
#define SYSTICK_STATUS	 	*(volatile int *)(0x0E101000)
#define SYSTICK_CURRENT_VALUE 	*(volatile int *)(0x0E101004)
#define SYSTICK_CONTROL_ENABLE       1
#define SYSTICK_CONTROL_CLEAR        2
#define SYSTICK_CONTROL_CONTINUOUS   4
int main()
{
	SYSTICK_RELOAD_VALUE=300;
	SYSTICK_CONTROL=SYSTICK_CONTROL_ENABLE|SYSTICK_CONTROL_CONTINUOUS;

	int i=300;
	while(i--)
	{
		char c = '#';
		mputc(c);
	}
	SYSTICK_CONTROL=0;
	//while(1);

	char *main_check="THIS IS MAIN\n";
	mputs(main_check);

	//int i;
	//int n;
	//int string_array[100];
	//char *mget_check="THIS IS MGET";
	//mputs(mget_check);
	//n=mgets(string_array);
	//for(i=0;i<n;i++) mputc(string_array[i]);
	//mputc('\n');

	int n;
	while(n!=9)
	{
		mputs("\n\n\n");
		mputs("PROGRAM START\n");
		mputs(">> 1: qsort\n");
		mputs(">> 2: gcd\n");
		mputs(">> 3: bcd\n");
		mputs(">> 9: go\n");
		n=mgetn();
		switch(n)
		{
			case 1: qsort_task(); break;
			case 2: gcd_task();   break;
			case 3: bcd_task();   break;
		}
	}

	while(1);
	return 0;
}
