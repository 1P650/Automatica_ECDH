#include<string.h>
#include"arifm.h"



void umn(int n, unsigned int *a, unsigned int *b, unsigned int *c)
{
	unsigned long long a1[MAXLEN];
	unsigned long long b1[MAXLEN];
	unsigned long long d;
	int i,j;

	i = n;
	while(--i>=0){ a1[i] = a[i]; b1[i] = b[i];}

	i = 2*n;
	while (--i >= 0) c[i] = 0;

	for(i = 0; i < n; i++)
	{
		d = 0;
		for(j = 0; j < n; j++)
		{
			d += (unsigned long long) a1[j] * b1[i] + c[i+j];
			c[i+j] = d;
			d >>= 32;
		}
		c[i+j] = d;
	}
}




void binop_and(int a_n, int b_n, unsigned int* a, unsigned int *b, unsigned int *c)
{
    for(int i = 0; i < b_n; ++i){
        c[i] = a[i] & b[i];
    }
    for(int i = b_n; i < a_n; ++i){
        c[i] = 0;
    }
}

void umn_mod(int n, unsigned int *a, unsigned int *b, unsigned int *p, unsigned int *c)
{
    unsigned int * c_tmp = malloc(2*n*sizeof(unsigned int));
    memset(c_tmp, 0, 2*n*sizeof(unsigned int));
    unsigned long long a1[MAXLEN];
    unsigned long long b1[MAXLEN];
    unsigned long long d;
    int i,j;

    i = n;
    while(--i>=0){ a1[i] = a[i]; b1[i] = b[i];}

    for(i = 0; i < n; i++)
    {
        d = 0;
        for(j = 0; j < n; j++)
        {
            d += (unsigned long long) a1[j] * b1[i] + c_tmp[i+j];
            c_tmp[i+j] = d;
            d >>= 32;
        }
        c_tmp[i+j] = d;
    }

    mod_p(c_tmp, 2*n, p, n);
    memcpy(c,c_tmp,n*sizeof(unsigned int));

    free(c_tmp);
}

int first_bit(int n, unsigned int *a)
{
	int i,j;
	for (i = n-1; i>=0; i--)
	{
		if(a[i])
		{
			for (j = 31; j>=0; j--)
			{
                if((a[i] >> j))
					return i * 32 + j;
			}
		}
	}
	return -1;
}

int first_bit32(unsigned int a)
{
    int i,j;

            for (j = 31; j>=0; j--)
            {
                if((a >> j))
                    return i * 32 + j;
            }

    return -1;
}


int cmp(int n, unsigned int *a, unsigned int *b)
{
    int i = n-1;
    while(i >= 0 && a[i] == b[i])
        i--;
    if(i < 0)
        return 0;
    if(a[i] > b[i])
        return 1;
    return -1;
}

int cmp_greater(int n_a,int n_b, unsigned int *a,  unsigned int *b)
{
    //assert n_a > n_b
    for(int j = n_a - 1; j >= n_b; --j){
        if(a[j]!=0) return 1;
    }

    int i = n_b-1;
    while(i >= 0 && a[i] == b[i])
        i--;
    if(i < 0)
        return 0;
    if(a[i] > b[i])
        return 1;
    return -1;

}

void sum(int n, unsigned int *a, unsigned int *b, unsigned int *c)
{
	unsigned int d = 0;
	unsigned long long s;
	for(int i = 0; i < n; i++)
	{
		s = (unsigned long long) a[i] + b[i] + d;
		c[i] = s;
		d = s >> 32;
	}
}

void sum_ext(int n_a, int n_b, unsigned int *a, unsigned int *b, unsigned int *c) {
    // n_a > n_b
    unsigned int d = 0;
    unsigned long long s;

    for (int i = 0; i < n_a; i++) {
        if (i < n_b) {
            s = (unsigned long long)a[i] + (unsigned long long)b[i] + d;
        } else {
            s = (unsigned long long)a[i] + d;
        }

        c[i] = (unsigned int)s;
        d = (unsigned int)(s >> 32);
    }

    if (d != 0) {
        c[n_a] = d;
    }
}

void minus(int len, unsigned int * a, unsigned int * b, unsigned int * c)
{
	int i;
	unsigned long long d;
	unsigned int h=0;
	for(i=0;i<len;i++)
	{
		d=(unsigned long long)a[i] - b[i] - h;
		c[i] = d & MASK_INT;
		h = (d & MASK_INT_C) ? 1 : 0;
	}
}

void minus_greater(int len_a, int len_b, unsigned int * a, unsigned int * b, unsigned int * c)
{
    int i;
    unsigned long long d;
    unsigned int h=0;
    for(i=0;i<len_b;i++)
    {
        d=(unsigned long long)a[i] - b[i] - h;
        c[i] = d & MASK_INT;
        h = (d & MASK_INT_C) ? 1 : 0;
    }
    for(i=len_b;i<len_a;i++)
    {
        d=(unsigned long long)a[i]  - h;
        c[i] = d & MASK_INT;
        h = (d & MASK_INT_C) ? 1 : 0;
    }
}




void sum_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c)
{
    sum(len,a,b,c);
    while(cmp(len,c,p)>=0) minus(len,c,p,c);
}

void sum_modp(int len, int len_c, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c)
{
    sum(len,a,b,c);
    mod_p(c,len_c,p, len);
}

void raz_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c)
{
	if(cmp(len,a,b)!=-1)
		minus(len,a,b,c);
	else
	{
		minus(len,a,b,c);
		sum(len,c,p,c);
	}
    while(cmp(len,c,p)>=0)
		minus(len,c,p,c);
}

void minus_modp(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c)
{
    if(cmp(len,a,b)!=-1)
        minus(len,a,b,c);
    else
    {
        minus(len,a,b,c);
        sum(len,c,p,c);
    }
    mod_p(c, len, p, len);
}

void mod_p(unsigned int * a, int n1, unsigned int * p, int n2)
{
	int m1=first_bit(n1,a);
	int m2=first_bit(n2,p);
	if(m2>m1)
		return;
	else if(m1==m2)
	{
		if(cmp(min(n1,n2),a,p)==-1)
			return;
	}
	int len=max(n1,n2);
    unsigned int * c = malloc(len*sizeof(c));
    unsigned int * p1 = malloc(len*sizeof(p1));
	memset(p1,0,len*sizeof(int));
	memcpy(p1,p,n2*sizeof(int));
    unsigned int * a1 = malloc(len*sizeof(a1));
	memset(a1,0,len*sizeof(int));
	memcpy(a1,a,n1*sizeof(int));
	do
	{
		int m1=first_bit(len,a1);
		int kn=m1-m2;
		shift_l(kn,len,p1,c);
		if(cmp(len,a1,c)==-1)
		{
			kn--;
			shift_l(kn,len,p1,c);
		}
		minus(len,a1,c,a1);
	}
	while(cmp(len,a1,p1)!=-1);
    memcpy(a,a1,n1*sizeof(a));
    free(c);
    free(p1);
    free(a1);
}


void mod_p_copy(unsigned int * a, int n1, unsigned int * p, int n2, unsigned int * dest)
{
    int m1=first_bit(n1,a);
    int m2=first_bit(n2,p);
    if(m2>m1)
        return;
    else if(m1==m2)
    {
        if(cmp(min(n1,n2),a,p)==-1)
            return;
    }
    int len=max(n1,n2);
    unsigned int * c = malloc(len*sizeof(c));
    unsigned int * p1 = malloc(len*sizeof(p1));
    memset(p1,0,len*sizeof(int));
    memcpy(p1,p,n2*sizeof(int));
    unsigned int * a1 = malloc(len*sizeof(a1));
    memset(a1,0,len*sizeof(int));
    memcpy(a1,a,n1*sizeof(int));
    do
    {
        int m1=first_bit(len,a1);
        int kn=m1-m2;
        shift_l(kn,len,p1,c);
        if(cmp(len,a1,c)==-1)
        {
            kn--;
            shift_l(kn,len,p1,c);
        }
        minus(len,a1,c,a1);
    }
    while(cmp(len,a1,p1)!=-1);
    memcpy(dest,a1,n1*sizeof(a));
    memcpy(a,a1,n1*sizeof(a));
    free(c);
    free(p1);
    free(a1);
}


void mulp(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c)
{
    unsigned int * u11;
    u11 = malloc(2*len*sizeof(u11));
	umn(len, a,b,u11);
	mod_p(u11,2*len,p,len);
	memcpy(c,u11,len*sizeof(int));
    free(u11);
}

void shift_l(int k, int n, unsigned int * a, unsigned int * c)
{
	unsigned int x[MAXLEN];
	int n1 = k / 32;
	int n2 = k % 32;
	int i;
	for(i=0;i<n;i++) x[i] = 0;
	for(i=0;i<n;i++)
	{
		if(n2 && i+n1+1<n)
			x[i+n1+1]|=(a[i]>>(BIT_INT-n2));
		if(i+n1<n)
		{
			x[i+n1]|=(a[i]<<n2);
			x[i+n1] &= MASK_INT;
		}
	}
	for(i=0;i<n;i++) c[i] = x[i];
}

void shift_l_ext(int k, int n, int N, unsigned int * a, unsigned int * c)
{
    int n1 = k / 32;
    int n2 = k % 32;
    int i;
    for(i=0;i<n;i++)
    {
        if(n2 && i+n1+1<N)
            c[i+n1+1]|=(a[i]>>(BIT_INT-n2));
        if(i+n1<N)
        {
            c[i+n1]|=(a[i]<<n2);
            c[i+n1] &= MASK_INT;
        }
    }
}

void shift_r(int k, int n, unsigned int * a, unsigned int * c)
{
	unsigned int x[MAXLEN];
	int n1 = k / 32;
	int n2 = k % 32;
	int i;
	for(i=0;i<n;i++) x[i] = 0;
	for(i=0;i<n;i++)
	{
		if(i-n1-1>=0)
		{
			x[i-n1-1]|=(a[i]<<(BIT_INT-n2));
			x[i-n1-1] &= MASK_INT;
		}
		if(i-n1>=0)
			x[i-n1]|=(a[i]>>n2);
	}
	for(i=0;i<n;i++) c[i] = x[i];
}

void change_sign(int len, unsigned int * c)
{
	int i,p;
	unsigned long long s;
	for(i=0;i<len;i++)
		c[i]^=MASK_INT;
	if((c[0]&1)==0)
		c[0]|=1;
	else
	{
		i=0;
		p=1;
		do
		{
			s=(unsigned long long)c[i]+1;
			c[i]=s&MASK_INT;
			if(s&MASK_INT_C)	p=1;
			else	p=0;
			i++;
		}
		while(p==1 && i<len);
	}
}

int div(int len, unsigned int * a, unsigned int * b, unsigned int * c)
{
	int sign1,sign2;
	int m1,m2,kn,i;
	unsigned int y[MAXLEN];
	unsigned int yb[MAXLEN];
	for(i=0;i<len;i++) {y[i] = a[i]; yb[i] = b[i];c[i] = 0;}
	if(first_bit(len,yb)==-1)
		return -1;
	sign1 = (y[len-1]>>(BIT_INT-1))&1;
	sign2 = (yb[len-1]>>(BIT_INT-1))&1;
	if(sign1)
		change_sign(len,y);
	if(sign2)
		change_sign(len,yb);
	if(cmp(len,y,yb)!=-1)
	{
		unsigned int x[MAXLEN];
		m2=first_bit(len,yb);
		do
		{
			m1=first_bit(len,y);
			kn=m1-m2;
			shift_l(kn,len,yb,x);
			if(cmp(len,y,x)==-1)
			{
				kn--;
				shift_l(kn,len,yb,x);
			}
			c[(kn>>LOG_BIT_INT)&0xff]|=1<<(kn&(BIT_INT-1));
			minus(len,y,x,y);
		}
		while(cmp(len,y,yb)!=-1);
	}
	return 0;
}



int max(int a, int b)
{
    return a > b ? a : b;
};

int min(int a, int b)
{
    return a < b ? a : b;
};

int divu(int len, unsigned int * a, unsigned int * b, unsigned int * c)
{
    int sign1,sign2;
    int m1,m2,kn,i;
    unsigned int y[MAXLEN];
    unsigned int yb[MAXLEN];
    for(i=0;i<len;i++) {y[i] = a[i]; yb[i] = b[i];c[i] = 0;}
    if(first_bit(len,yb)==-1)
        return -1;
    if(cmp(len,y,yb)!=-1)
    {
        unsigned int x[MAXLEN];
        m2=first_bit(len,yb);
        do
        {
            m1=first_bit(len,y);
            kn=m1-m2;
            shift_l(kn,len,yb,x);
            if(cmp(len,y,x)==-1)
            {
                kn--;
                shift_l(kn,len,yb,x);
            }
            c[(kn>>LOG_BIT_INT)&0xff]|=1<<(kn&(BIT_INT-1));
            minus(len,y,x,y);
        }
        while(cmp(len,y,yb)!=-1);
    }
    return 0;
}


