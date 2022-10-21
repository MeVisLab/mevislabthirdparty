#include "f2c.h"
#include "clapack.h"
#include "stdio.h"

#define SIZE 4

void MAIN_() {}
void MAIN__() {}
void _MAIN_() {}

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int main()
{
    char JOBU;
    char JOBVT;

    int i;

    integer M = SIZE;
    integer N = SIZE;

    integer LDA = M;
    integer LDU = M;
    integer LDVT = N;
    integer LWORK;
    integer INFO;

    integer mn = MIN(M, N);
    integer MN = MAX(M, N);

    double a[SIZE * SIZE] = { 16.0, 5.0, 9.0, 4.0, 2.0, 11.0, 7.0, 14.0, 3.0, 10.0, 6.0, 15.0, 13.0, 8.0, 12.0, 1.0 };
    double s[SIZE];
    double wk[201];
    double uu[SIZE * SIZE];
    double vt[SIZE * SIZE];

    JOBU = 'A';
    JOBVT = 'A';
    LWORK = 201;

    dgesvd_(&JOBU, &JOBVT, &M, &N, a, &LDA, s, uu, &LDU, vt, &LDVT, wk, &LWORK, &INFO);

    printf("\n INFO=%ld", INFO);

    for (i = 0; i < SIZE; i++) {
        printf("\n s[ %d ] = %f", i, s[i]);
    }

    return 0;
}
