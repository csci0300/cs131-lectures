	.file	"call06.c"
	.text
	.globl	_Z1fllllllll
	.type	_Z1fllllllll, @function
_Z1fllllllll:
.LFB0:
	movl	%edi, a(%rip)
	movl	%esi, 4+a(%rip)
	movl	%edx, 8+a(%rip)
	movl	%ecx, 12+a(%rip)
	movl	%r8d, 16+a(%rip)
	movl	%r9d, 20+a(%rip)
	movq	8(%rsp), %rax
	movl	%eax, 24+a(%rip)
	movq	16(%rsp), %rax
	movl	%eax, 28+a(%rip)
	ret
.LFE0:
	.size	_Z1fllllllll, .-_Z1fllllllll
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
