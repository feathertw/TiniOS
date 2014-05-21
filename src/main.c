int  mgetn();
void mputs(char*);
void qsort_task();
void gcd_task();
void bcd_task();
int main()
{
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
