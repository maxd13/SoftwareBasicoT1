/* struct X {
  int val;
  struct X *next;
};

int add (struct X *x) {
  int a = 0;
  for (; x != NULL; x = x->next)
    a += x->val;
  return a;
}

int add2 (struct X *x) {
  if (x == NULL) return 0;
  else return x->val + add2(x->next);
}

 */



.text
.globl add
.globl add2
add:
    movl $0, %eax
loop:
    cmpq $0, %rdi
    je finish
    addl (%rdi), %eax
    movq 8(%rdi), %rdi
    jmp loop

finish:
    ret

add2:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rbx, -8(%rbp)

    movl $0, %eax
    cmpq $0, %rdi
    je finish2
    movq %rdi, %rbx
    movq 8(%rdi), %rdi
    call add2
    addl (%rbx), %eax


finish2:
    movq -8(%rbp), %rbx
    leave
    ret
