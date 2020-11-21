//水仙花数是指一个N位正整数（N≥3），它的每个位上的数字的N次幂之和等于它本身。
//本题要求编写两个函数，一个判断给定整数是否水仙花数，另一个按从小到大的顺序打印出给定区间(m,n)内所有的水仙花数。
//输入 153 400 
#include <stdio.h>

int narcissistic( int number );
void PrintN( int m, int n );

int main()
{
    int m, n;

    scanf("%d %d", &m, &n);
    if ( narcissistic(m) ) printf("%d is a narcissistic number\n", m);
    PrintN(m, n);
    if ( narcissistic(n) ) printf("%d is a narcissistic number\n", n);

    return 0;
}
int narcissistic( int number )
{
	int i,n,sum=0,m=0,a=1,b;
	n=number;
	while(n)
	{
		n/=10;
		m++;
	}
	n=number;
	while(n)
	{
		a=1;
		b=n%10;
		for(i=1;i<=m;i++)a*=b;
			n/=10;
		sum+=a;
	}
	if(sum==number)return 1;
	else return 0;
}
void PrintN( int m, int n )
{
  int i;
  for(i=m+1;i<n;i++)
  if(narcissistic(i)==1)
  printf("%d\n",i);
}

