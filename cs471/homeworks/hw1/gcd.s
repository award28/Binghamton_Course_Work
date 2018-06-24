	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_gcdI
	.p2align	4, 0x90
_gcdI:                                  ## @gcdI
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:					## 	1. The creation of the stack frame.
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp	##	2. Argument storage and updates.
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	je	LBB0_6			## 4. Translation of the loop.
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	-4(%rbp), %eax		
	cmpl	-8(%rbp), %eax
	jle	LBB0_4
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	-4(%rbp), %eax
	subl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)		##	3. Local variable storage and updates.
	jmp	LBB0_5
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	-8(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, -8(%rbp)		##	3. Local variable storage and updates.
LBB0_5:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_1
LBB0_6:					## 5. Some form of return result, and an exit from the function.
	movl	-4(%rbp), %eax
	popq	%rbp
	retq				

	.cfi_endproc


.subsections_via_symbols
