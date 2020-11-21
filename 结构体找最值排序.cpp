#include<stdio.h>
#include<string.h>
#define N 10
struct {
	int num;
	int score;
}t,s[N];
main()
{
	int max,i,j,n;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d %d",&s[i].num,&s[i].score);
	}
	for(i=0;i<n-1;i++)
	{
		max=i;
		for(j=i+1;j<n;j++)
		{
			if(s[max].score<s[j].score)
			{
				max=j;
			}
		}
		if(max!=i)
		{
			t=s[max];
			s[max]=s[i];
			s[i]=t;
		} 
	}
	printf("%d %d\n",s[0].num,s[0].score);
}

