#include<stdio.h>
struct type
{
	double cash;
	char name[101];
};

int main()
{
	int i,n;
	struct type s1,max,min;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
    {
		scanf("\n");
	  gets(s1.name);
		scanf("%lf",&s1.cash);
		if(i==1)max=min=s1;
		if(max.cash<s1.cash)max=s1;
		if(min.cash>s1.cash)min=s1;
	}
	printf("%.2lf, %s\n",max.cash,max.name);
	printf("%.2lf, %s",min.cash,min.name);
}

