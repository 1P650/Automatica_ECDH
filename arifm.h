#ifndef _ARIFM_H
#define _ARIFM_H

#define MAXLEN 33
#define BIT_INT 32
#define LOG_BIT_INT 5
#define MASK_INT 0xffffffff
#define MASK_INT_C 0x100000000l


////////////////////////////////////////////////////////////////////
// ������� ��� ������ � �������� �������
// len - ������ ����� � ������
// ������������ ������ ����� - MAXLEN
////////////////////////////////////////////////////////////////////

// ��������� a �� b, ��������� � c
void umn(int len, unsigned int *a, unsigned int *b, unsigned int *c);

// ���������� ����� ������� ������� � ����� a
int first_bit(int len, unsigned int *a);

// ��������� a c b
// ���������: 0 - �����, 1 - a ������ b, -1 - a ������ b
int cmp(int len, unsigned int *a, unsigned int *b);

// �������� a � b, ��������� � c
void sum(int len, unsigned int *a, unsigned int *b, unsigned int *c);

// ��������� b �� a, ��������� � c
void minus(int len, unsigned int * a, unsigned int * b, unsigned int * c);

// �������� a � b �� ������ p, ��������� � c
void sum_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c);

// ��������� b �� a �� ������ p, ��������� � c
void raz_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c);

// ���������� a (����� n1 ����) �� ������ p(����� n2 ����)
void mod_p(unsigned int * a, int n1, unsigned int * p, int n2);

// ������������ a �� b �� mod p, ��������� � c
void mulp(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c);

// ����� a �� k ��� �����, ��������� � c
void shift_l(int k, int len, unsigned int * a, unsigned int * c);

// ����� a �� k ��� ������, ��������� � c
void shift_r(int k, int len, unsigned int * a, unsigned int * c);

// ��������� ����� ����� c
void change_sign(int len, unsigned int * c);

// ����� ����� �� ������� a �� b, ��������� � c
int div(int len, unsigned int * a, unsigned int * b, unsigned int * c);

// ��������� �
void binop_and(int a_n, int b_n, unsigned int* a, unsigned int *b, unsigned int *c);


// �������� a � b � ���������?, ��������� � c
void sum_ext(int n_a, int n_b, unsigned int *a, unsigned int *b, unsigned int *c);

#endif
