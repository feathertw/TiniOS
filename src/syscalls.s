	.globl syscall
syscall:
	syscall #0x8
	
	!smw.adm	$sp, [$sp], $sp, 2
	!la	$r0, check
	!jal	mputs
	!lmw.bim $sp, [$sp], $sp, 2

	jr	$lp

	.globl fork
fork:
	syscall #0x1
	jr	$lp

	.globl getpid
getpid:
	syscall #0x2
	jr	$lp

	.globl read
read:
	syscall #0x3
	jr	$lp

	.globl write
write:
	syscall #0x4
	jr	$lp

	.data
check:
	.asciz "this is systick\n"
	.align 4
