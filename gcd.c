#include <stdio.h>
/*
ŷ������㷨��ѧԭ��
	��a,b,c������������ȫΪ�����������a=bq+c������q����������gcd(a,b)=gcd(b,c)=gcd(b, a%b)��
*********************************************************************************************************/

/* 
�����Լ���ļ��ַ�����
	1. շת�����(ŷ������㷨)
	2. �������
	3. ��ٷ�
*/

/*����С�������㷨��
	��С������=�������ĳ˻������Լ��
*/

/* շת�����(�ǵݹ�)
��������a��b��
	1 a%b������c;
	2 ��c=0����b��Ϊ���������Լ��;
	3 ��c��0����a=b��b=c���ٻ�ȥִ��1.
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

/* շת�����(�ݹ�ʵ��)*/
int GCDMethodRec1(int a, int b)
{
	if(0==b)
		return a;
	return GCDMethodRec1(b, a%b);
}

/* շת�����(�ݹ�ʵ��)*/
int GCDMethodRec2(int a, int b)
{
	return b ? GCDMethodRec1(b, a%b) : a;
}

/* �������
��������a��b��
	1 ��a>b����a=a-b;
	2 ��a<b����b=b-a;
	3 ��a=b����a����b����Ϊ���������Լ��;
	4 ��a��b�����ٻ�ȥִ��1.
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

/* ��ٷ�
��������a��b��
	1 i= a(��b);
	2 ��a��b��ͬʱ��i��������i��Ϊ���Լ��������;
	3 i--���ٻ�ȥִ��2.
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
	
	// շת�����
	//c = GCDMethod1(a, b);
	// �������
	//c = GCDMethod2(a, b);	
	// ��ٷ�
	c = GCDMethod3(a, b);
	
	printf("The greatest common divisor bewteen(%d, %d) is %d\n", a, b, c);
	return 0;
}





