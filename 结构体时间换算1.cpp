#include<stdio.h>
struct time
{
	int h;
	int f;
	int m;
}a;

int main(void)
{
	int n;
	scanf("%d:%d:%d\n",&a.h,&a.f,&a.m);
	scanf("%d",&n);
	a.m+=n;
	if(a.m>=60)
	{
		a.m-=60;
		a.f++;
	}
	if(a.f>=60)
	{
		a.f-=60;
		a.h++;
	}
	if(a.h>=24)
	{
		a.h-=24;
	}
	printf("%02d:%02d:%02d",a.h,a.f,a.m);
		
return 0;
}

