/* Luiz Carlos Rumbelsperger Viana 1810936 3WB */
#include <math.h>
#include <stdlib.h>
#include "grava_structs.h"

//retorna o tamanho do tipo.
unsigned char field_size(char c){
    switch(c){
        case 'c': return 1;
        case 's': return 2;
        case 'i': return 4;
        case 'l': return 8;
    }
    return 0;
}

//converte de little endian para big endian e vice-versa.
unsigned char reverseBits(unsigned char num){ 
    unsigned char count = sizeof(num) * 8 - 1; 
    unsigned char reverse_num = num; 
      
    num >>= 1;  
    while(num) 
    { 
       reverse_num <<= 1;        
       reverse_num |= num & 1; 
       num >>= 1; 
       count--; 
    } 
    reverse_num <<= count; 
    return reverse_num; 
}

int grava_structs (int nstructs, void *valores, char *campos, char ord, char *arquivo){
	unsigned char max = 1;
	char* s = campos;
    unsigned char n = 0;
    unsigned char c = 0;
    unsigned char* i;
    unsigned char* l;
    int  j, k;
    int size = 0;
    FILE* out;
    //oter o tamanho do struct e numero de campos.
	while(*s){
        c = field_size(*s);
        //adiciona os bytes de c ao tamanho, com o padding necessario.
        if(size % c == 0) size += c;
        else size += 2*c - (size % c);
        //obtem o tamanho maximo de um campo
        if(max < c) max = c;
        //padding no final
        if(!*(s+1) && size % max != 0) size += max - (size % max);
        s++;
        n++;
	}
    //abrir arquivo e escrever header, byte por byte.
    out = fopen(arquivo, "wb");    
    if(!out) return -1;
    fprintf(out, "%c", (unsigned char) nstructs);
    fprintf(out, "%c", (ord == 'L'? 128 : 0) + n);
    c = 0;
    //escreve representacao dos valores no header.
    for(j = 0; j < n; j += 4){
        for(k = 0; k < (n - j < 4 ? n - j : 4); k++)
            switch (campos[j+k]){
                case 's':
                    c += 1 << (6 - 2*k);
                    break;
                case 'i':
                    c += 2 << (6 - 2*k);
                    break;
                case 'l':
                    c += 3 << (6 - 2*k);
                    break;
                default:
                    continue;
            }
        fprintf(out, "%c", c);
        c = 0;
    }

    //coloca os valores armazenados no struct no arquivo.
    i = (unsigned char*)valores;
    while(i < (unsigned char*) (valores + nstructs*size)){
        s = campos;
        //tratar proximo struct.
        while(*s){
            c = field_size(*s);
            if((i - (unsigned char*)valores) % c == 0){
                //inserir bytes do campo no arquivo.
                for(l = i; l < i+c; l++)
                    fprintf(out, "%c", (ord == 'L' ? reverseBits(*l) : *l) );
                i += c;
            }
            else{
                //pular bytes de padding.
                i += c - ((i - (unsigned char*)valores) % c);
                continue;
            }
            //pular padding no final
            if(!*(s+1) && (i - (unsigned char*)valores) % max != 0) i += max - ((i - (unsigned char*)valores) % max);
            s++;
        }
    }
    
    return fclose(out);
}

void dump_structs (char *arquivo){
    unsigned char architecture = 0;
    unsigned char nstructs = 0;
    unsigned char nfields = 0;
    unsigned char nbytes = 0;
    unsigned char* fields;
    unsigned char c = 0;
    unsigned char i, j, loop;
    FILE* in;
    in = fopen(arquivo, "rb");
    if(!in){
        printf("Erro ao ler o arquivo.\n");
        return;
    }
    nstructs = (unsigned char) fgetc(in);
    architecture = (unsigned char) fgetc(in);

    nfields = architecture >= 128 ? architecture - 128 : architecture;
    architecture = architecture >= 128 ? 'L' : 'B';
    nbytes = (unsigned char) ceilf(2*nfields/8.0);
    fields = (unsigned char*) malloc(nfields);
    if(!fields){
        printf("Erro ao alocar memoria.\n");
        return;
    }

    //le tipos de campo.
    loop = 0;
    for(i = 0; i < nbytes; i++){
        c = (unsigned char) fgetc(in);
        for(j = 0; j < 4; j++){
            if(loop >= nfields) break;
            //isso mapeia 'c' para 1, 's' para 2, 'i' para 4 e 'l' para 8.
            fields[loop++] = (unsigned char) powf(2, (c >> (6 - 2*j)) & 3);
        }
    }

    printf("%c\n", architecture);
    printf("%d\n", nstructs);
    
    //imprime os structs.
    for(i = 0; i < nstructs; i++){
        printf("*\n");
        for(j = 0; j < nfields; j++){
            for(loop = 0; loop < fields[j]; loop++){
                c = (unsigned char) fgetc(in);
                //usado para que a saida final represente os bytes em
                //little endian caso tenha sido escritos desse modo.
                //isso gera uma saida mais parecida com a entrada,
                //apesar de que o efeito e' puramente cosmetico.
                //E.g. caso se tenha um campo char com valor 128,
                //ele sera impresso como 80, o que e' a sua representacao hexadecimal correta.
                //caso este comando seja omitido, seria impresso 01, que é 128 little endian.
                c = architecture == 'L' ? reverseBits(c) : c;
                printf("%02X ", c);
            }
            printf("\n");
        }
    }

    free(fields);
    fclose(in);
}