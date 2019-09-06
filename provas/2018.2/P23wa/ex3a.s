.text
.globl acumula
acumula:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movsd 
movq $0, -8(%rbp) # double t
movl $0, -12(%rbp) # int i


loop:
movl -12(%rbp), %eax
cmpl %edi, %eax
jge finish
imull $8, %eax
addq %rsi, %rax
movsd (%rax), %xmm0
call verif
movl $0, %eax
cvtsi2sd %eax, %xmm1
ucomisd %xmm1, %xmm0
jbe incr
movl -12(%rbp), %eax
imull $8, %eax
addq %rsi, %rax
movsd (%rax), %xmm0
addsd -8(%rbp), %xmm0
movsd %xmm0, -8(%rbp) 

incr:
addl $1, -12(%rbp)
jmp loop

finish:
movq -8(%rbp), %rax
leave
ret

