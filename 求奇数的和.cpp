//����N�����������������ĺͣ�ͬʱʵ��һ���ж���ż�Եĺ�����
#include <stdio.h>

#define MAXN 10

int even( int n );
int OddSum( int List[], int N );

int main()
{    
    int List[MAXN], N, i;

    scanf("%d", &N);
    printf("Sum of ( ");
    for ( i=0; i<N; i++ ) {
        scanf("%d", &List[i]);
        if ( even(List[i])==0 )
            printf("%d ", List[i]);
    }
    printf(") = %d\n", OddSum(List, N));

    return 0;
}
int even (int n)
{
	if(n%2==0)
	return 1;
	else return 0;
}
int OddSum(int List[],int N)
{
	int a=0,i;
	for(i=0;i<N;i++)
	{
		if(even(List[i])==0)
		 	a+=List[i];
	}
	return a;
}
