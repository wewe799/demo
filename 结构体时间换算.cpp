#include<stdio.h>
#include<string.h>
struct t_type{
	int h;
	int m;
	int s;
}t1,t2;
int main()
{
	int time;
	scanf("%d:%d:%d",&t1.h,&t1.m,&t1.s);
    scanf("%d",&time);
	t2.s=(t1.s+time)%60;
	t2.m=(t1.m+(t1.s+time)/60)%60;
	t2.h=(t1.h+( ( t1.m+( t1.s+time )/60 )/60 ) )%24;
	printf("%02d:%02d:%02d",t2.h,t2.m,t2.s);
}

