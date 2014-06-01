#include "main.h"
#include "mlib.h"
#include "task.h"

#define TASK_NUM_LIMIT  8
#define TASK_STACK_SIZE 256
#define PRESERVE_REGSET 32

void syscall();
RegSet *to_user_mode(RegSet *stack);
void init_task()
{
	int i=0;
	while(1)
	{
		mputn(i++); mputc(' ');
		mputs("THIS IS INIT_TASK\n");
		syscall();
	}
}
void second_task()
{
	int i=0;
	while(1)
	{
		mputn(i++); mputc(' ');
		mputs("THIS IS SECOND_TASK\n");
		syscall();
	}
}
RegSet *set_task(unsigned int *task_stack, void (*start)() )
{
	RegSet *rs= (RegSet *)task_stack+TASK_STACK_SIZE-PRESERVE_REGSET;
	rs->pc = (unsigned int)start;
	return rs;
}

int main()
{
	mputs("THIS IS MAIN\n");
	unsigned int task_number =0;
	unsigned int task_currnet=0;

	unsigned int task_stack[TASK_NUM_LIMIT][TASK_STACK_SIZE];
	RegSet *rs[TASK_NUM_LIMIT];

	rs[task_number]=set_task(task_stack[task_number],&init_task);
	task_number++;
	rs[task_number]=set_task(task_stack[task_number],&second_task);
	task_number++;

	while(1)
	{
		rs[task_currnet] = to_user_mode(rs[task_currnet]);
		task_currnet=(task_currnet+1>=task_number)?0:task_currnet+1;
	}

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
