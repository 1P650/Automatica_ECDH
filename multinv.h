#ifndef MULTINV_H
#define MULTINV_H

typedef unsigned int u32;
typedef unsigned long long u64;

/* Вычисление обратного в GF(p) с помощью EGCD
* elem - ptr на элемент поля
* modulo - ptr на порядок поля
* inverse - ptr на обратный элемент поля
*/
int MULTINV_EGCD(int modlen, u32 * elem, u32 * mod, u32 * inverse);


/* Вычисление обратного в GF(p) с помощью ~бинарного EGCD
 * elem - ptr на элемент поля
 * modulo - ptr на порядок поля
 * inverse - ptr на обратный элемент поля
 * кажется работает быстрее однако не является идеально оптимизированным вариантом
 */
int MULTINV_EBGCD(int modlen, u32 * elem, u32 * mod, u32 * inverse);

/* Вычисление обратного в GF(p) с помощью бинарного EGCD
 * elem - ptr на элемент поля
 * modulo - ptr на порядок поля
 * inverse - ptr на обратный элемент поля
 * немногим другая версия эквивалентная по производительности
 */

int MULTINV_EBGCD2(int modlen, u32 * elem, u32 * mod, u32 * dest);

/* Возведение в степень с помощью повторного возведения в квадрат
*/
void MULTINV_SQPOW(int modlen, u32 * elem, u32 * pow, u32 * mod, u32 * pw);

/* Вычисление обратного в GF(p) с помощью малой теоремы Ферма; sqpow
 * elem - ptr на элемент поля
 * modulo - ptr на порядок поля
 * inverse - ptr на обратный элемент поля
*/
int MULTINV_FERMAT_SQPOW(int modlen, u32 * elem, u32 * mod, u32 * inverse);

/* Вычисление обратного в GF(p) с помощью малой теоремы Ферма; Монтгомери
 * На 26.11.24 22:34 заменена оптимизированной
 * elem - ptr на элемент поля
 * modulo - ptr на порядок поля
 * inverse - ptr на обратный элемент поля
*/
int MULTINV_FERMAT_MONPOW(int modlen, u32 * elem, u32 * mod, u32 * inverse);

/* Вычисление обратного в GF(p) с помощью малой теоремы Ферма; Монтгомери, оптимизированное умножение
 * elem - ptr на элемент поля
 * modulo - ptr на порядок поля
 * inverse - ptr на обратный элемент поля
*/
// int MULTINV_FERMAT_MONPOW_OPT(int modlen, u32 * elem, u32 * mod, u32 * inverse);


#endif // MULTINV_H
