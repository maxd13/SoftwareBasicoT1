  .data
  s1: .string "ls -ls"

  .text
  .globl main
  main:
  /* prologo */
    pushq %rbp
    movq  %rsp, %rbp
    movl  $-256, %eax
    sub  $4000, %rsp
    sub $2, %rax
    movl $100, -4(%rbp)
    movl $100, -8(%rbp)
    movl $100, -16(%rbp)
    movl $100, -256(%rbp)
    movl $100, (%rbp)
  /* coloque seu codigo aqui */
	movq $s1, %rdi
	call system



  /* finalizacao */
    leave
    ret

someotherBullshit:
    pushq %rbp
    movq  %rsp, %rbp
    leave
    ret
