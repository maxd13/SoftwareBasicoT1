  .data
  nums: .int 3, -5, 7, 8, -2
  s1:   .string "%d\n"

  .text
  .globl main
  main:
  /* prologo */
     pushq %rbp
     movq  %rsp, %rbp
     subq  $16, %rsp
     movq  %rbx, -8(%rbp)
     movq  %r12, -16(%rbp)

  /* coloque seu codigo aqui */
  movl  $0, %ebx  /* ebx = 0; i */
  movq  $nums, %r12  /* r12 = &nums */

L1:
  cmpl  $5, %ebx  /* if (ebx == 5) ? */
  je  L2          /* goto L2 */


/*************************************************************/
/* este trecho chama a funcao filtro */
  movl    (%r12), %edi     /* primeiro parametro (inteiro)*/
  movl    $1, %esi      /* segundo parametro  (inteiro) */
  call    filtro       /* chama a funcao da biblioteca */
/*************************************************************/



/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $s1, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/



  addl  $1, %ebx  /* ebx += 1; */
  addq  $4, %r12  /* r12 += 4; */
  jmp  L1         /* goto L1; */

L2:  

  /* finalizacao */
     movq -8(%rbp), %rbx
     movq -16(%rbp), %r12
     leave
     ret
