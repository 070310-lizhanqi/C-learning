#include<stdio.h>
int main()
{
	int a=10;
	int *p=NULL;
	p=&a;
	int **q=NULL;
	q=&p;
	printf("a:%d\n",a);
	printf("*p:%d\n",*p);//*p是a的值
	printf("p:%d\n",p);//p存的是a的地址
	printf("q:%d\n",q);//q存的是p的地址
	printf("*q:%d\n",*q);//*q是p的值
	printf("**q:%d\n",**q);//**q是a的值
	return 0;
}