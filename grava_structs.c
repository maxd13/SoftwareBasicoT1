#include "grava_structs.h"
//we assume a little endian architecture.
int grava_structs (int nstructs, void *valores, char *campos, char ord, char *arquivo){
	int multiplier = 1;
	char* s = campos;
    unsigned char n = 0;
    void* i;
    int  j;
    int size;
    FILE* out;
	while(*s){
		if(*s == 'l') multiplier = 8;
        else if(*s == 'i' && multiplier < 4) multiplier = 4;
        else if(*s == 's' && multiplier < 2) multiplier = 2;
        s++;
        n++;
	}
    size = n*multiplier;
    out = fopen(arquivo, "wb");    
    if(!out) return -1;
    fprintf(out, "%c", (unsigned int) nstructs);
    fprintf(out, "%c", (ord == 'L'? 128 : 0) + n);



    for(i = valores; i < valores + nstructs*size; i += size){
        s = campos;
        while(*s){

        }


    }
}
void dump_structs (char *arquivo);
