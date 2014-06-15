#define TASK_READY	0x0
#define TASK_WAIT_READ	0x1
#define TASK_WAIT_WRITE	0x2
#define TASK_READ	0x3
#define TASK_WRITE	0x4

#define PIPE_NUM_LIMIT	16

#define SYSTICK_CONTROL 	*(volatile int *)(0x0E100000)
#define SYSTICK_RELOAD_VALUE 	*(volatile int *)(0x0E100004)
#define SYSTICK_STATUS	 	*(volatile int *)(0x0E101000)
#define SYSTICK_CURRENT_VALUE 	*(volatile int *)(0x0E101004)
#define SYSTICK_CONTROL_ENABLE       1
#define SYSTICK_CONTROL_CLEAR        2
#define SYSTICK_CONTROL_CONTINUOUS   4

