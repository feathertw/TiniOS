#define PIPE_DATA_SIZE	512
#define PIPE_PUSH(PIPE,V) \
	do{ \
		(PIPE).data[(PIPE).head]=(V); \
		(PIPE).head++; \
		if((PIPE).head>PIPE_DATA_SIZE) (PIPE).head=0; \
	}while(0)
#define PIPE_POP(PIPE,V) \
	do{ \
		(V)=(PIPE).data[(PIPE).tail]; \
		(PIPE).tail++; \
		if((PIPE).tail>PIPE_DATA_SIZE) (PIPE).tail=0; \
	}while(0)
#define PIPE_LENTH(PIPE) \
	(PIPE).head>(PIPE).tail?(PIPE).head-(PIPE).tail:PIPE_DATA_SIZE-((PIPE).tail-(PIPE).head)

typedef unsigned int uint;
typedef struct
{
	uint head;
	uint tail;
	uint data[PIPE_DATA_SIZE];
}Pipe_Ringbuffer;
typedef struct
{
	uint state;
	uint it_number;
	uint r4;
	uint r5;
	uint r6;
	uint r7;
	uint r8;
	uint r9;
	uint r10;
	uint r11;
	uint r12;
	uint r13;
	uint r14;
	uint r15;
	uint r16;
	uint r17;
	uint r18;
	uint r19;
	uint r20;
	uint r21;
	uint r22;
	uint r23;
	uint r24;
	uint r25;
	uint r26;
	uint r27;

	uint r0;
	uint r1;
	uint r2;
	uint r3;
	uint fp;
	uint gp;
	uint lp;
	uint pc;
}RegSet;
