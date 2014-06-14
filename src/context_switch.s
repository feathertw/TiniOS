	.globl	to_kernel_mode
to_kernel_mode:
	!la	$r0, tkm_check
	!jal	mputs
	mfsr	$r0, $P_P1
	smw.adm	$r3, [$r0], $r27, 0
	addi	$r0, $r0, #-4

	lmw.bim $r1, [$sp], $r27, 14
	jr	$lp

	.globl to_user_mode
to_user_mode:
	smw.adm	$r1, [$sp], $r27, 14

	movi	$r1, #1
	mtsr	$r1, $PSW
	mtsr	$r1, $IPSW

	addi	$sp, $r0, #8
	lmw.bim $r4, [$sp], $r27,  0

	!la	$r0, tum_check
	!jal	mputs

	iret

	.data
tkm_check:	
	.asciz "THIS IS TO KERNEL MODE\n"
	.align 4
tum_check:	
	.asciz "THIS IS TO USER MODE\n"
	.align 4
