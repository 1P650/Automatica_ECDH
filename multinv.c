#include "arifm.h"
#include "multinv.h"
#include "montgomery.h"

// Поиск обратного в поле GF(p); Расширенный Алгоритм Евклида
int MULTINV_EGCD(int modlen, u32 * elem, u32 * mod, u32 * dest){
    u32 *MEMORY = malloc( (modlen*2 + (2*modlen+1)*7) * sizeof (u32));
    memset(MEMORY, 0, (modlen*2 + (2*modlen+1)*7) * sizeof (u32));


    u32 *a = MEMORY;
    u32 *b = a + modlen;

    u32 *k = b + modlen;
    u32 *r = k + 2*modlen+1;

    u32 *s1 = r + 2*modlen+1;
    u32 *s2 = s1 + 2*modlen+1;

    u32 *zero = s2 + 2*modlen+1;
    u32 *s_tmp = zero + 2*modlen+1;

    s2[0] = 0x1;

    memcpy(b, mod, modlen*sizeof(u32));
    memcpy(a,elem,modlen*sizeof(u32));

    zero[0] = 1;

    while(cmp(modlen, a, zero) != 0){
         divu(modlen, b, a, k);
         mod_p(b, modlen, a, modlen);
         u32 *swp = a;
         a = b;
         b = swp;
         umn(2*modlen+1, k, s2, s_tmp);
         minus(2*modlen+1, s1, s_tmp, s_tmp);
         memcpy(s1, s2, (2*modlen+1)*sizeof(u32));
         memcpy(s2, s_tmp, (2*modlen+1)*sizeof(u32));
    }

    if(s2[2*modlen] & 0x80000000 != 0){
        sum_ext(2*modlen+1,modlen, s2, mod, s2);
    }
    memcpy(dest,s2, modlen*sizeof(u32));
    free(MEMORY);
    return 0;
}


// Поиск обратного в поле GF(p); Расширенный Бинарный Алгоритм Евклида
int MULTINV_EBGCD(int modlen, u32 * elem, u32 * mod, u32 * dest){
    u32* MEMORY = malloc(modlen * sizeof(u32) * 8);
    memset(MEMORY, 0, modlen * sizeof (u32) * 8);
    u32* a = MEMORY;
    u32* b = a + modlen;

    u32* s1 = b + modlen;
    u32* s2 = s1 + modlen;

    u32* zero = s2 + modlen;

    u32* twoinv = zero + modlen;

    memcpy(a, elem, modlen*sizeof(u32));
    memcpy(b, mod, modlen*sizeof(u32));

    s1[0] = 1;

    //calculate 2^-1 mod m
    sum(modlen, mod, s1, twoinv);
    shift_r(1, modlen, twoinv, twoinv);


    while(cmp(modlen, a,zero)!=0){
        if(a[0]%2){
            if(cmp(modlen, a, b) == -1){
                u32* swap = a;
                a = b;
                b = swap;

                swap = s1;
                s1 = s2;
                s2 = swap;
            }
            minus(modlen, a, b, a);
            raz_mod(modlen, s1, s2, mod,s1);
        }
        shift_r(1, modlen, a, a);
        umn_mod(modlen, s1, twoinv, mod, s1);
    }

    memcpy(dest,s2, modlen*sizeof(u32));
    free(MEMORY);
    return 0;
}

// Поиск обратного в поле GF(p); Расширенный Бинарный Алгоритм Евклида; работает немногим быстрее
int MULTINV_EBGCD2(int modlen, u32 * elem, u32 * mod, u32 * dest){
    u32* MEMORY = malloc(modlen * sizeof(u32) * 8);
    memset(MEMORY, 0, modlen * sizeof (u32) * 8);
    u32* a = MEMORY;
    u32* b = a + modlen;

    u32* s1 = b + modlen;
    u32* s2 = s1 + modlen;

    u32* zero = s2 + modlen;

    u32* twoinv = zero + modlen;

    memcpy(a, elem, modlen*sizeof(u32));
    memcpy(b, mod, modlen*sizeof(u32));

    s1[0] = 1;

    //calculate 2^-1 mod m
    sum(modlen, mod, s1, twoinv);
    shift_r(1, modlen, twoinv, twoinv);

    int BITS = first_bit(modlen, mod)+1;


    //int BITS = modlen*8;

    for(int i = 1; i<=2*BITS-1; ++i){
        if(a[0]%2 != 0){
            if(cmp(modlen, a, b) == -1){
                u32* swap = a;
                a = b;
                b = swap;

                swap = s1;
                s1 = s2;
                s2 = swap;
            }
            minus(modlen, a, b, a);
            raz_mod(modlen, s1, s2, mod,s1);
        }
        shift_r(1, modlen, a, a);
        umn_mod(modlen, s1, twoinv, mod, s1);
    }

    memcpy(dest,s2, modlen*sizeof(u32));
    free(MEMORY);
    return 0;
}


//~Быстрое возведение в степень по модулю (по сути квадрат-умнож)
void MULTINV_SQPOW(int modlen, u32 *elem, u32 *pow, u32 *mod, u32 *pw){
    u32 *MEMORY = malloc(modlen*sizeof(u32)*4);
    memset(MEMORY,0, modlen*sizeof(u32)*4);

    u32 *a = MEMORY;
    u32 *e = a + modlen;
    u32 *r = e + modlen;
    u32 *zero = r + modlen;
    r[0] = 1;

    memcpy(a, elem, modlen*sizeof(u32));
    memcpy(e, pow, modlen*sizeof(u32));

    int E_FB = first_bit(modlen, e);
    for(int i = 0; i<=E_FB; ++i){
        if(((e[i/32]>>(i%32))&1)==1 ){
            umn_mod(modlen, r, a, mod, r);
        }
        umn_mod(modlen, a ,a, mod, a);

    }
    memcpy(pw, r, modlen*sizeof(u32));
    free(MEMORY);
}


// Поиск обратного в поле GF(p) с помощью малой теоремы Ферма; квадрат-умнож
int MULTINV_FERMAT_SQPOW(int modlen, u32 * elem, u32 * mod, u32 * dest){
    u32 *MEMORY = malloc(modlen * sizeof(u32)*2);
    memset(MEMORY,0,modlen*sizeof(u32)*2);
    u32 *two = MEMORY;
    u32 *phi = MEMORY + modlen;
    two[0] = 2;
    minus(modlen, mod, two, phi);
    MULTINV_SQPOW(modlen, elem, phi, mod, dest);
    free(MEMORY);
    return 0;
}

// Поиск обратного в поле GF(p) с помощью малой теоремы Ферма; возведение в степень Монтгомери
int MULTINV_FERMAT_MONPOW(int modlen, u32 * elem, u32 * mod, u32 * dest){
    u32 *MEMORY = malloc(modlen * sizeof(u32)*2);
    memset(MEMORY,0,modlen*sizeof(u32)*2);
    u32 *two = MEMORY;
    u32 *phi = MEMORY + modlen;
    two[0] = 2;
    minus(modlen, mod, two, phi);
    MONTGOMERY_MONPOW(modlen, elem, phi, mod, dest);
    free(MEMORY);
    return 0;
}

// Поиск обратного в поле GF(p) с помощью малой теоремы Ферма; возведение в степень Монтгомери; оптимизированный, заменен
// int MULTINV_FERMAT_MONPOW_OPT(int modlen, u32 * elem, u32 * mod, u32 * dest){
//     u32 *MEMORY = malloc(modlen * sizeof(u32)*2);
//     memset(MEMORY,0,modlen*sizeof(u32)*2);
//     u32 *two = MEMORY;
//     u32 *phi = MEMORY + modlen;
//     two[0] = 2;
//     minus(modlen, mod, two, phi);
//     MONTGOMERY_MONPOW(modlen, elem, phi, mod, dest);
//     free(MEMORY);
//     return 0;
// }
