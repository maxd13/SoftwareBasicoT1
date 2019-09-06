/* 

int foo(long v1[], int *pi, int n) {
    int i;
    for (i = 0; i < n; i++, pi++) {
        if (*pi < n) {
            v1[*pi] = 0;
        }
    }
}
*/

.text
foo:

  /* prologo */
  pushq %rbp
  movq %rsp, %rbp
  subq $8, %rsp
  movq %r12, -8(%rbp)

  movl $0, %eax # i = 0

FOR:
  cmpl $edx, %eax # i < n
  jge ENDFOR

  compl %edx, (%rsi) # if (*pi < n)
  jge INC

  movl (%rsi), %r12
  imulq $8, %r12
  addq %rdi, %r12 # %r12 = &v1[*pi]

  movq $0, (%r12)

INC:
  incl %eax # i++
  incl %rsi # pi++
  jmp FOR

ENDFOR:
  movq $0, %rax
  movq -8(%rbp), %r12
  leave
  ret