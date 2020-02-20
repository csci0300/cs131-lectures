	.file	"call05.c"
	.text
	.globl	_Z1flllllll
	.type	_Z1flllllll, @function
_Z1flllllll:
.LFB0:
	movl	%edi, a(%rip)
	movl	%esi, 4+a(%rip)
	movl	%edx, 8+a(%rip)
	movl	%ecx, 12+a(%rip)
	movl	%r8d, 16+a(%rip)
	movl	%r9d, 20+a(%rip)
	movq	8(%rsp), %rax
	movl	%eax, 24+a(%rip)
	ret
.LFE0:
	.size	_Z1flllllll, .-_Z1flllllll
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
