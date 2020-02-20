	.file	"call07.c"
	.text
	.globl	_Z1fll
	.type	_Z1fll, @function
_Z1fll:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, a(%rip)
	movq	-16(%rbp), %rax
	movq	%rax, 8+a(%rip)
	nop
	popq	%rbp
	ret
.LFE0:
	.size	_Z1fll, .-_Z1fll
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
