#include "main.h"
#include "mlib.h"
#include "task.h"

#define TASK_STACK_SIZE 256
#define PRESERVE_REGSET 32

void syscall();
RegSet *to_user_mode(RegSet *stack);
int init_task()
{
	mputs("1: THIS IS INIT_TASK\n");
	syscall();
	mputs("2: THIS IS INIT_TASK\n");
	syscall();
	while(1);
}
int main()
{
	mputs("THIS IS MAIN\n");

	unsigned int task_stack[TASK_STACK_SIZE];
	RegSet *rs= (RegSet *)task_stack+TASK_STACK_SIZE-PRESERVE_REGSET;
	rs->pc = (unsigned int) &init_task;

	mputs("1: START!\n");
	rs = to_user_mode(rs);
	mputs("2: BACK!\n");

	mputs("2: START!\n");
	rs = to_user_mode(rs);
	mputs("2: BACK!\n");

	while(1);

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
