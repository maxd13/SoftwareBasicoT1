#include "converte.h"

int main(int argc, char const *argv[]){
    FILE *in = fopen("utf8_peq", "rb");
    FILE *out = fopen("saida", "wb");
    if(!in) return handle("Erro na leitura do arquivo utf8.\nO arquivo existe?\n");
    if(!out) return handle("Erro na escrita do arquivo varint.\nO arquivo existe?\n");
    utf_varint(in, out);
    if(ferror(in)) return handle("Erro na leitura do arquivo utf8.\n");
    if(ferror(out)) return handle("Erro na escrita do arquivo varint.\n");
    if(fclose(in)) return handle("Nao foi possivel fechar o arquivo utf8.\n");
    if(fclose(out)) return handle("Nao foi possivel fechar o arquivo varint.\n");
    return 0;
}
