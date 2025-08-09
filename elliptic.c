#include "arifm.h"
#include "elliptic.h"
//Сложение точки с собой
int ELLIPTIC_ADD_XX(const CurveParams CURVE_PARAMS, u32 *P_X, u32 *P_Y, u32 *DEST_X, u32 *DEST_Y){
    u32 *mod = CURVE_PARAMS.mod;
    u32 modlen = CURVE_PARAMS.modlen;
    u32 *a = CURVE_PARAMS.a;

    u32 *MEMORY = malloc(modlen * 3 * sizeof(u32));
    memset(MEMORY, 0, modlen*3*sizeof(u32));

    u32 *lambda = MEMORY;
    u32 *buffer1 = lambda + modlen;
    u32 *buffer2 = buffer1 + modlen;

    buffer1[0] = 3;

    //lambda
    // x <- x*x
    umn_mod(modlen, P_X, P_X, mod, lambda);
    umn_mod(modlen, lambda, buffer1, mod, lambda);

    sum_mod(modlen, lambda, a, mod, lambda);
    sum_mod(modlen, P_Y, P_Y, mod, buffer1);
    MULTINV_EGCD(modlen, buffer1, mod, buffer1);
    umn_mod(modlen, lambda, buffer1, mod, lambda);

    //x_r
    umn_mod(modlen, lambda, lambda, mod, buffer1);
    raz_mod(modlen, buffer1, P_X, mod, buffer1);
    raz_mod(modlen, buffer1, P_X, mod, buffer1);
    //y_r
    raz_mod(modlen, P_X, buffer1, mod, buffer2);
    umn_mod(modlen, buffer2, lambda, mod, buffer2);
    raz_mod(modlen, buffer2, P_Y, mod, buffer2);

    memcpy(DEST_X, buffer1, modlen*sizeof(u32));
    memcpy(DEST_Y, buffer2, modlen*sizeof(u32));

    free(MEMORY);
}


//Сложение двух разных точек
int ELLIPTIC_ADD_XY(const CurveParams CURVE_PARAMS, u32 *P_X, u32 *P_Y, u32 *Q_X, u32 *Q_Y, u32 *DEST_X, u32 *DEST_Y){

    u32 *mod = CURVE_PARAMS.mod;
    u32 modlen = CURVE_PARAMS.modlen;
    u32 *a = CURVE_PARAMS.a;

    u32 *MEMORY = malloc(modlen * 6 * sizeof(u32));
    memset(MEMORY, 0, modlen*6*sizeof(u32));

    u32 *lambda = MEMORY;
    u32 *buffer1 = lambda + modlen;
    u32 *buffer2 = buffer1 + modlen;

    //lambda
    raz_mod(modlen, Q_X, P_X, mod, buffer2);
    raz_mod(modlen, Q_Y, P_Y, mod, lambda);
    MULTINV_EGCD(modlen, buffer2, mod, buffer2);
    umn_mod(modlen, lambda, buffer2, mod, lambda);

    //x_r
    umn_mod(modlen, lambda, lambda, mod, buffer1);
    raz_mod(modlen, buffer1, P_X, mod, buffer1);
    raz_mod(modlen, buffer1, Q_X, mod, buffer1);

    //y_r
    raz_mod(modlen, P_X, buffer1, mod, buffer2);
    umn_mod(modlen, buffer2, lambda, mod, buffer2);
    raz_mod(modlen, buffer2, P_Y, mod, buffer2);

    memcpy(DEST_X, buffer1, modlen*sizeof(u32));
    memcpy(DEST_Y, buffer2, modlen*sizeof(u32));

    free(MEMORY);
}

//Кратная точка n*P
int ELLIPTIC_MULNP(const CurveParams CURVE_PARAMS, u32 *P_X, u32 *P_Y, u32 * n, u32 *DEST_X, u32 *DEST_Y){
    u32 modlen = CURVE_PARAMS.modlen;

    u32 *MEMORY = malloc(modlen*2*sizeof(u32));
    memset(MEMORY, 0, modlen*2*sizeof(u32));

    u32 *T_PX = MEMORY;
    u32 *T_PY = T_PX + modlen;

    memcpy(T_PX, P_X, modlen*sizeof(u32));
    memcpy(T_PY, P_Y, modlen*sizeof(u32));

    int E_FB = first_bit(modlen, n);
    for(int i = E_FB-1; i>=0; --i)
    {
        ELLIPTIC_ADD_XX(CURVE_PARAMS, T_PX, T_PY, T_PX, T_PY);
        if(((n[i/32]>>(i%32))&1)==1)
        {
            ELLIPTIC_ADD_XY(CURVE_PARAMS, T_PX, T_PY, P_X, P_Y, T_PX, T_PY);
        }
    }
    memcpy(DEST_X, T_PX, modlen*sizeof(u32));
    memcpy(DEST_Y, T_PY, modlen*sizeof(u32));
    free(MEMORY);
}
