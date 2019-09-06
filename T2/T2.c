#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define _DEBUG //comment for release version.
#define CODE_SIZE 1048576 //1MB.

#ifdef _DEBUG
    void unit_test();
#endif

//handler de excecoes.
static void handle(const char* message, ...){
	va_list argptr;
	va_start(argptr, message);
	vfprintf(stderr, message, argptr);
	va_end(argptr);
	exit(EXIT_FAILURE);
}

static void error (const char *msg, int line) {
  handle("Erro: '%s' na linha %d\n", msg, line);
}

typedef int (*funcp) (int x);

//alloc gives number of bytes to alloc on top of the stack.
void perform_alloc(void* mcode, int* n, int alloc){
    *(mcode + (*n)++) = 0x48;
    *(mcode + (*n)++) = alloc < 0xFF ? 0x83 : 0x81;
    *(mcode + (*n)++) = 0xEC;
    for(int i = 0; i < 4; i++) *(mcode + *n + i) = (alloc >> i*8) & 0xFF;
    *n += 4;
}

void perform_function(void* mcode, int* n){
    *(mcode + (*n)++) = 0x55;
    *(mcode + (*n)++) = 0x48;
    *(mcode + (*n)++) = 0x89;
    *(mcode + (*n)++) = 0xe5;
}

void perform_return_constant(void* mcode, int* n, int value){
    *(mcode + (*n)++) = 0xb8;
    for(int i = 0; i < 4; i++) *(mcode + *n + i) = (value >> i*8) & 0xFF;
    *n += 4;
    *(mcode + (*n)++) = 0xc9;
    *(mcode + (*n)++) = 0xc3;
}

void perform_call(void* mcode, int* size){

}

void gera_codigo (FILE *f, void **code, funcp *entry){
    int n = 0;
    int line = 1;
    int c, c0, var0, var1, op;
    int fu, idx0, ixd1, idx2, 
    void* mcode = malloc(CODE_SIZE);
    if(!mcode) handle("Erro interno do compilador: falta de memória para alocar dados.\n");

    while ((c = fgetc(myfp)) != EOF) {
    switch (c) {
      case 'f': /* function */
        if (fscanf(myfp, "unction%c", &c0) != 1) error("comando invalido", line);
        perform_function(mcode, &n);
        break;
      case 'e': /* end */
        if (fscanf(myfp, "nd%c", &c0) != 1) error("comando invalido", line);
        break;
      case 'r': {  /* retorno incondicional */
        if (fscanf(myfp, "et %c%d", &var0, &idx0) != 2) error("comando invalido", line);
        printf("ret %c%d\n", var0, idx0);
        break;
      }
      case 'z': {  /* retorno condicional */
        int idx0, idx1;
        if (fscanf(myfp, "ret %c%d %c%d", &var0, &idx0, &var1, &idx1) != 4) 
          error("comando invalido", line);
        printf("zret %c%d %c%d\n", var0, idx0, var1, idx1);
        break;
      }
      case 'v': {  /* atribuicao */
        int idx0;
        char var0 = c, c0;
        if (fscanf(myfp, "%d = %c",&idx0, &c0) != 2)
          error("comando invalido",line);

        if (c0 == 'c') { /* call */
          int fu idx1;
          char var1;
          if (fscanf(myfp, "all %d %c%d\n", &fu &var1, &idx1) != 3)
            error("comando invalido",line);
          printf("%c%d = call %d %c%d\n",var0, idx0, fu var1, idx1);
        }
        else { /* operaÃ§Ã£o aritmÃ©tica */
          int idx1, idx2;
          char var1 = c0, var2, op;
          if (fscanf(myfp, "%d %c %c%d", &idx1, &op, &var2, &idx2) != 4)
            error("comando invalido", line);
          printf("%c%d = %c%d %c %c%d\n",
                var0, idx0, var1, idx1, op, var2, idx2);
        }
        break;
      }
      default: error("comando desconhecido", line);
    }
    line ++;
    fscanf(myfp, " ");
  }
}

void libera_codigo (void *p) {free(p);}


int main(int argc, char const *argv[]){
    FILE *myfp;
    char* arquivo = "programa";    

    if (!(myfp = fopen (arquivo, "r"))) handle("Erro de leitura: Nao foi possivel abrir arquivo solicitado.");
    return 0;
}
