#include <stdarg.h>
#include "converte.h"

unsigned int int_to_varint(unsigned int value){

    return value;
}

unsigned int int_to_utf8(unsigned int value){

    return value;
}

//exception handler.
int handle(const char* message, ...){
	va_list argptr;
	va_start(argptr, message);
	vfprintf(stderr, message, argptr);
	va_end(argptr);
	return -1; //exit(EXIT_FAILURE);
}

int utf_varint(FILE *arq_entrada, FILE *arq_saida){
    unsigned char read = fgetc(arq_entrada);
    unsigned int value;
    unsigned char n;
    char i;
    while (read != EOF){
        //validate input.
        //if char read begins with 10 we have a problem.
        if((read & 0xC0) == 0x80) return handle("1 : Formato invalido na leitura do arquivo utf8.\n");
        if (read >= 128){
            n = 0;
            // count the number of leading 1s.
            do{n++; read = read << 1;}
            while(read & 0x80);
            printf("n : %d\n", n);
            read = read << 1; // remove leading 0
            value = read << (6*(n - 1) - n - 1); //allocate enough space for the rest.
            for(i = n - 2; i >= 0; i--){
                printf("value : %x\n", value);
                read = fgetc(arq_entrada);
                //if we reach the end of the file or char read doesn't begin with 10, we have a problem.
                if(read == EOF || (read & 0xC0) != 0x80) return handle("Formato invalido na leitura do arquivo utf8.\n");
                read = read << 2; //remove leading 10.
                if (value == 0) value = read << (17 + n);
                else value |= read << 8*i;
            }
        }
        else value = read;
        value = int_to_varint(value);
        do{
            n = value & 0xFF;
            fputc(n, arq_saida);
            value = value >> 8;
        } while (value != 0);
       read = fgetc(arq_entrada); 
    }
    return 0;
}
int varint_utf(FILE *arq_entrada, FILE *arq_saida);