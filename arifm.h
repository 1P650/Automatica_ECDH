#ifndef _ARIFM_H
#define _ARIFM_H

#define MAXLEN 33
#define BIT_INT 32
#define LOG_BIT_INT 5
#define MASK_INT 0xffffffff
#define MASK_INT_C 0x100000000l


////////////////////////////////////////////////////////////////////
// функции для работы с большими числами
// len - размер чисел в словах
// максимальный размер чисел - MAXLEN
////////////////////////////////////////////////////////////////////

// умножение a на b, результат в c
void umn(int len, unsigned int *a, unsigned int *b, unsigned int *c);

// порядковый номер старшей единицы в числе a
int first_bit(int len, unsigned int *a);

// сравнение a c b
// результат: 0 - равны, 1 - a больше b, -1 - a меньше b
int cmp(int len, unsigned int *a, unsigned int *b);

// сложение a и b, результат в c
void sum(int len, unsigned int *a, unsigned int *b, unsigned int *c);

// вычитание b из a, результат в c
void minus(int len, unsigned int * a, unsigned int * b, unsigned int * c);

// сложение a и b по модулю p, результат в c
void sum_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c);

// вычитание b из a по модулю p, результат в c
void raz_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c);

// приведение a (длины n1 слов) по модулю p(длины n2 слов)
void mod_p(unsigned int * a, int n1, unsigned int * p, int n2);

// произведение a на b по mod p, результат в c
void mulp(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c);

// сдвиг a на k бит влево, результат в c
void shift_l(int k, int len, unsigned int * a, unsigned int * c);

// сдвиг a на k бит вправо, результат в c
void shift_r(int k, int len, unsigned int * a, unsigned int * c);

// изменение знака числа c
void change_sign(int len, unsigned int * c);

// целая часть от деление a на b, результат в c
int div(int len, unsigned int * a, unsigned int * b, unsigned int * c);

// побитовое и
void binop_and(int a_n, int b_n, unsigned int* a, unsigned int *b, unsigned int *c);


// сложение a и b с переносом?, результат в c
void sum_ext(int n_a, int n_b, unsigned int *a, unsigned int *b, unsigned int *c);

#endif
