#include<stdio.h>
#define N 10
int sort(int a[10],int n)
{
	int i,j,t;
	for(i=0;i<n-1;i++)
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]<a[j+1])
			{
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;	
			}	
		}	
}

int main(void)
{
	int a[10],i;
	printf("Please input %d numbers:\n",N);
	for(i=0;i<N;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(a,10);
	for(i=0;i<N;i++)
		printf("%d ",a[i]);
	return 0;
}
