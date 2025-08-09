/* ПОИСК ОБРАТНОГО ЭЛЕМЕНТА
 *
 * Поиск обратного элемента в поле GF(p) или Z/pZ
 *  * Предполагается, что модуль - ТОЛЬКО ПРОСТОЕ ЧИСЛО
 *  * Предполагается, что элемент приведен по модулю
 *  * На данный момент наибольший размер числа, так или иначе проверенный - 512 бит.
 *
 *
 * Реализация в большинстве случаев с помощью предложенной библиотеки
 * Для работы с большими числами - aripfm.h
 *
 * Реализованные алгоритмы для поиска обратного:
 * 1) Расширенный алгоритм Евклида
 * * функция - MULTINV_EGCD
 * 2) Расширенный Бинарный алгоритм Евклида (неоптимизированный)
 * * функция - MULTINV_EBGCD или MULTINV_EBGCD_constTime
 * 3) Малая теорема Ферма;
 * * функция через возведение в квадрат - MULTINV_FERMAT_SQPOW
 * * функция через умножение Монтгомери - MULTINV_FERMAT_MONPOW или MULTINV_FERMAT_MONPOW_OPT
 *
 */

 /* Составляющие программы:
 * * Файл main.c
 * * * Смена бенчмарка через указатель CURRBENCH
 * * * Смена алгоритма через указатель INVERSE
 * * * Функциональный тест через флаг CHECK_INV
 * * * Среднее время выполнения функции через флаг DO_BENCHMARK
 * *
 * * Файлы arifm.c, arifm.h - библиотека + модификации к ней
 * *
 * * Файлы multinv.c и multinv.h
 * * * Содержат реализации алгоритмов
 * *
 * * Файл montgomery.h
 * * * Содержит функции для умножения Монтгомери
 * *
 * * Файл benchmark.h
 * * * содержит тестовые вектора
 * * Файл hexutil.h
 * * * Пока содержит только функцию печати массива
 */


#include <stdio.h>
#include <time.h>

#include "arifm.h"
#include "multinv.h"
#include "hexutil.h"

#include "benchmark.h"

// Проверка умножением на исходный
#define CHECK_INV 1
//Простой замер времени выполнения
#define DO_BENCHMARK 0

// Запуск бенчмарка
void BENCHMARK_RUN(int (*INVERSE)(int, u32*, u32*, u32*), BENCHCASE *CURRBENCH, int CHECK_INVERSE, int MEASURE){
    int f = INVERSE(CURRBENCH->MODLEN, CURRBENCH->ELEMENT, CURRBENCH->MODULO, CURRBENCH->RESULT);
    printf("MODULO = ");
    HEXUTIL_printHex(CURRBENCH->MODULO, CURRBENCH->MODLEN);
    printf("ELEMENT = ");
    HEXUTIL_printHex(CURRBENCH->ELEMENT, CURRBENCH->MODLEN);
    printf("EXPECTED = ");
    HEXUTIL_printHex(CURRBENCH->EXPECTED, CURRBENCH->MODLEN);
    printf("RESULT = ");
    HEXUTIL_printHex(CURRBENCH->RESULT, CURRBENCH->MODLEN);

    if(CHECK_INVERSE){
        unsigned int *MUL = malloc(sizeof(unsigned int) * CURRBENCH->MODLEN);
        mulp(CURRBENCH->MODLEN, CURRBENCH->RESULT, CURRBENCH->ELEMENT, CURRBENCH->MODULO, MUL);
        printf("\n\n[---CHECK INVERSE---]:\n\nELEM*RESULT = ");
        HEXUTIL_printHex(MUL, CURRBENCH->MODLEN);
        free(MUL);
    }

    if(MEASURE){
        unsigned long long i = 0;
        double sum = 0;

        int REPETITIONS = 5;

        for(int j = 0; j < REPETITIONS; ++j){
            clock_t t1 = clock();
            for(i = 0; ; ++i){
                int f = INVERSE(CURRBENCH->MODLEN, CURRBENCH->ELEMENT, CURRBENCH->MODULO, CURRBENCH->RESULT);
                clock_t t2 = clock();
                double time_spent = (double)(t2 - t1) / CLOCKS_PER_SEC;
                if(2 - time_spent < 0) break;

            }
            sum += i;
        }

        double q = (double) sum / REPETITIONS;



        printf("\n\n[---MEAUSRE: TIME AVERAGE = %f ;---]\n\n",q);
    }
}
int main()
{
    const int (*ALGS[])(int, u32*, u32*, u32*) = {
        MULTINV_EGCD,
        MULTINV_EBGCD2 ,
        MULTINV_FERMAT_SQPOW,
        MULTINV_FERMAT_MONPOW
    };

    const char* ALGNAMES []= {
        "EGCD",
        "BINARY EGCD",
        "FERMAT SQPOW",
        "FERMAT MONTGOMERY"
    };

    const BENCHCASE *BENCHCASES[] = {
        &BENCH_2_5,
        &BENCH_13_17,
        &BENCH_725_51971,
        &BENCH_ECC_256,
        &BENCH_SHORT_256,
        &BENCH_ECC_512
    };

    BENCHCASE *CURRBENCH;
    int ALGS_COUNT = sizeof(ALGS)/sizeof(ALGS[0]);
    int BENCH_COUNT = sizeof(BENCHCASES)/sizeof(BENCHCASES[0]);

    for(int i = 0; i < ALGS_COUNT; ++i){
        printf("\n\n[!!!------RUNNING BENCHS FOR %s------!!!]\n\n", ALGNAMES[i]);
        for(int j = 0; j< BENCH_COUNT; ++j){
            printf("\n[----RUNNING BENCH: %s----]\n", BENCHCASES[j]->BENCHNAME);
            BENCHMARK_RUN(ALGS[i], BENCHCASES[j], CHECK_INV, DO_BENCHMARK);
        }
    }





    return 0;
}
