#include <stdio.h>
int *swap(int *a, int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
    return a;
}

int main()
{
    int i=10,j=20;
    int *c=swap(&i,&j);
    printf("%d %d\n",i,j);
    printf("%d\n",*c);
    return 0;
}