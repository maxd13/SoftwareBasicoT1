/*
int main (void) {
  for(int i = 1; i < 11; i++) printf("%d\n", i*i);
  return 0;
}
*/

.data
Sf:  .string "%d\n"    /* primeira string de formato para printf */

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $8, %rsp
  movq    %rbx, -8(%rbp)  /* guarda rbx */
/********************************************************/

  movb $1, %bl  /* i = 0; */ 

L1:
  cmpb  $11, %bl  /* if (i == 11) ? */
  je  L2          /* goto L2 */

  movsbl %bl, %eax
  imull %eax, %eax

/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax) */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  movl  $0, %eax
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/


  incb %bl         /* i++; */
  jmp  L1         /* goto L1; */

L2:  

/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq    -8(%rbp), %rbx  /* recupera rbx */
  leave
  ret      
/***************************************************************/