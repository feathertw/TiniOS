#include "mtype.h"
#include "main.h"
#include "mlib.h"
#include "task.h"

#define IT_FORK 	0x1
#define IT_GETPID 	0x2
#define IT_READ 	0x3
#define IT_WRITE 	0x4
#define IT_SYSCALL	0x8
#define IT_SYSTICK	0x9

void syscall();
int fork();
int getpid();
int read(int fd, void *buff, uint size);
int write(int fd, const void *buff, uint size);

RegSet *to_user_mode(RegSet *stack);
void pathserver()
{
	mputs("THIS IS PATHSERVER\n");

	uint paths[PIPE_NUM_LIMIT-TASK_NUM_LIMIT-PATH_NUM_RESERVED][PATH_NAME_MAX];
	uint num=0;
	uint buff[PATH_NAME_MAX];

	uint n = setbuff(buff,"/sys/pathserver");
	imemcpy(paths[num++],buff,n);

	uint i;
	uint fd;
	uint len;

	while(1)
	{
		read(PATHSERVER_FD,&fd,1);
		read(PATHSERVER_FD,&len,1);
		read(PATHSERVER_FD,buff,len);

		if(fd==MKFIFO_FD)
		{
			imemcpy(paths[num++],buff,len);
		}
		else
		{
			for(i=0;i<num;i++)
			{
				if( *paths[i] && istrcmp(buff,paths[i])==0 )
				{
					i = i + PATH_NUM_RESERVED +TASK_NUM_LIMIT;
					write(fd,&i,1);
					i=0;
					break;
				}
				if(i>=num)
				{
					i=-1;
					write(fd,&i,1);
				}
			}
		}
	}
}
void counter(int t, char *s)
{
	int i;
	while(1)
	{
		i=t;
		while(i--);
		mputs(s);
	}
}
void second_task()
{
	uint len;
	uint buff[100];
	mputs("THIS IS SECOND_TASK\n");
	mkfifo("/proc/0");
	uint fd = open("/proc/0");
	while(1)
	{
		read(fd,&len,1);
		read(fd,buff,len);
		mputu(buff);
	}
}
void init_task()
{
	mputs("THIS IS INIT_TASK\n");
	if( !fork() ) pathserver();
	if( !fork() ) second_task();
	uint fd = open("/proc/0");
	uint buff[100];
	uint len;
	while(1)
	{
		len=setbuff(buff+1,"this is message\n");
		buff[0]=len;
		write(fd,buff,1+len);
	}
}
RegSet *set_task(uint *task_stack, void (*start)() )
{
	RegSet *rs= (RegSet *)(task_stack+TASK_STACK_SIZE-PRESERVE_REGSET);
	rs->state = TASK_READY;
	rs->pc = (uint)start;
	return rs;
}

uint task_number =0;
uint task_currnet=0;
Pipe_Ringbuffer pipes[PIPE_NUM_LIMIT];
int main()
{
	mputs("THIS IS MAIN\n");

	uint i;
	for(i=0;i<PIPE_NUM_LIMIT;i++)
		pipes[i].head = pipes[i].tail = 0;

	uint task_stack[TASK_NUM_LIMIT][TASK_STACK_SIZE];
	RegSet *rs[TASK_NUM_LIMIT];
	rs[task_number]=set_task(task_stack[task_number],&init_task);
	task_number++;

	SYSTICK_RELOAD_VALUE=5000;
	SYSTICK_CONTROL=SYSTICK_CONTROL_ENABLE|SYSTICK_CONTROL_CONTINUOUS;

	while(1)
	{
		//mputc('*');
		if(rs[task_currnet]->state==TASK_READY)
			rs[task_currnet] = to_user_mode(rs[task_currnet]);
		//rs[task_currnet]->state=TASK_READY;
		switch(rs[task_currnet]->it_number)
		{
			case IT_FORK:
				if(task_number==TASK_NUM_LIMIT)
				{
					rs[task_currnet]->r0=-1;
				}
				else
				{
					uint used=(task_stack[task_currnet])+
						(TASK_STACK_SIZE)-(uint *)(rs[task_currnet]);
					rs[task_number]=(RegSet *)
						(task_stack[task_number]+(TASK_STACK_SIZE)-used);
					imemcpy(rs[task_number],rs[task_currnet],used);

					rs[task_currnet]->r0=task_number;
					rs[task_number]->r0=0;
					task_number++;
				}
				break;
			case IT_GETPID:
				rs[task_currnet]->r0=task_currnet;
				break;
			case IT_READ:
				_read(rs[task_currnet],&pipes[rs[task_currnet]->r0]);
				if(rs[task_currnet]->state==TASK_READY)
				{
					for(i=0;i<task_number;i++)
					{
						if(rs[i]->state==TASK_WAIT_WRITE)
							rs[i]->state=TASK_WRITE;
					}
				}
				break;
			case IT_WRITE:
				_write(rs[task_currnet],&pipes[rs[task_currnet]->r0]);
				if(rs[task_currnet]->state==TASK_READY)
				{
					for(i=0;i<task_number;i++)
					{
						if(rs[i]->state==TASK_WAIT_READ)
							rs[i]->state=TASK_READ;
					}
				}
				break;

			case IT_SYSCALL:
				break;
			case IT_SYSTICK:
				break;
		}
		while(1)
		{
			task_currnet=(task_currnet+1>=task_number)?0:task_currnet+1;
			uint state=rs[task_currnet]->state;
			if(state==TASK_READY||state==TASK_READ||state==TASK_WRITE) break;
		}
	}

	//while(1);

	//int n;
	//while(n!=9)
	//{
	//	mputs("\n\n\n");
	//	mputs("PROGRAM START\n");
	//	mputs(">> 1: qsort\n");
	//	mputs(">> 2: gcd\n");
	//	mputs(">> 3: bcd\n");
	//	mputs(">> 9: go\n");
	//	n=mgetn();
	//	switch(n)
	//	{
	//		case 1: qsort_task(); break;
	//		case 2: gcd_task();   break;
	//		case 3: bcd_task();   break;
	//	}
	//}

	//while(1);
	//return 0;
}
