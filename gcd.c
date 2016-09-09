#include <stdio.h>

/* 
求最大公约数的几种方法：
	1. 辗转相除法(欧几里得算法)
	2. 更相减损法
	3. 穷举法
*/

/*求最小公倍数算法：
	最小公倍数=两整数的乘积÷最大公约数
*/

/* 辗转相除法(非递归)
有两整数a和b：
	1 a%b得余数c;
	2 若c=0，则b即为两数的最大公约数;
	3 若c≠0，则a=b，b=c，再回去执行1.
*/
int GCDMethod1(int a, int b)
{
	
	int c = a%b;
	while(c != 0)
	{
		a = b;
		b = c;
		c = a%b;
	}
	return b;
}

/* 辗转相除法(递归实现)*/
int GCDMethodRec1(int a, int b)
{
	if(0==b)
		return a;
	return GCDMethodRec1(b, a%b);
}

/* 辗转相除法(递归实现)*/
int GCDMethodRec2(int a, int b)
{
	return b ? GCDMethodRec1(b, a%b) : a;
}

/* 更相减损法
有两整数a和b：
	1 若a>b，则a=a-b;
	2 若a<b，则b=b-a;
	3 若a=b，则a（或b）即为两数的最大公约数;
	4 若a≠b，则再回去执行1.
*/
int GCDMethod2(int a, int b)
{
	while(a != b)
	{
		if(a > b)
			a = a - b;
		else
			b = b - a;
	}
	return a;
}

/* 穷举法
有两整数a和b：
	1 i= a(或b);
	2 若a，b能同时被i整除，则i即为最大公约数，结束;
	3 i--，再回去执行2.
*/
int GCDMethod3(int a, int b)
{
	int i = a<b ? a : b;
	while(!((0 == a%i) && (0 == b%i)))
	{
		i--;
	}
	return i;
}

int main()
{
	int a, b, c;
	printf("Please input two integer numbers(a, b):");
	scanf("%d%d", &a, &b);
	
	// 辗转相除法
	//c = GCDMethod1(a, b);
	// 更相减损法
	//c = GCDMethod2(a, b);	
	// 穷举法
	c = GCDMethod3(a, b);
	
	printf("The greatest common divisor bewteen(%d, %d) is %d", a, b, c);
	return 0;
}




