
	.globl syscall
syscall:
	syscall #7
	
	!smw.adm	$sp, [$sp], $sp, 2
	!la	$r0, check
	!jal	mputs
	!lmw.bim $sp, [$sp], $sp, 2

	jr	$lp

	.data
check:
	.asciz "this is systick\n"
	.align 4
