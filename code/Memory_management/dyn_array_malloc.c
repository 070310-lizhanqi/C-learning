#include<stdio.h>
#include<stdlib.h>

int main()
{
    int* dyn_array;//定义一个整型指针变量，用于存储动态数组的首地址
    int n;//定义一个整型变量，用于存储数组元素个数
    printf("请输入数组元素个数:");

    if(scanf("%d", &n) != 1)//判断输入是否有效
    {
        printf("输入无效\n");
        return -1;
    }
    if(n <= 0)//判断数组元素个数是否为正整数
    {
        printf("数组元素个数必须为正整数\n");
        return -1;
    }
    dyn_array = (int*)malloc((size_t)n * sizeof(int));//动态分配内存空间，存储n个整型元素
    if(dyn_array == NULL)//判断内存分配是否成功
    {
        printf("内存分配失败\n");
        return -1;
    }
    for(int i = 0; i < n; i++)//循环初始化数组元素
    {
        dyn_array[i] = i + 1;
    }
    printf("动态数组元素为:");
    for(int i = 0; i < n; i++)//循环输出数组元素
    {
        printf("%d ", dyn_array[i]);
    }
    free(dyn_array);//释放动态分配的内存空间
    return 0;
}