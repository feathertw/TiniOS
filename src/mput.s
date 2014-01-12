	.equ UART_BASE, 0x02000000
	.equ UART_ENABLE_OFFSET,   0x00000000
	.equ UART_TX_FLAG_OFFSET,  0x00000010
	.equ UART_RX_FLAG_OFFSET,  0x00000014
	.equ UART_TX_DATA_OFFSET,  0x00000020
	.equ UART_RX_DATA_OFFSET,  0x00000024
	.equ UART_BAUDRATE_OFFSET, 0x00000030

	.globl	init_mput
init_mput:
	smw.adm	$r1, [$sp], $r2, 0
	la	$r1, UART_BASE
	swi	$r0, [$r1+UART_BAUDRATE_OFFSET]
	movi	$r2, #1
	swi	$r2, [$r1+UART_ENABLE_OFFSET]
	lmw.bim	$r1, [$sp], $r2, 0
	jr	$lp

	.globl	mputn
mputn:
	smw.adm	$r1, [$sp], $r2, 2

	bgez	$r0, us_n
	subri	$r1, $r0, #0
	la	$r0, '-'
	jal	mputc
	addi	$r0, $r1, #0
us_n:
	movi	$r2, #0
conti_ns:
	addi	$r1, $r0, #0
	jal	mod_u10
	swi	$r0, [$sp+(#-4)]
	addi	$sp, $sp, #-4
	addi	$r2, $r2, #1
	addi	$r0, $r1, #0
	jal	div_u10
	bnez	$r0, conti_ns

conti_nl:
	lwi	$r0, [$sp+#0]
	addi	$sp, $sp, #4
	addi	$r0, $r0, #48
	jal	mputc
	addi	$r2, $r2, #-1
	bnez	$r2, conti_nl

	lmw.bim	$r1, [$sp], $r2, 2
	jr	$lp

	.globl mputs
mputs:
	smw.adm	$r1, [$sp], $r3, 2
	addi	$r1, $r0, #0
	la	$r2, #0xFFFFFFFC
conti:
	and	$r3, $r1, $r2
	lwi	$r0, [$r3+#0]
	andi	$r3, $r1, #0x3
	slli	$r3, $r3, #3
	srl	$r0, $r0, $r3
	andi	$r0, $r0, #0xFF
	beqz	$r0, fini
	jal	mputc
	addi	$r1, $r1, #1
	j	conti
fini:
	lmw.bim	$r1, [$sp], $r3, 2
	jr	$lp


	.globl	mputc
mputc:	
	smw.adm	$r1, [$sp], $r2, 0
	la	$r1, UART_BASE
wait:
	lwi	$r2, [$r1+UART_TX_FLAG_OFFSET]
	bnez	$r2, wait
	swi	$r0, [$r1+UART_TX_DATA_OFFSET]
	movi	$r2, #1
	swi	$r2, [$r1+UART_TX_FLAG_OFFSET]
	lmw.bim	$r1, [$sp], $r2, 0
	jr	$lp
