	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_getNextActiveTache
	.align	4, 0x90
_getNextActiveTache:                    ## @getNextActiveTache
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	movl	$0, -12(%rbp)
	movl	$0, -20(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$20, -20(%rbp)
	jge	LBB0_8
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	_tblActiveTache@GOTPCREL(%rip), %rax
	movslq	-20(%rbp), %rcx
	imulq	$56, %rcx, %rcx
	addq	%rcx, %rax
	movl	28(%rax), %edx
	cmpl	-12(%rbp), %edx
	jle	LBB0_4
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	_tblActiveTache@GOTPCREL(%rip), %rax
	movslq	-20(%rbp), %rcx
	imulq	$56, %rcx, %rcx
	addq	%rcx, %rax
	movl	28(%rax), %edx
	movl	%edx, -12(%rbp)
	movl	-20(%rbp), %edx
	movl	%edx, -16(%rbp)
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	_tblActiveTache@GOTPCREL(%rip), %rax
	movslq	-20(%rbp), %rcx
	imulq	$56, %rcx, %rcx
	addq	%rcx, %rax
	cmpl	$3, 40(%rax)
	jne	LBB0_6
## BB#5:
	movl	-20(%rbp), %eax
	movl	%eax, _ptrLastActiveTache(%rip)
	jmp	LBB0_8
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_7
LBB0_7:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB0_1
LBB0_8:
	cmpl	$0, -12(%rbp)
	jne	LBB0_10
## BB#9:
	movq	$0, -8(%rbp)
	jmp	LBB0_11
LBB0_10:
	movq	_tblActiveTache@GOTPCREL(%rip), %rax
	movslq	-20(%rbp), %rcx
	imulq	$56, %rcx, %rcx
	movq	%rax, %rdx
	addq	%rcx, %rdx
	movl	32(%rdx), %esi
	movslq	-20(%rbp), %rcx
	imulq	$56, %rcx, %rcx
	movq	%rax, %rdx
	addq	%rcx, %rdx
	movl	%esi, 28(%rdx)
	movslq	-20(%rbp), %rcx
	imulq	$56, %rcx, %rcx
	addq	%rcx, %rax
	movq	%rax, -8(%rbp)
LBB0_11:
	movq	-8(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_pushActiveTache
	.align	4, 0x90
_pushActiveTache:                       ## @pushActiveTache
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$56, %eax
	movl	%eax, %edx
	movq	_tblActiveTache@GOTPCREL(%rip), %rcx
	movq	%rdi, -8(%rbp)
	movl	_ptrLastActiveTache(%rip), %eax
	addl	$1, %eax
	movl	%eax, _ptrLastActiveTache(%rip)
	movq	-8(%rbp), %rdi
	movl	$1, 40(%rdi)
	movslq	_ptrLastActiveTache(%rip), %rdi
	imulq	$56, %rdi, %rdi
	addq	%rdi, %rcx
	movq	-8(%rbp), %rdi
	movq	%rdi, -16(%rbp)         ## 8-byte Spill
	movq	%rcx, %rdi
	movq	-16(%rbp), %rsi         ## 8-byte Reload
	callq	_memcpy
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_pushSleepingTache
	.align	4, 0x90
_pushSleepingTache:                     ## @pushSleepingTache
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp6:
	.cfi_def_cfa_offset 16
Ltmp7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp8:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$56, %eax
	movl	%eax, %edx
	movq	_tblSleepingTache@GOTPCREL(%rip), %rcx
	movq	%rdi, -8(%rbp)
	movl	_ptrLastSleepingTache(%rip), %eax
	addl	$1, %eax
	movl	%eax, _ptrLastSleepingTache(%rip)
	movq	-8(%rbp), %rdi
	movl	$2, 40(%rdi)
	movslq	_ptrLastSleepingTache(%rip), %rdi
	imulq	$56, %rdi, %rdi
	addq	%rdi, %rcx
	movq	-8(%rbp), %rdi
	movq	%rdi, -16(%rbp)         ## 8-byte Spill
	movq	%rcx, %rdi
	movq	-16(%rbp), %rsi         ## 8-byte Reload
	callq	_memcpy
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_idle
	.align	4, 0x90
_idle:                                  ## @idle
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp9:
	.cfi_def_cfa_offset 16
Ltmp10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp11:
	.cfi_def_cfa_register %rbp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_scheduler
	.align	4, 0x90
_scheduler:                             ## @scheduler
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp12:
	.cfi_def_cfa_offset 16
Ltmp13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp14:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	$0, -8(%rbp)
	movq	$0, -16(%rbp)
LBB4_1:                                 ## =>This Inner Loop Header: Depth=1
	callq	_getNextActiveTache
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	LBB4_3
## BB#2:                                ##   in Loop: Header=BB4_1 Depth=1
	callq	_idle
LBB4_3:                                 ##   in Loop: Header=BB4_1 Depth=1
	cmpq	$0, -8(%rbp)
	je	LBB4_8
## BB#4:                                ##   in Loop: Header=BB4_1 Depth=1
	movq	-8(%rbp), %rax
	cmpl	$1, 40(%rax)
	jne	LBB4_6
## BB#5:                                ##   in Loop: Header=BB4_1 Depth=1
	movq	-8(%rbp), %rax
	movl	28(%rax), %ecx
	addl	$-1, %ecx
	movl	%ecx, 28(%rax)
	movq	-8(%rbp), %rdi
	callq	_pushActiveTache
	jmp	LBB4_7
LBB4_6:                                 ##   in Loop: Header=BB4_1 Depth=1
	movq	-8(%rbp), %rdi
	callq	_pushSleepingTache
LBB4_7:                                 ##   in Loop: Header=BB4_1 Depth=1
	jmp	LBB4_8
LBB4_8:                                 ##   in Loop: Header=BB4_1 Depth=1
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB4_1
	.cfi_endproc

	.globl	_ptrLastActiveTache     ## @ptrLastActiveTache
.zerofill __DATA,__common,_ptrLastActiveTache,4,2
	.globl	_ptrLastSleepingTache   ## @ptrLastSleepingTache
.zerofill __DATA,__common,_ptrLastSleepingTache,4,2
	.comm	_tblActiveTache,1120,4  ## @tblActiveTache
	.comm	_tblSleepingTache,1120,4 ## @tblSleepingTache

.subsections_via_symbols
