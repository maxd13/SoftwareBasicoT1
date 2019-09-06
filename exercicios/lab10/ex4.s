/* int f(int x);

void map2 (int* um, int * outro, int n) {
  int i;
  for (i=0; i<n; i++)
    *(outro+i) = f(*(um+i));
}
*/

.text
.globl map2
map2:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)
    movq %r14, -32(%rbp)

    movq %rdi, %rbx
    movq %rsi, %r12
    movl %edx, %r13d
    movl $0, %r14d

loop:
    cmpl %r13d, %r14d
    je finish
    movslq %r14d, %rdi # rdi = i
    imulq $4, %rdi # rdi = 4*i
    addq %rbx, %rdi # rdi = um + i
    movl (%rdi), %edi # edi = *(um + i)
    call f
    movslq %r14d, %rdi
    imulq $4, %rdi
    addq %r12, %rdi # rdi = outro + i
    movl %eax, (%rdi) # *(outro + i) = eax
    incl %r14d
    jmp loop

finish:
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    movq -24(%rbp), %r13
    movq -32(%rbp), %r14
    leave
    ret

