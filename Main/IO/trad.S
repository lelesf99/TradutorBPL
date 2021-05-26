# TRADUÇÂO:
.section .rodata
.data
.text
.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp
	subq $32, %rsp
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)
	leave
	ret
.globl f2
f2:
	pushq %rbp
	movq %rsp, %rbp
	subq $64, %rsp
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)
	leave
	ret
.globl f3
f3:
	pushq %rbp
	movq %rsp, %rbp
	subq $96, %rsp
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)
	leave
	ret
