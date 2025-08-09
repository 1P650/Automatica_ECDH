#ifndef HEXUTIL_H
#define HEXUTIL_H

void HEXUTIL_printHex(void * memory, int c){
    int i;
    unsigned int *p = (unsigned int *)memory;
    for (i=0;i<c;i++) {
        printf("0x%08X ", p[i]);
        if ((i%16==0) && i)
            printf("\n");
    }
    printf("\n");
}

void HEXUTIL_printHexLine(void * memory, int c){
    int i;
    unsigned int *p = (unsigned int *)memory;
    for (i=c-1;i>=0;i--) {
        printf("%08x", p[i]);
        if ((i%16==0) && i)
            printf("\n");
    }
    printf("\n");
}


#endif // HEXUTIL_H
