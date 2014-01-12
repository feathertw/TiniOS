
	.globl div_u10
div_u10:
	smw.adm	$r1, [$sp], $r2, 0
	srli	$r1, $r0, #1
	srli	$r2, $r0, #2
	add	$r1, $r1, $r2
	srli	$r2, $r1, #4
	add	$r1, $r1, $r2
	srli	$r2, $r1, #8
	add	$r1, $r1, $r2
	srli	$r2, $r1, #16
	add	$r1, $r1, $r2
	srli	$r1, $r1, #3
	slli	$r2, $r1, #2
	add	$r2, $r2, $r1
	slli	$r2, $r2, #1
	sub	$r2, $r0, $r2
	addi	$r0, $r2, #6
	srli	$r0, $r0, #4
	add	$r0, $r1, $r0
	lmw.bim	$r1, [$sp], $r2, 0
	jr	$lp

	.globl	mul_u10
mul_u10:
	smw.adm	$r1, [$sp], $r1, 0
	slli	$r1, $r0, #2
	add	$r0, $r1, $r0
	slli	$r0, $r0, #1
	lmw.bim	$r1, [$sp], $r1, 0
	jr	$lp

	.globl	mod_u10
mod_u10:
	smw.adm	$r1, [$sp], $r1, 2
	addi	$r1, $r0, #0
	jal	div_u10
	jal	mul_u10
	sub	$r0, $r1, $r0
	lmw.bim	$r1, [$sp], $r1, 2
	jr	$lp
