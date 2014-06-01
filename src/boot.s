
	.equ STACK_ADDR, 0x01001000

	.section "vectors"
_start:
	j	Reset_Handler
	j	Syscall_Handler
	j	Systick_Handler
	.word
	.word
	.word
	.word
	.word

Reset_Handler:

init_data:
	la	$r0, _etext
	la	$r1, _sdata
	la	$r2, data_size
	la	$r3, #0x000000FF
copy_data:
	beqz	$r2, init_bss
	lwi.bi	$r4, [$r0], #4

	addi	$r5, $r4, #0
	and	$r4, $r4, $r3

	slli	$r4, $r4, #8
	srli	$r5, $r5, #8
	and	$r6, $r5, $r3
	or	$r4, $r4, $r6

	slli	$r4, $r4, #8
	srli	$r5, $r5, #8
	and	$r6, $r5, $r3
	or	$r4, $r4, $r6

	slli	$r4, $r4, #8
	srli	$r5, $r5, #8
	and	$r6, $r5, $r3
	or	$r4, $r4, $r6


	swi.bi	$r4, [$r1], #4
	addi	$r2, $r2, #-4
	j	copy_data

init_bss:
	la	$r0, _sbss
	la	$r1, bss_size
zero_bss:
	beqz	$r1, init_sp
	movi	$r2, #0
	swi.bi	$r2, [$r0], #4
	addi	$r1, $r1, #-4
	j	zero_bss

init_sp:
	la	$sp, STACK_ADDR

	la	$r0, boot_check
	jal	mputs
	!syscall #7
	j	main

Syscall_Handler:
	!la	$r0, syscall_check
	!jal	mputs
	la	$lp, to_kernel_mode
	jr	$lp
	!iret

Systick_Handler:
	#j	new_systick_handler
	movi	$r0, '@'
	jal	mputc
	#la	$r0, systick_check
	#jal	mputs
	iret

	.text
loop:	j	loop

	.data
boot_check:	.asciz "THIS IS BOOT\n"
syscall_check:	.asciz "THIS IS SYSCALL\n"
systick_check:	.asciz "THIS IS SYSTICK\n"
	.align 4
