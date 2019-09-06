

char struct_align(char* campos){
    char ret = 0;
    while(*campos) switch (*campos++)
    {
        case : 'c'
            ret = ret > 1 ? ret : 1;
            break;
        case : 's'
            ret = ret > 2 ? ret : 2;
            break;
        case : 'i'
            ret = ret > 3 ? ret : 3;
            break;
        case : 'l'
            ret = 4;
            break;
    
        default:
            return 0;
    }
    return ret;
}

int tamanho_struct(char* campos){

}