#include "mtype.h"
#include "mlib.h"
#include "main.h"

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
void _read(RegSet *rs, Pipe_Ringbuffer *pipe)
{
	rs->state = TASK_READY;
	int fd = rs->r0;
	uint *buff = (uint *)rs->r1;
	uint size = rs->r2;
	if(fd>=PIPE_NUM_LIMIT||size>PIPE_DATA_SIZE)
	{
		rs->r0=-1;
	}
	else if( size>PIPE_LENTH(*pipe))
	{
		rs->state = TASK_WAIT_READ;
	}
	else
	{
		uint i=0;
		for(i=0;i<size;i++)
			PIPE_POP(*pipe,buff[i]);
	}
}
void _write(RegSet *rs, Pipe_Ringbuffer *pipe)
{
	rs->state = TASK_READY;
	int fd = rs->r0;
	const uint *buff = (const uint *)rs->r1;
	uint size = rs->r2;
	if(fd>=PIPE_NUM_LIMIT||size>PIPE_DATA_SIZE)
	{
		rs->r0=-1;
	}
	else if( size>PIPE_DATA_SIZE-PIPE_LENTH(*pipe))
	{
		rs->state = TASK_WAIT_WRITE;
	}
	else
	{
		uint i=0;
		for(i=0;i<size;i++)
			PIPE_PUSH(*pipe,buff[i]);
	}
}

