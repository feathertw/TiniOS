#define SYSTICK_CONTROL 	*(volatile int *)(0x0E100000)
#define SYSTICK_RELOAD_VALUE 	*(volatile int *)(0x0E100004)
#define SYSTICK_STATUS	 	*(volatile int *)(0x0E101000)
#define SYSTICK_CURRENT_VALUE 	*(volatile int *)(0x0E101004)
#define SYSTICK_CONTROL_ENABLE       1
#define SYSTICK_CONTROL_CLEAR        2
#define SYSTICK_CONTROL_CONTINUOUS   4

typedef struct
{
	unsigned int r4;
	unsigned int r5;
	unsigned int r6;
	unsigned int r7;
	unsigned int r8;
	unsigned int r9;
	unsigned int r10;
	unsigned int r11;
	unsigned int r12;
	unsigned int r13;
	unsigned int r14;
	unsigned int r15;
	unsigned int r16;
	unsigned int r17;
	unsigned int r18;
	unsigned int r19;
	unsigned int r20;
	unsigned int r21;
	unsigned int r22;
	unsigned int r23;
	unsigned int r24;
	unsigned int r25;
	unsigned int r26;
	unsigned int r27;

	unsigned int r0;
	unsigned int r1;
	unsigned int r2;
	unsigned int r3;
	unsigned int fp;
	unsigned int gp;
	unsigned int lp;
	unsigned int pc;
}RegSet;
