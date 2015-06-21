	.file	"code.c"
	.text
.globl _sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	addl	%eax, _accum
	popl	%ebp
	ret
.globl _accum
	.bss
	.align 4
_accum:
	.space 4
