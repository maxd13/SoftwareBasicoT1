/*
struct X {
  int val1;
  int val2;
};

int f(int i, int v);

void boo (struct X *px, int n, int val) {
  while (n--) {
    px->val2 = f(px->val1, val);
    px++;
  }
}
*/

.text
.globl boo
boo:
  pushq %rbp
  movq %rsp, %rbp
  subq $32, %rsp
  movq %rbx, -8(%rbp)
  movq %r12, -16(%rbp)
  movq %r13, -24(%rbp)

  movq %rdi, %rbx
  movl %esi, %r12d
  movl %edx, %r13d

loop:
  cmpl $0, %r12d
  je finish
  movl (%rbx), %edi
  movl %r13d, %esi
  call f
  movl %eax, 4(%rbx)
  addq $8, %rbx
  decl %r12d
  jmp loop


finish:
  movq -8(%rbp), %rbx
  movq -16(%rbp), %r12
  movq -24(%rbp), %r13
  leave
  ret



