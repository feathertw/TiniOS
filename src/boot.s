	.equ UART_ENABLE,   0x02000000
	.equ UART_TX_FLAG,  0x02000010
	.equ UART_RX_FLAG,  0x02000014
	.equ UART_TX_DATA,  0x02000020
	.equ UART_RX_DATA,  0x02000024
	.equ UART_BAUDRATE, 0x02000030

	.equ STACK_ADDR, 0x01001000

	.text
	.globl _start
_start:
	la	$sp, STACK_ADDR
	la	$r0, 'H'
	jal	mputc

	!movi	$r0, #12
	!movi	$r0, #12345
	!movi	$r0, #0
	movi	$r0, #-12345
	!jal	div_u10
	!jal	mod_u10
	jal	mputn

	la	$r0, '\n'
	jal	mputc

	la	$r0, hello
	jal	mputs
	!j	loop
	j	main
loop:	j	loop
!
!	la	$r0, UART_BAUDRATE
!	movi	$r1, #9600
!	swi	$r1, [$r0+#0]
!	la	$r0, UART_ENABLE
!	movi	$r1, #1
!	swi	$r1, [$r0+#0]
!
!	la	$r5, UART_TX_FLAG
!	la	$r6, UART_TX_DATA
!	movi	$r7, #1
!	movi	$r8, #0x3
!	la	$r9, #0xFFFFFFFC
!
!	la	$r0, hello
!	jal	put
!
!	j	loop
!	j	main
!
!	.globl	put
!put:	
!	and	$r2, $r0, $r8
!	and	$r1, $r0, $r9
!	lwi	$r1, [$r1+#0]
!	slli	$r2, $r2, #3
!	srl	$r1, $r1, $r2
!	andi	$r1, $r1, #0xFF
!	bnez	$r1, put_wait
!	jr	$lp
!
!put_wait:
!	lwi	$r2, [$r5+#0]
!	bnez	$r2, put_wait
!	swi	$r1, [$r6+#0]
!	swi	$r7, [$r5+#0]
!	addi	$r0, $r0, #1
!	j	put
!
!loop:	j	loop

	.data
hello:	.asciz "HELLO! THIS IS BOOT\n"
	.byte 0
	.align
