#include<stdio.h>
int main()
{
	int a[6]={1,0,1,3,1,0};
	int *p=a;
	for(int i=0;i<6;i++)
	{
		printf("%d ",*(p+i));
	}
}