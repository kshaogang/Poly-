#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<poly.h>

//一元多项式的相加和相乘：读，加，乘

void main() {

	Polynomial P1, P2, PSum, PMul;
	P1 = ReadPoly();//调用函数时不要忘记括号WTF
	P2 = ReadPoly();
	PSum = PlusPoly(P1, P2);
	PMul = MulP(P1, P2);
	printf("多项式的和为：");
	PrintPoly(PSum);
	printf("\n");
	printf("多项式的乘积为：");
	PrintPoly(PMul);
	// 我说怎么一直失败，原来输入时没有从大到小输入，再写一个排列的函数
	//函数调用参数过多：.h文件的声明忘记加参数了
}
/*1.char类型：为char变量赋值时有两种情况，第一种是char a = 'a'，此时a = a，第二种是char a = 97，此时a = a，还有另一种是a="a",当然
这种是不符合规范的，因为此时a 被赋值为字符串常量，实际是包含一个元素的数组加上 '\0'*/
/*2.char类型的输出也有两种，一种是%c，一种是%d(编译器允许的情况下),会输出字符和整数*/
/*3.scanf:%c 用于读取单个字符，并将其存储在一个 char 类型的变量中,用户可以输入任何字符，包括空格*/
/*4.scanf:使用 [^\n]* 来读取一行中的所有字符直到换行符：*/