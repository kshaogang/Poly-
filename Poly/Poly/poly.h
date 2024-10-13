#include<stdio.h>
#include<stdlib.h>

struct Poly {
	int coef;//系数
	int expon;//指数
	struct Poly* Link;
};
typedef struct Poly* Polynomial;

Polynomial ReadPoly();
void PrintPoly(Polynomial A);
Polynomial PlusPoly(Polynomial B, Polynomial C);
Polynomial Rank(Polynomial A);
Polynomial MulP(Polynomial P1, Polynomial P2);
