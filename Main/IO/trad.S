# TRADUÇÂO:
.section .rodata
.data
.text
.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp
	subq $48, %rsp
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)
#	vi1 = -36(%rbp)

	movl %edi, %r12d
	movl %esi, %r13d

#	5 vi1 = pi1 + pi2 
	movl $1, %r8d
	movl $2, %r8d
	addl %r9d, %r8d
	movl %r8d, -36(%rbp)

#	6 return vi1 
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)

	movl -36(%rbp), %eax

	leave
	ret

.globl f2
f2:
	pushq %rbp
	movq %rsp, %rbp
	subq $48, %rsp
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)
#	vi1 = -36(%rbp)
#	vi2 = -40(%rbp)
#	vi3 = -44(%rbp)
#	vi4 = -48(%rbp)

	movq %rdi, %r12

#	15 get pa1 index ci0 to vi1 
	movq %r12, %r9
	movq $0, %r8
	imulq $4, %r8
	addq %r9, %r8
	movl (%r8), %r9d
	movl %r9d, -36(%rbp)

#	16 get pa1 index ci1 to vi2 
	movq %r12, %r9
	movq $1, %r8
	imulq $4, %r8
	addq %r9, %r8
	movl (%r8), %r9d
	movl %r9d, -40(%rbp)

#	17 vi3 = vi1 + vi2 
	movl -36(%rbp), %r8d
	movl -40(%rbp), %r9d
	addl %r9d, %r8d
	movl %r8d, -44(%rbp)

#	18 get pa1 index ci2 to vi1 
	movq %r12, %r9
	movq $2, %r8
	imulq $4, %r8
	addq %r9, %r8
	movl (%r8), %r9d
	movl %r9d, -36(%rbp)

#	19 vi3 = vi3 + vi1 
	movl -44(%rbp), %r8d
	movl -36(%rbp), %r9d
	addl %r9d, %r8d
	movl %r8d, -44(%rbp)

#	20 get pa1 index ci3 to vi1 
	movq %r12, %r9
	movq $3, %r8
	imulq $4, %r8
	addq %r9, %r8
	movl (%r8), %r9d
	movl %r9d, -36(%rbp)

#	21 vi3 = vi3 + vi1 
	movl -44(%rbp), %r8d
	movl -36(%rbp), %r9d
	addl %r9d, %r8d
	movl %r8d, -44(%rbp)

#	22 get pa1 index ci4 to vi1 
	movq %r12, %r9
	movq $4, %r8
	imulq $4, %r8
	addq %r9, %r8
	movl (%r8), %r9d
	movl %r9d, -36(%rbp)

#	23 vi3 = vi3 + vi1 
	movl -44(%rbp), %r8d
	movl -36(%rbp), %r9d
	addl %r9d, %r8d
	movl %r8d, -44(%rbp)

#	24 return vi3 
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)

	movl -44(%rbp), %eax

	leave
	ret

.globl f3
f3:
	pushq %rbp
	movq %rsp, %rbp
	subq $64, %rsp
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)
#	va1 = -52(%rbp)
#	vi2 = -56(%rbp)

	movq %rdi, %r12

#	31 vi2 = call f2 pa1 
	movq %r12, %rdi
	call f2
	movl %eax, -56(%rbp)

#	32 if vi2 
	cmpl $0, -56(%rbp)
	je endif32

#	33 return vi2 
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)

	movl -56(%rbp), %eax

	leave
	ret

#	34 endif 
endif32:

#	35 return ci-1 
	movq %r12, -8(%rbp)
	movq %r13, -16(%rbp)
	movq %r14, -24(%rbp)
	movq %r15, -32(%rbp)

	movl $-1, %eax

	leave
	ret

