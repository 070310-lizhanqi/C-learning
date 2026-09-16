#include<stdio.h>
int main()
{
    int a=3,b=1,c=7;
    int const *p=NULL;
    p=&a;
    printf("%d %d\n",p,&a);
    printf("%d\n",*p);
    p=&b;
    printf("%d %d\n",p,&b);
    printf("%d\n",*p);
    //*p=c;
    //在const的修饰下*p是只读的，不能直接修改*p的值，但是可以通过修改指针p指向的地址来改变*p的值。
    int *const q=&c;
    printf("%d %d\n",q,&c);
    *q=5;
    printf("%d %d\n",*q,q);
    //在const的修饰下q是只读的，不能直接修改q的值，但是可以通过修改指针q指向的地址来改变*q的值。
    return 0;
}
//总结：用const修饰时，靠近const的变量是只读的。在修饰指针时，const在*前不能改变*（变量），但是可以改变指针的指向；const在*后不能改变指针，但是可以改变指针指向的变量。
