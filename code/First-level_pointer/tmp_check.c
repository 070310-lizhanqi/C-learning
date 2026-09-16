#include <stdio.h>
int main(void)
{
    int a[6] = {1,0,1,3,1,0};
    int *p = a;
    for (int i = 0; i < 6; i++)
    {
        printf("%d\n", *(p + i));
    }
    return 0;
}
