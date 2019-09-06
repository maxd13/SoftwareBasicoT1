/*

#define NULL 0

struct X {
  int val;
  long valc;
  struct X *next;
};

int abs(int j);
long calc(int x);

void boo(struct X *px, int *v) {
  while (px != NULL) {
    px->val = *v;
    px->valc = calc(abs(*v));
    px = px->next;
    v++;
  }
}

*/

.text
BOO:
/* prologo */
  pushq %rbp
  movq %rsp, %rbp
  subq $16, %rsp
  movq %r12, -8(%rbp)
  movq %rbx, -16(%rbp)

  movq %rdi, %rbx
  movq %rsi, %r12

WHILE:
  cmpq $0, %rbx
  je END

  movl (%r12), %eax # eax = *v
  movl %eax, (%rbx) # px->val = *v;

  
  movl %eax, %rdi
  call abs
  movl %eax, %rdi
  call calc
  movq %rax, 8(%rbx) # px->valc = calc(abs(*v));

  movq 16(%rbx), %rbx
  incl %r12

END:
  movq $0, %rax
  movq -8(%rbp), %r12
  movq -16(%rbp), %rbx
  leave
  ret