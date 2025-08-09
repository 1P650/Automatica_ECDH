#include <stdio.h>
#include "multinv.h"
#include "hexutil.h"
#include "elliptic.h"

#define MODLEN 8
int main()
{

    //Модуль эллиптической кривой - взят из ГОСТ
    u32 MODULE [MODLEN] = {0x00000431, 0x00000000, 0x00000000, 0x00000000,
                     0x00000000, 0x00000000, 0x00000000, 0x80000000 };
    //Коэффициент a эллиптической кривой (y^2 = x^3 + ax + b) (ГОСТ)
    u32 A[MODLEN] = { 7, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0 };


    //Точка P эллиптической кривой (ГОСТ)
    u32 P_X[MODLEN] = {2,0,0,0,0,0,0,0};
    u32 P_Y[MODLEN] = {0xEA7E8FC8, 0x2B96ABBC, 0x9CA26712, 0x85C97F0A, 0x0E16D19C, 0xBD631603, 0xE65147D4, 0x08E2A8A0};


    // Номер варианта
    unsigned int t = 11;

    // x = 2^64 + 2^32 + t;   y = 2^65 + 2^31 + t
    //Закрытый ключ абонента А (x)
    u32 A_SecretKey[MODLEN] = {t, 1, 1};
    //Публичный ключ абонента A (= x*P)
    u32 A_PublicKey_X[MODLEN] = {0};
    u32 A_PublicKey_Y[MODLEN] = {0};

    //Общий ключ абонента A (нужен y*P)
    u32 A_SharedKey_X[MODLEN] = {0};
    u32 A_SharedKey_Y[MODLEN] = {0};

    //Закрытый ключ абонента B (y)
    u32 B_SecretKey[MODLEN] = {0x80000000 | t, 0, 2};
    //Публичный ключ абонента B (= y*P)
    u32 B_PublicKey_X[MODLEN] = {0};
    u32 B_PublicKey_Y[MODLEN] = {0};

    //Общий ключ абонента B (нужен x*P)
    u32 B_SharedKey_X[MODLEN] = {0};
    u32 B_SharedKey_Y[MODLEN] = {0};


    //Часть параметров эллиптической кривой
    CurveParams PARAMS = {A, MODLEN, MODULE};


    //Вывод параметров

    printf("Program params:\n");
    printf("Variant: %d\n", t);
    printf("Module: ");
    HEXUTIL_printHexLine(MODULE, MODLEN);
    printf("Coefficient A: ");
    HEXUTIL_printHexLine(A, MODLEN);
    printf("P point of elliptic curve (generator):\n");
    printf("P_X: ");
    HEXUTIL_printHexLine(P_X, MODLEN);
    printf("P_Y: ");
    HEXUTIL_printHexLine(P_Y, MODLEN);
    printf("\n----------------\n");
    printf("DIFFIE HELLMAN:");
    printf("\n----------------\n");
    //Проткол Диффи-Хеллмана
    printf("Alice secret key: ");
    HEXUTIL_printHexLine(A_SecretKey, MODLEN);

    printf("Alice public key:\n");
    //Вычисление x*P
    ELLIPTIC_MULNP(PARAMS, P_X, P_Y, A_SecretKey, A_PublicKey_X, A_PublicKey_Y);

    printf("A_X: ");
    HEXUTIL_printHexLine(A_PublicKey_X, MODLEN);
    printf("A_Y: ");
    HEXUTIL_printHexLine(A_PublicKey_Y, MODLEN);

    printf("Bob gets Alice public key.\n");
    printf("Bob calculates secret shared key:\n");

    //Вычисленеи y*(x*P)
    ELLIPTIC_MULNP(PARAMS, A_PublicKey_X, A_PublicKey_Y, B_SecretKey, B_SharedKey_X, B_SharedKey_Y);

    printf("Bob SharedKey_X: ");
    HEXUTIL_printHexLine(B_SharedKey_X, MODLEN);
    printf("Bob SharedKey_Y: ");
    HEXUTIL_printHexLine(B_SharedKey_Y, MODLEN);

    printf("\n----------------\n");

    printf("Bob secret key: ");
    HEXUTIL_printHexLine(B_SecretKey, MODLEN);

    printf("Bob public key:\n");
    //Вычисление y*P
    ELLIPTIC_MULNP(PARAMS, P_X, P_Y, B_SecretKey, B_PublicKey_X, B_PublicKey_Y);

    printf("B_X: ");
    HEXUTIL_printHexLine(B_PublicKey_X, MODLEN);
    printf("B_Y: ");
    HEXUTIL_printHexLine(B_PublicKey_Y, MODLEN);

    printf("Alice gets Alice public key.\n");
    printf("Alice calculates secret shared key:\n");

    //Вычисление x*(y*P)
    ELLIPTIC_MULNP(PARAMS, B_PublicKey_X, B_PublicKey_Y, A_SecretKey, A_SharedKey_X, A_SharedKey_Y);

    printf("Alice SharedKey_X: ");
    HEXUTIL_printHexLine(A_SharedKey_X, MODLEN);
    printf("Alice SharedKey_Y: ");
    HEXUTIL_printHexLine(A_SharedKey_Y, MODLEN);

    printf("\n----------------\n");
    printf("SHARED KEY IS:\n");
    printf("SharedKey_X: ");
    HEXUTIL_printHexLine(A_SharedKey_X, MODLEN);
    printf("SharedKey_Y: ");
    HEXUTIL_printHexLine(B_SharedKey_Y, MODLEN);

    return 0;
}
