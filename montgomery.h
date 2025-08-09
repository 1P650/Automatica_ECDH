#ifndef MONTGOMERY_H
#define MONTGOMERY_H

/* Умножение Монтгомери и возведение в степень с помощью Монтгомери
 * На практике наиболее производительный
 * Однако скорее всего уступит бинарному алгоритму Евклида, если последний реализован оптимизированно
 */


/* Приведение к форме Монтгомери
 *
 */

void MONTGOMERY_MONFORM(int modlen, int k, u32 *a, u32 *mod, u32* t_x, u32 * a_r){
    memset(t_x,0,(2*modlen + 1)*sizeof(u32));
    shift_l_ext(k, modlen, 2 * modlen + 1, a, t_x);
    mod_p(t_x, 2*modlen+1, mod, modlen);
    memcpy(a_r, t_x, modlen*sizeof(u32));
}

/* Умножение с редукцией для форм Монтгомери
 * m(a)*m(b) = m(m(a*b))
 * m(a*b) = m^-1(m(a)*m(b))
 * Чтобы получить из m(x) x, нужно подать на вход функции monpro(m(x), 1)
 */

// void MONTGOMERY_MONPRO(int modlen, int k,u32 *a, u32 *b, u32 *mod, u32 *r_m1, u32 *mod_inv, u32 *T1, u32 *T2, u32* x){

//     //1) T1 = A_R
//     memcpy(T1, a, modlen*sizeof(u32));
//     //2) T2 = B_R
//     memcpy(T2, b, modlen*sizeof(u32));
//     //3) T1 = T1*T2
//     umn(2*modlen+1, T1, T2,T1);

//     //m(a,b) = m^-1(m(a)m(b))
//     //reduction - m^-1

//     // 4) T2 = T1 mod R
//     //binop_and(2*modlen+1, modlen, T1, r_m1, T2);
//     mod_p(T1, 2*modlen + 1, r_m1, modlen+1);
//     // 5) T2 = T2 * M_INV
//     umn(modlen, T1, mod_inv, T2);
//     // 6) T2 = T2 mod R
//     mod_p(T2, 2*modlen + 1, r_m1, modlen+1);
//     //binop_and(modlen, modlen, T2, r_m1, T2);
//     // 7) T2 = T2 * M
//     umn(modlen, T2, mod, T2);
//     // 7) T2 = T2 + T1
//     sum(2*modlen + 1, T1, T2, T2);
//     // 8) T2 = T2 / R
//     shift_r(k, 2*modlen+1, T2, T2);
//     // 9) T2 = T2 mod M
//     memset(T1,0,(2*modlen+1)*sizeof(u32));
//     memcpy(T1, mod, modlen*sizeof(u32));

//     // if(cmp(2*modlen+1,T2,T1) >= 0){
//     //      memset(T1,0,(2*modlen+1)*sizeof(u32));
//     //      memcpy(T1, mod, modlen*sizeof(u32));
//     //      minus(2*modlen+1, T2, T1, T2);
//     //  }

//     mod_p(T2, 2*modlen + 1, mod, modlen);
//     memcpy(x, T2, modlen*sizeof(u32));
// }


void MONTGOMERY_MONPRO(int modlen, int k,u32 *a, u32 *b, u32 *mod, u32 *T1, u32 *T2, u32* x){

    //1) T1 = C = 0
    memset(T1, 0, (2*modlen + 1)*sizeof(u32));

    //2) T2 = b
    memcpy(T2, b, modlen*sizeof(u32));

    for(int i = 0; i<= k-1; ++i){
        if(((a[i/32]>>(i%32)&1)!=0)){
            sum(2*modlen+1, T1, T2, T1);
        }
        if(T1[0]%2 != 0){
            sum_ext(2*modlen+1, modlen, T1, mod, T1);
        }
        shift_r(1, 2*modlen+1, T1,T1);
    }
    memset(T2,0,(2*modlen+1)*sizeof(u32));
    memcpy(T2, mod, modlen*sizeof(u32));
     if(cmp(modlen,T1,mod) >= 0){
         minus(2*modlen+1, T1, T2, T1);
     }



    memcpy(x, T1, modlen*sizeof(u32));
    memset(T1,0,(2*modlen + 1)*sizeof(u32));
    memset(T2, 0, (2*modlen + 1)*sizeof(u32));
}

/* Возведение в степень с помощью умножения Монтгомери
 * modlen - длина модуля
 * elem - ptr на элемент
 * mod - ptr на модуль
 * pw - ptr на результат
 */


// Эта версия падает на ECC 256
// void MONTGOMERY_MONPOW(int modlen, u32 * elem, u32 * pow, u32 * mod, u32 * pw){
//     u32* MEMORY = malloc(modlen * sizeof(u32) * 6 + (modlen + 1) * sizeof(u32) * 4 + (2 * modlen + 1) * sizeof(u32) * 4+sizeof(u32));
//     memset(MEMORY, 0, modlen * sizeof(u32) * 6 + (modlen + 1) * sizeof(u32) * 4 + (2 * modlen + 1) * sizeof(u32) * 4+sizeof(u32));
//     u32* a = MEMORY;
//     u32* e = a + modlen;
//     u32* x = e + modlen;
//     u32* zero = x + (2*modlen + 1);

//     u32* r = zero + modlen;
//     u32* T1 = r + modlen + 1;
//     u32* T2 = T1 + (2 * modlen + 1);
//     u32* mod_inv = T2 + (2 * modlen + 1);

//     memcpy(a, elem, modlen*sizeof(u32));
//     memcpy(e, pow, modlen*sizeof(u32));

//     int k = first_bit(modlen, mod) + 1;
//     r[k/32] = 1 << (k%32);
//     printf("MONTDEBUG: k = %d\n",k);



//     //calculate -n^-1 mod r
//     mod_inv[0] = 1;
//     zero[0] = 1;
//     for(int i = 2; i <= k; ++i){
//         memset(T2, 0, sizeof(u32)*(2*modlen+1));T2[0]=1;
//         shift_l(i, 2*modlen+1, zero, x);
//         memset(T2, 0, sizeof(u32)*(2*modlen+1));
//         minus(modlen, x, zero, T2);
//         umn(modlen, mod, mod_inv, T1);
//         binop_and(2*modlen + 1, modlen, T1, T2, T1);
//         memset(T2, 0, sizeof(u32)*(2*modlen+1));
//         T2[0]=1;
//         if(cmp(2*modlen+1,T1,T2) != 0){
//             shift_r(1,2*modlen+1,x,x);
//             sum(2*modlen+1, mod_inv, x, mod_inv);
//         }

//     }

//     minus(modlen+1, r, mod_inv, mod_inv);
//     printf("MONTDEBUG: mod_inv = ");
//     HEXUTIL_printHex(mod_inv, modlen+1);

//     printf("MONTDEBUG: mod = ");
//     HEXUTIL_printHex(mod, modlen);

//     printf("MONTDEBUG: r = ");
//     HEXUTIL_printHex(r, modlen+1);

//     memset(T1,0, (2*modlen+1)*sizeof(u32));
//     memset(T2,0, (2*modlen+1)*sizeof(u32));
//     memset(x,0, (2*modlen+1)*sizeof(u32));

//     //calculate constants
//     memcpy(T2, mod, modlen * sizeof(u32));


//     if(r[modlen]==0){
//         minus(modlen+1, r, T2, x);
//     }
//     else{
//         minus(modlen+1, r, T2, T2);
//         memcpy(x, T2, modlen*sizeof(u32));
//     }


//     //minus(modlen+1, r, T2, x);

//     // a = elem * r mod n = elem << k mod n

//     shift_l_ext(k, modlen,2*modlen+1, elem, T1);
//     mod_p(T1, 2*modlen + 1, mod, modlen);
//     memcpy(a, T1, modlen*sizeof(u32));


//     memset(T2,0, (2*modlen+1)*sizeof(u32));

//     zero[0] = 1;

//     //minus(modlen+1, r, zero, r);
//     //if(r[modlen]!=0) r[modlen] = 0;
//     zero[0] = 0;

//     int E_FB = first_bit(modlen, e);
//     for(int i = E_FB; i>=0; i--){
//         MONTGOMERY_MONPRO(modlen, k, x, x, mod, r, mod_inv, T1, T2, x);
//         if(((e[i/32]>>(i%32))&1) == 1){
//             MONTGOMERY_MONPRO(modlen, k, x, a, mod, r, mod_inv, T1, T2, x);
//         }
//     }

//     memset(zero, 0, modlen*sizeof(u32));
//     memset(T1, 0, (2*modlen+1)*sizeof(u32));
//     memset(T2, 0, (2*modlen+1)*sizeof(u32));
//     zero[0]=1;
//     MONTGOMERY_REDUCE(modlen, k, x,zero, mod, r, mod_inv, T1, T2, x);
//     memcpy(pw, x, modlen*sizeof(u32));
//     free(MEMORY);
// }

void MONTGOMERY_MONPOW(int modlen, u32 * elem, u32 * pow, u32 * mod, u32 * pw){
    u32* MEMORY = malloc(modlen * sizeof(u32) * 5 + (modlen + 1) * sizeof(u32) * 2 + (2 * modlen + 1) * sizeof(u32) * 2+sizeof(u32));
    memset(MEMORY, 0, modlen * sizeof(u32) * 5 + (modlen + 1) * sizeof(u32) * 2 + (2 * modlen + 1) * sizeof(u32) * 2+sizeof(u32));
    u32* a = MEMORY;
    u32* e = a + modlen;
    u32* x = e + modlen;
    u32* zero = x + modlen + 1;

    u32* r = zero + modlen;
    u32* T1 = r + modlen + 1;
    u32* T2 = T1 + (2 * modlen + 1);


    memcpy(a, elem, modlen*sizeof(u32));
    memcpy(e, pow, modlen*sizeof(u32));
    int k = first_bit(modlen, mod) + 1;
    r[k/32] = 1 << (k%32);

    //calculate constants
    memcpy(T2, mod, modlen * sizeof(u32));
    if(r[modlen-1]==0){
        minus(modlen, r, T2, x);
    }
    else{
        minus(modlen+1, r, T2, T2);
        memcpy(x, T2, modlen*sizeof(u32));
    }

    // a = elem * r mod n = elem << k mod n
    shift_l_ext(k, modlen,2*modlen+1, elem, T1);
    mod_p(T1, 2*modlen + 1, mod, modlen);
    memcpy(a, T1, modlen*sizeof(u32));

    zero[0] = 1;
    minus(modlen+1, r, zero, r);
    r[modlen] = 0;

    zero[0] = 0;

    int E_FB = first_bit(modlen, e);
    for(int i = E_FB; i>=0; i--){
        MONTGOMERY_MONPRO(modlen, k, x, x, mod, T1, T2, x);
        if(((e[i/32]>>(i%32))&1) == 1){
            MONTGOMERY_MONPRO(modlen, k, x, a, mod, T1, T2, x);
        }
    }

    memset(zero, 0, modlen*sizeof(u32));
    zero[0] = 1;
    MONTGOMERY_MONPRO(modlen, k, x, zero, mod, T1, T2, x);
    memcpy(pw, x, modlen*sizeof(u32));
    free(MEMORY);
}


#endif // MONTGOMERY_H
