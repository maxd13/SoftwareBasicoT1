#include "grava_structs.h"
struct s {
    int i1;
    long l1;
    short s1;
    char c1;
    short s2;
  };

struct s2 {
    long l1;
    char c1;
    long l2;
    int s1;
  };


int main(int argc, char const *argv[])
{
    struct s exemplo[4] = {// cada campo de tamanho n tem o valor do succesor do maior valor do tipo anterior.
                           {65536, 4294967296, 256, 128, 256}, 
                           //primeiros n/2 bytes de cada campo sao 0xFF.
                           {65535, 4294967295, 255, 255, 255},
                           //tudo com o maior valor possivel. Todos os bytes 0xFF.
                           {4294967295, 0xFFFFFFFFFFFFFFFF, 65535, 255, 65535},
                           //tudo 0.
                           {0, 0, 0, 0, 0}
                          };

    struct s2 exemplo2[3] = {//tudo 80
                             {0x8080808080808080, 128, 0x8080808080808080, 0x80808080},
                             {1, 2, 3, 4},
                             //0xFF em posicoes pares do primeiro long, 0xFF na diagonal depois, o resto 0.
                             {0xFF00FF00FF00FF00, 0xFF, 0xFF << 8,0xFF << 8*2}
                            };

    //espera-se o mesmo resultado mostrado independente da arquitetura escolhida, 
    //mas os arquivos devem estar diferentes.
    grava_structs(4, exemplo, "ilscs", 'B', "saida");
    grava_structs(4, exemplo, "ilscs", 'L', "saidaL");
    grava_structs(3, exemplo2, "lcli", 'L', "saida2L");
    printf("saida:\n");
    dump_structs("saida");
    printf("\nsaidaL:\n");
    dump_structs("saidaL");
    printf("\nsaida2L:\n");
    dump_structs("saida2L");


    return 0;
}
