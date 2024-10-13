#define _CRT_SECURE_NO_WARNINGS

#include<poly.h>
//�޷���Դ�ļ�"poly.h"ʱ����Ŀ��������Ӹ���Ŀ¼�����poly.h��Ŀ¼

Polynomial ReadPoly() {
	printf("���������Ķ���ʽÿһ���ϵ����ָ����������֮��ʹ�ö��Ÿ�����������ʱ��#����\n");
	char a;
	int c;
	int e;
	scanf("%d %d", &c, &e);//scanf��ʽ


	//����һ���սڵ�洢ϵ����ָ������Ϊ��һ��
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct Poly));
	P->coef = c;
	P->expon = e;
	P->Link = NULL;


	//������ͷ�ͱ�β
	//��ͷ����ָ�����ʽ����β�������Ӹ����ڵ�
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
		Rear->Link = NewNode;//����
		Rear = NewNode;

		scanf("%c", &a);
	}
	Rear->Link = NULL;//���һ���ڵ�ָ��NULL�����β��������������ã����ܻ�����ڴ���Һ��ڴ�й¶
	printf("������\n");
	return Rank(Front);
}

void PrintPoly(Polynomial A) {
	int flag = 0;

	if (!A) { printf("0 0\n"); return; }//���A�ǿ�

	while (A) {
		if (!flag) {
			flag = 1;//����flag���жϵ�һ���Ϊ��һ��ļӺ�ʡ��
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
	//B��C���ǿ�
	Polynomial Plus, T, Front;
	Plus = (Polynomial)malloc(sizeof(struct Poly));
	//malloc���ڷ���ָ�����õ��ڴ������ָ��
	//��һ����ָ�����ڽ���ͷ���϶���ʽ��������ʹ���ӵĲ���һ��
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
			/*����Ҫ��ֱ�����C���ɰ�
			Plus->Link = C;
			Plus = Plus->Link;
			C = C->Link;*/
		}
	}
	else Plus->Link = NULL;

	Front = Front->Link;
	free(T);
	return Front;//��Ӧ��return Plus����ΪPlus�Ѿ�ָ������ı�β�ˣ�
}

//������Ķ���ʽ�Ӵ�С���У�ʹ��ð������bubble sort,����������
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

//����һ�γ�ֻ��Ҫ����N^2�Σ���������ݽṹ�Ŀ���ҪN^3��?
Polynomial MulP(Polynomial P1, Polynomial P2) {
	Polynomial t1, t2, PMul, T, Rear;
	//ͷ���
	PMul = (Polynomial)malloc(sizeof(struct Poly));
	T = Rear = PMul;//��������
	PMul->Link = NULL;

	t1 = P1;
	t2 = P2;
	int c, e;

	if (!P1 || !P2)return NULL;

	//��ó�ʼ����ʽ
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

	//����
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