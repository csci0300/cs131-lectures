	.file	"call03.c"
	.text
	.globl	_Z1fllllll
	.type	_Z1fllllll, @function
_Z1fllllll:
.LFB0:
	movq	%rdi, -8(%rsp)
	movq	%rsi, -16(%rsp)
	movq	%rdx, -24(%rsp)
	movq	%rcx, -32(%rsp)
	movq	%r8, -40(%rsp)
	movq	%r9, -48(%rsp)
	movq	-8(%rsp), %rax
	movl	%eax, a(%rip)
	movq	-16(%rsp), %rax
	movl	%eax, 4+a(%rip)
	movq	-24(%rsp), %rax
	movl	%eax, 8+a(%rip)
	movq	-32(%rsp), %rax
	movl	%eax, 12+a(%rip)
	movq	-40(%rsp), %rax
	movl	%eax, 16+a(%rip)
	movq	-48(%rsp), %rax
	movl	%eax, 20+a(%rip)
	nop
	ret
.LFE0:
	.size	_Z1fllllll, .-_Z1fllllll
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
