#ifndef BENCHMARK_H
#define BENCHMARK_H

#endif // BENCHMARK_H

/* Файл с тестовыми данными и бенчмарками
*
*/

typedef struct {
    char * BENCHNAME;
    int MODLEN;
    unsigned int *MODULO;
    unsigned int *ELEMENT;
    unsigned int *EXPECTED;
    unsigned int *RESULT;

}BENCHCASE;






/*Тестовые данные малой длины
*/

//2^-1 mod 5
extern unsigned int PRIM_M5E2_M[1] = {5};
extern unsigned int PRIM_M5E2_E[1] = {2};
extern unsigned int PRIM_M5E2_I[1] = {3};
extern unsigned int PRIM_M5E2_RESULT[1] = {0};

extern const char NAME_2_5[] = "2^-1 MOD 5";
extern BENCHCASE BENCH_2_5 = {
    NAME_2_5,
    1,
    PRIM_M5E2_M,
    PRIM_M5E2_E,
    PRIM_M5E2_I,
    PRIM_M5E2_RESULT
};

//13^-1 mod 17
extern unsigned int PRIM_M17E14_M[1] = {17};
extern unsigned int PRIM_M17E14_E[1] = {14};
extern unsigned int PRIM_M17E14_I[1] = {11};
extern unsigned int PRIM_M17E14_RESULT[1] = {0};


extern const char NAME_13_17[] = "13^-1 MOD 17";
extern BENCHCASE BENCH_13_17 = {
    NAME_13_17,
    1,
    PRIM_M17E14_M,
    PRIM_M17E14_E,
    PRIM_M17E14_I,
    PRIM_M17E14_RESULT
};

//725^-1 mod 51971
extern unsigned int PRIM_M51971E725_M[1] = {51971};
extern unsigned int PRIM_M51971E725_E[1] = {725};
extern unsigned int PRIM_M51971E725_I[1] = {1362};
extern unsigned int PRIM_M51971E725_RESULT[1] = {0};


extern const char NAME_725_51971[] = "725^-1 MOD 51971";
extern BENCHCASE BENCH_725_51971 = {
    NAME_725_51971,
    1,
    PRIM_M51971E725_M,
    PRIM_M51971E725_E,
    PRIM_M51971E725_I,
    PRIM_M51971E725_RESULT
};



/*Тестовые данные
* ГОСТ 34.10-2018; Пример 2
* q, e, v = e^-1 mod q
* Длина - 256 бит
*/
extern unsigned int ECC_256_M [8] = {
    0x3ACCF5B3,
    0xC59CFC19,
    0x92976154,
    0x50FE8A18,
    0x00000001,
    0x00000000,
    0x00000000,
    0x80000000,
};

extern unsigned int ECC_256_E [8] = {
    0x2B043EE5,
    0x67ECE667,
    0xB1022E8E,
    0xCE52032A,
    0xE0EEC61F,
    0x88C09C52,
    0x72D89A11,
    0x2DFBC1B3,
};

extern unsigned int ECC_256_V [8] = {
    0x706354C2,
    0xFAC8F381,
    0x7BF945E5,
    0x9D3BA53C,
    0x64555BB2,
    0x423E3889,
    0x29F84EBC,
    0x271A4EE4,
};

extern unsigned int ECC_256_RES [8] = {0};

extern const char NAME_ECC_256[] = "ECC 256";

extern BENCHCASE BENCH_ECC_256 = {
    NAME_ECC_256,
    8,
    ECC_256_M,
    ECC_256_E,
    ECC_256_V,
    ECC_256_RES
};



/*Тестовые данные
* ГОСТ 34.10-2018; Пример 2
* q, e, v = e^-1 mod q
* Длина - 512 бит
*/

extern unsigned int ECC_512_M [16] = {
    0x87E6E6DF,
    0xD644AAF1,
    0xBE23C595,
    0xD86E25ED,
    0xECC423F1,
    0x19905C5E,
    0xCB1DBAC7,
    0xA82F2D7E,
    0xB5D2D15D,
    0xD4EB7C09,
    0xFFB90F04,
    0x922B14B2,
    0x6B2FEE80,
    0x550D267B,
    0xFE0023C7,
    0x4531ACD1
};

extern unsigned int ECC_512_E [16] = {
    0x72075B8C,
    0xC6777D29,
    0x1D560C4F,
    0x407ADEDB,
    0x647C5D5A,
    0x4339976C,
    0x6593F441,
    0x7184EE53,
    0x35B0C591,
    0xA71D1470,
    0xC170C533,
    0x1B09B6F9,
    0x4D8DAB53,
    0x5C4F4A7C,
    0xACC9E061,
    0x3754F3CF
};

extern unsigned int ECC_512_V [16] = {
    0xB3A840FF,
    0xFD504000,
    0x5721EC8C,
    0x4A55AD87,
    0x0A6DE0E1,
    0xA1999D5F,
    0x7B2F3448,
    0x4595EEC8,
    0x9BB47298,
    0x0AAF8BBD,
    0x82B6AD14,
    0x4D7EF4E7,
    0x2CADF3E6,
    0xA0F23853,
    0xE25D1A80,
    0x30D212A9
};

extern unsigned int ECC_512_RES [16] = {0};
extern const char NAME_ECC_512[] = "ECC 512";

extern BENCHCASE BENCH_ECC_512 = {
    NAME_ECC_512,
    16,
    ECC_512_M,
    ECC_512_E,
    ECC_512_V,
    ECC_512_RES
};


//Тест на большой M и маленький E, 256 бит


extern unsigned int SHORTELEM_256_E [8] = {
    0x3,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};

extern unsigned int SHORTELEM_256_V [8] = {
0x7C88A3CD, 0xD91352BB, 0x0C64EB8D, 0x35FF06BB, 0x55555556, 0x55555555, 0x55555555, 0x55555555
};

extern unsigned int SHORTELEM_256_RES [8] = {0};

extern const char NAME_ECC_256_SHORT[] = "ECC 256 SHORT ELEM";

extern BENCHCASE BENCH_SHORT_256 = {
    NAME_ECC_256_SHORT,
    8,
    ECC_256_M,
    SHORTELEM_256_E,
    SHORTELEM_256_V,
    SHORTELEM_256_RES
};





