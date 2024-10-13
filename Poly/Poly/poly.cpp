#define _CRT_SECURE_NO_WARNINGS

#include<poly.h>
//无法打开源文件"poly.h"时在项目属性里添加附加目录，添加poly.h的目录

Polynomial ReadPoly() {
	printf("请输入您的多项式每一项的系数和指数，项与项之间使用逗号隔开，输出完成时按#跳出\n");
	char a;
	int c;
	int e;
	scanf("%d %d", &c, &e);//scanf格式


	//创建一个空节点存储系数和指数，作为第一项
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct Poly));
	P->coef = c;
	P->expon = e;
	P->Link = NULL;


	//创建表头和表尾
	//表头用于指向多项式，表尾用于连接各个节点
	Polynomial Front, Rear;
	Front = P;
	Rear = P;
	scanf("%c", &a);


	while (a != '#')
	{
		scanf("%d %d", &c, &e);

		Polynomial NewNode;
		NewNode = (Polynomial)malloc(sizeof(struct Poly));
		NewNode->coef = c;
		NewNode->expon = e;
		NewNode->Link = NULL;
		Rear->Link = NewNode;//连接
		Rear = NewNode;

		scanf("%c", &a);
	}
	Rear->Link = NULL;//最后一个节点指向NULL代表结尾，如果不这样设置，可能会造成内存混乱和内存泄露
	printf("输出完成\n");
	return Rank(Front);
}

void PrintPoly(Polynomial A) {
	int flag = 0;

	if (!A) { printf("0 0\n"); return; }//如果A是空

	while (A) {
		if (!flag) {
			flag = 1;//利用flag来判断第一项，因为第一项的加号省略
			if (A->coef < 0) {
				printf("-");
				A->coef = -A->coef;
			}
		}
		else if (A->coef >= 0) {
			printf("+");
		}
		else if (A->coef < 0) {
			printf("-");
			A->coef = -A->coef;
		}
		printf("%dx^%d", A->coef, A->expon);
		A = A->Link;
	}
	printf("\n");
}

Polynomial PlusPoly(Polynomial B, Polynomial C) {
	//B和C均非空
	Polynomial Plus, T, Front;
	Plus = (Polynomial)malloc(sizeof(struct Poly));
	//malloc用于返回指向分配好的内存区域的指针
	//第一个空指针用于将表头接上多项式。并可以使连接的操作一致
	T = Front = Plus;

	while (B && C) {
		if (B->expon > C->expon) {
			Plus->Link = B;
			Plus = Plus->Link;
			B = B->Link;
		}
		else if (B->expon < C->expon) {
			Plus->Link = C;
			Plus = Plus->Link;
			C = C->Link;
		}
		else if (B->expon == C->expon) {
			if (B->coef + C->coef != 0) {
				Polynomial K;
				K = (Polynomial)malloc(sizeof(struct Poly));
				K->coef = B->coef + C->coef;
				K->expon = B->expon;
				Plus->Link = K;
				Plus = K;
			}
			B = B->Link;
			C = C->Link;
		}

	}
	if (B || C)
	{
		if (B) {
			Plus->Link = B;
		}
		if (C) {
			Plus->Link = C;
			/*不需要，直接添加C即可啊
			Plus->Link = C;
			Plus = Plus->Link;
			C = C->Link;*/
		}
	}
	else Plus->Link = NULL;

	Front = Front->Link;
	free(T);
	return Front;//不应该return Plus，因为Plus已经指向链表的表尾了！
}

//将输入的多项式从大到小排列，使用冒泡排序bubble sort,仅交换数据
Polynomial Rank(Polynomial A) {

	if (!A) {
		printf("NUll");
		return NULL;
	}

	Polynomial Temp, Head, count;
	Head = count = A;
	Temp = A->Link;
	int C, E;

	while (count != NULL) {

		while (Temp != NULL) {
			if (Temp->expon > Head->expon) {
				C = Temp->coef;
				Temp->coef = Head->coef;
				Head->coef = C;

				E = Temp->expon;
				Temp->expon = Head->expon;
				Head->expon = E;
			}
			Head = Head->Link;
			Temp = Temp->Link;
		}
		Head = A;
		Temp = A->Link;
		count = count->Link;
	}
	return A;
}

//这样一次乘只需要遍历N^2次，而浙大数据结构的课需要N^3次?
Polynomial MulP(Polynomial P1, Polynomial P2) {
	Polynomial t1, t2, PMul, T, Rear;
	//头结点
	PMul = (Polynomial)malloc(sizeof(struct Poly));
	T = Rear = PMul;//用于链接
	PMul->Link = NULL;

	t1 = P1;
	t2 = P2;
	int c, e;

	if (!P1 || !P2)return NULL;

	//获得初始多项式
	while (t2) {
		c = t1->coef * t2->coef;
		e = t1->expon + t2->expon;

		Polynomial P = (Polynomial)malloc(sizeof(struct Poly));
		P->coef = c;
		P->expon = e;
		P->Link = NULL;

		Rear->Link = P;
		Rear = Rear->Link;

		t2 = t2->Link;
	}
	PMul = PMul->Link;
	free(T);

	//遍历
	t1 = t1->Link;
	t2 = P2;
	while (t1) {
		Polynomial NewPoly, NewRear, NewT;
		NewPoly = (Polynomial)malloc(sizeof(struct Poly));
		NewRear = NewT = NewPoly;

		while (t2) {
			c = t1->coef * t2->coef;
			e = t1->expon + t2->expon;

			Polynomial P = (Polynomial)malloc(sizeof(struct Poly));
			P->coef = c;
			P->expon = e;
			P->Link = NULL;

			NewRear->Link = P;
			NewRear = NewRear->Link;

			t2 = t2->Link;
		}

		NewPoly = NewPoly->Link;
		free(NewT);
		PMul = PlusPoly(PMul, NewPoly);
		t1 = t1->Link;
		t2 = P2;
	}

	return PMul;
}