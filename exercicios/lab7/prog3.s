/*

int nums[4] = {65, -105, 111, 34};

int main (void) {
  int i;
  int s = 0;

  for (i=0;i<4;i++)
    s = s+nums[i];

  printf ("soma = %d\n", s);

  return 0;
}
*/

.data
nums: .int 65, -105, 111, 34
Sf:  .string "soma = %d\n"    /* primeira string de formato para printf */

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
/********************************************************/

  movb $0, %bl  /* i = 0; */
  movl $0, %eax /* s = 0; */

L1:
  cmpb  $4, %bl  /* if (i == 4) ? */
  je  L2          /* goto L2 */

  movsbq %bl, %rcx
  imulq $4, %rcx
  addq $nums, %rcx /* ecx e' o endereco de nums[i] */
  addl (%rcx), %eax

  incb %bl         /* i++; */
  jmp  L1         /* goto L1; */

L2:

/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax) */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  movl  $0, %eax
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/ 

/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq    $0, %rax  /* rax = 0  (valor de retorno) */
  leave
  ret      
/***************************************************************/