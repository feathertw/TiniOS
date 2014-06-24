#include "mtype.h"
#include "mlib.h"
#include "main.h"

uint mkfifo(char *pathname)
{
	uint buff[2+PATH_NAME_MAX];
	uint n=setbuff(buff+2,pathname);
	buff[0]=MKFIFO_FD;
	buff[1]=n;
	write(PATHSERVER_FD,buff,2+n);
	return 0;
}
uint open(char *pathname)
{
	uint replyfd = getpid()+PATH_NUM_RESERVED;
	uint buff[2+PATH_NAME_MAX];
	uint n=setbuff(buff+2,pathname);
	buff[0]=replyfd;
	buff[1]=n;
	write(PATHSERVER_FD,buff,2+n);
	read(replyfd, &replyfd, 1);
	return replyfd;
}
uint setbuff(uint *buff, char *s)
{
	uint c,n=0;
	do{
		GETCHAR(c,s+n);
		buff[n++]=c;
	}while(c);
	return n;
}
void mputo(char* s, int n)
{
	mputs(s);
	mputn(n);
	mputc('\n');
}
void mputu(uint *u)
{
	char c;
	while(*u)
	{
		c= (*u++)&(0xFF);
		mputc(c);
	}
}
int istrcmp(const int *a, const int *b)
{
	int r=0;
	while( !r && *a && *b) r=(*a++)-(*b++);
	return r;
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

