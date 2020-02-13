	.file	"asm14.c"
	.text
	.globl	_Z1fii
	.type	_Z1fii, @function
_Z1fii:
.LFB0:
	cmpl	%esi, %edi
	jl	.L3
	movl	%edi, %eax
	ret
.L3:
	movl	$0, %eax
	ret
.LFE0:
	.size	_Z1fii, .-_Z1fii
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
