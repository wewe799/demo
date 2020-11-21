#include<stdio.h>

struct student 
{    
	char number[100];    
	char name[100];    
	int score;
}a[10];

int main() 
{    
	int i, t, n, max=0, k;   
	int s1, s2, s3;
	    
	scanf("%d", &n);
    	for (i = 1; i <= n; i++) 
		{        
    		scanf("%s %s %d %d %d", &a[i].number, &a[i].name, &s1, &s2, &s3);        
   			a[i].score = s1 + s2 + s3; 
   		}
	for (i = 1; i <= n; i++) 
	{         
		if (max < a[i].score) 
		{            
		max = a[i].score;            
		k = i;        		      
		}    
	}    
	printf("%s %s %d", a[k].name, a[k].number, a[k].score);
	
}

