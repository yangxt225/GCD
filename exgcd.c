#include <stdio.h>

/******************************************************************************************************** 
博文网址：http://blog.csdn.net/yxtxiaotian/article/details/52440808

欧几里德算法数学原理：
定理1：设a,b,c是任意三个不全为零的整数，且a=bq+c，其中q是整数，则gcd(a,b)=gcd(b,c)=gcd(b, a%b)；
*********************************************************************************************************
扩展欧几里得算法：对于不完全为 0 的非负整数 a，b，gcd（a，b）表示 a，b 的最大公约数，必然存在整数对 x，y ，使得 ：
gcd（a，b）=ax+by
*********************************************************************************************************
在RSA算法中，会使用到扩展欧几里得算法来生成密钥对，如下：
	ed ≡ 1 (mod φ(n))
这个式子等价于:
　　ed - 1 = kφ(n)
于是，找到模反元素d，实质上就是对下面这个二元一次方程求解:
　　ex + φ(n)y = 1
*********************************************************************************************************
扩展欧几里得算法应用：
（1）求解不定方程；
（2）求解模线性方程（线性同余方程）；
（3）求解模的逆元；
*********************************************************************************************************/

/*
扩展欧几里得算法(递归实现):
在实际应用中一般不使用递归实现，因其递归层次过深导致效率低下。
设 a>b。
　　1，显然当 b=0，gcd（a，b）=a。此时 x=1，y=0；
　　2，ab!=0 时
　　设 ax1+by1=gcd(a,b);
　　bx2+(a mod b)y2=gcd(b,a mod b);
　　根据朴素的欧几里德原理有 gcd(a,b)=gcd(b,a mod b);(递归公式)
　　则:ax1+by1=bx2+(a mod b)y2;
　　即:ax1+by1=bx2+(a-(a/b)*b)y2=ay2+bx2-(a/b)*by2;
　　根据恒等定理得：x1=y2; y1=x2-(a/b)*y2;
*/
int ExGcdRec(int a, int b, int *x, int *y)
{
	if(0==b)
	{
		*x = 1;
		*y = 0;
		return a;
	}
	int r = ExGcdRec(b, a%b, x, y);
	int tmp = *x;
	*x = *y;
	*y = tmp - (a/b)*(*y);
	return r;
}

/***************************************************************************************
扩展欧几里得算法(非递归实现)--效率较高:
公式推导：
假设在每一步i都可以找到x_i,y_i满足r_i=a*x_i+b*y_i，于是可以得到如下式子：
a=b*q_1+r_1, 				r_1=a*x_1+b*y_1;
由欧几里德算法数学原理, a=bq+c, gcd(a, b)=gcd(b, c)=gcd(b, a%b), 可递推出下面算式：
b=r_1*q_2+r_2, 				r_2=a*x_2+b*y_2;
r_1=r_2*q_3+r_3, 			r_3=a*x_3+b*y_3
……
r_(n-2)=r_(n-1)*q_n+r_n, 	r_n=a*x_n+b*y_n;
r_(n-1)=r_n*q_(n+1)+0;     // 最后都可以得到余数为0。

由r_(n-2)=r_(n-1)*q_n+r_n，可以通过移项得到：r_i=r_(i-2) - r_(i-1)*q_i 	(2)
同样从r_n=a*x_n+b*y_n，可以得到:
 r_(i-1)=a*x_(i-1)+b*y_(i-1);
 r_(i-2)=a*x_(i-2)+b*y_(i-2);
带入式(2)有:
r_i=a*x_(i-2)+b*y_(i-2) - [a*x_(i-1)+b*y_(i-1)]*q_i
    =a[x_(i-2) - x_(i-1)*q_i]+b[y_(i-2) - y_(i-1)*q_i]
又由假设r_i=a*x_i+b*y_i，可知:
x_i=x_(i-2) - x_(i-1)*q_i;
y_i=y_(i-2) - y_(i-1)*q_i.

至此便得到了x_i和y_i的推导公式，辗转相除的最后得到 r_n=ax_n+by_n，r_n即为a、b的最大公因子，
所以x_n，y_n就是所求的x、y。我们可以在辗转相除的同时根据递推式求解出x_n、y_n。
***************************************************************************************
推导x_1, y_1, x_2, y-2:
(1) 由a=b*q_1+r_1, r_1=a*x_1+b*y_1，令b=0,则有：
	a=r_1=a*x_1+b*y_1; ==> x_1=1, y_1=0;
(2) 由b=r_1*q_2+r_2, r_2=a*x_2+b*y_2; 令r_1=0,则有：
	b=r_2=a*x_2+b*y_2; ==> x_2=0, y_2=1;
***************************************************************************************
实现如下：
*/
int ExGcd(int a, int b, int *x, int *y)
{
	// 需要增加6个变量保存中间计算结果
	int x1=1,y1=0,x2=0,y2=1,x3,y3;
	
	if(0==b)
	{
		*x = 1;
		*y = 0;
		return a;
	}
	int r;
	while(r=a%b)
	{
		x3=x1-x2*(a/b);
		y3=y1-y2*(a/b);
		x1=x2;
		y1=y2;
		x2=x3;
		y2=y3;
		a = b;
		b = r;
	}
	*x = x3;
	*y = y3;
	return b;
}

int main()
{
	int a, b, x, y, result;
	printf("Please input two integer numbers(a, b):");
	scanf("%d%d", &a, &b);
	result = ExGcdRec(a, b, &x, &y);
	printf("%d, %d, %d\n", x, y, result);
	result = ExGcd(a, b, &x, &y);
	printf("%d, %d, %d\n", x, y, result);
	return 0;
}




