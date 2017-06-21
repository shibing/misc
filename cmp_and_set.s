	.file	"cmp_and_set.c"
	.globl	d
	.bss
	.align 4
	.type	d, @object
	.size	d, 4
d:
	.zero	4
	.text
	.globl	cmp_and_set
	.type	cmp_and_set, @function
cmp_and_set:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	movq	-32(%rbp), %rsi
	movl	-36(%rbp), %edx
	movq	-24(%rbp), %rcx
#APP
# 10 "cmp_and_set.c" 1
	lock;cmpxchgl %edx, (%rcx);movl %eax, (%rsi);sete %al;
# 0 "" 2
#NO_APP
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	cmp_and_set, .-cmp_and_set
	.globl	incr
	.type	incr, @function
incr:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	nop
.L4:
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	leaq	-4(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cmp_and_set
	testl	%eax, %eax
	je	.L4
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	incr, .-incr
	.globl	run
	.type	run, @function
run:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	movl	$d, %edi
	call	incr
	addl	$1, -4(%rbp)
.L6:
	cmpl	$5999999, -4(%rbp)
	jle	.L7
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	run, .-run
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	-8(%rbp), %rax
	movl	$0, %ecx
	movl	$run, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create
	leaq	-16(%rbp), %rax
	movl	$0, %ecx
	movl	$run, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create
	movq	-8(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join
	movq	-16(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join
	movl	$0, %eax
	call	run
	movl	d(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.3.1 20170306"
	.section	.note.GNU-stack,"",@progbits
