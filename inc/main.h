#define SYSTICK_CONTROL 	*(volatile int *)(0x0E100000)
#define SYSTICK_RELOAD_VALUE 	*(volatile int *)(0x0E100004)
#define SYSTICK_STATUS	 	*(volatile int *)(0x0E101000)
#define SYSTICK_CURRENT_VALUE 	*(volatile int *)(0x0E101004)
#define SYSTICK_CONTROL_ENABLE       1
#define SYSTICK_CONTROL_CLEAR        2
#define SYSTICK_CONTROL_CONTINUOUS   4

