	.equ UART_BASE, 0x02000000
	.equ UART_TX_ENABLE_OFFSET, 0x00000000
	.equ UART_RX_ENABLE_OFFSET, 0x00000004
	.equ UART_TX_FLAG_OFFSET,   0x00000010
	.equ UART_RX_FLAG_OFFSET,   0x00000014
	.equ UART_TX_DATA_OFFSET,   0x00000020
	.equ UART_RX_DATA_OFFSET,   0x00000024
	.equ UART_BAUDRATE_OFFSET,  0x00000030

	.globl	mgets
mgets:
	smw.adm	$r1, [$sp], $r6, 0
	la	$r1, UART_BASE
	movi	$r2, #1
	swi	$r2, [$r1+UART_RX_ENABLE_OFFSET]

	movi	$r2, #0
	movi	$r3, #0x0a
	movi	$r6, #0
conti:
	lwi	$r4, [$r1+UART_RX_FLAG_OFFSET]
	beqz	$r4, conti
	addi	$r6, $r6, #1
	lwi	$r5, [$r1+UART_RX_DATA_OFFSET]
	swi	$r2, [$r1+UART_RX_FLAG_OFFSET]
	andi	$r5, $r5, #0xFF

	swi.bi	$r5, [$r0], #4
	bne	$r5, $r3, conti
	addi	$r0, $r0, #-4
	movi	$r5, #0
	swi.bi	$r5, [$r0], #4
	addi	$r0, $r6, #0

	lmw.bim	$r1, [$sp], $r6, 0
	jr	$lp


	.globl	mgetn
mgetn:
	smw.adm	$r1, [$sp], $r6, 2
	la	$r1, UART_BASE
	movi	$r2, #1
	swi	$r2, [$r1+UART_RX_ENABLE_OFFSET]
	movi	$r2, #0
	movi	$r3, #0x0a
	movi	$r6, #0
nconti:
	lwi	$r4, [$r1+UART_RX_FLAG_OFFSET]
	beqz	$r4, nconti
	lwi	$r5, [$r1+UART_RX_DATA_OFFSET]
	swi	$r2, [$r1+UART_RX_FLAG_OFFSET]
	andi	$r5, $r5, #0xFF
	beq	$r5, $r3, nfini
	addi	$r0, $r6, #0
	jal	mul_u10
	addi	$r5, $r5, #-48
	add	$r6, $r0, $r5
	j	nconti
nfini:
	addi	$r0, $r6, #0
	lmw.bim	$r1, [$sp], $r6, 2
	jr	$lp
