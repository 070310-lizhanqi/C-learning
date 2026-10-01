#include <stdio.h>

int main()
{
    int x=1,y=2;
    { 
        int x=2;
        { int x=3;
            printf("x=%d,y=%d\n",x,y); // x=3，这里用最内层的x
        }
        printf("x=%d,y=%d\n",x,y);   // x=2，退出内层，用第二层x
    }
    printf("x=%d,y=%d\n",x,y);       // x=1，全部退出，用最外层x
    int ch=getchar();
    putchar(ch);
    return 0;
}