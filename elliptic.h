#ifndef ELLIPTIC_H
#define ELLIPTIC_H

#include "multinv.h"
/* Функции для работы с эллиптическими кривыми */

/* Структура с параметрами кривой - параметр A, модуль, размер модуля*/
typedef struct{
    //Curve Params
    u32 *a;
    //Field params
    u32 modlen;
    u32 *mod;
} CurveParams;



/* Сложение точки с собой
* CURVE_PARAMS - параметры кривой
* P_X, P_Y - координаты точки
* DEST_X, DEST_Y - указатели на точку для записи результата
*/
int ELLIPTIC_ADD_XX(const CurveParams CURVE_PARAMS, u32 *P_X, u32 *P_Y, u32 *DEST_X, u32 *DEST_Y);


/* Сложение двух разных точек
* CURVE_PARAMS - параметры кривой
* P_X, P_Y - координаты первой точки
* Q_X, Q_Y - координаты второй точки
* DEST_X, DEST_Y - указатели на точку для записи результата
*/
int ELLIPTIC_ADD_XY(const CurveParams CURVE_PARAMS, u32 *P_X, u32 *P_Y, u32 *Q_X, u32 *Q_Y, u32 *DEST_X, u32 *DEST_Y);

/* Вычисление кратной точки n*P
* CURVE_PARAMS - параметры кривой
* P_X, P_Y - координаты точки
* n - множитель; сколько раз точку сложить с собой
* DEST_X, DEST_Y - указатели на точку для записи результата
*/
int ELLIPTIC_MULNP(const CurveParams CURVE_PARAMS, u32 *P_X, u32 *P_Y, u32 * n, u32 *DEST_X, u32 *DEST_Y);

#endif // ELLIPTIC_H
