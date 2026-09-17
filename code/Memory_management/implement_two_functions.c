#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char *my_strdup(const char *s)
{
    if(s==NULL)//防止传进来的字符串指针为空，若为空则返回NULL
    {
        return NULL;
        printf("传入的字符串指针为空\n");
    }
    size_t n=0;//定义一个整型变量n，用于存储字符串的长度
    if(n==SIZE_MAX) //防止溢出，若n等于SIZE_MAX，则返回NULL
    {
        return NULL;
    }
    while (s[n]) n++;//计算字符串长度，字符串以\0结尾，所以当while(s[n])为0时，n停止++。
    char *p=malloc(n+1);//为字符串分配内存空间，+1是为了存储字符串结尾的\0
    if(p==NULL) // 
    {
        return NULL;
    }
    for(size_t i=0;i<=n;i++)//循环将字符串s的内容复制到新分配的内存空间p中，<=n是为了复制字符串结尾的\0
    {
        p[i]=s[i];
    }
    return p;//返回新分配的内存空间的首地址
}
char *my_strndup(const char *s, size_t n)
{
    if(n==SIZE_MAX) //防止溢出，若n等于SIZE_MAX，则返回NULL
    {
        return NULL;
    }
    if(s==NULL)//防止传进来的字符串指针为空，若为空则返回NULL
    {
        return NULL;
        printf("传入的字符串指针为空\n");
    }
    char* p=malloc(n+1);//为字符串分配内存空间，+1是为了存储字符串结尾的\0
    if(p==NULL) // 
    {
        return NULL;
        printf("内存分配失败\n");
    }
    for(size_t i=0;i<n;i++)
    {
        p[i]=s[i];//循环将字符串s的前n个字符复制到新分配的内存空间p中
    }
    p[n]='\0';//在字符串末尾添加结束符
    return p;//返回新分配的内存空间的首地址
}

int main()
{
    char array[] = "Hello, World!";
    size_t n=strlen(array);
    char *a=my_strdup(array);
    char *b=my_strndup(array,n);
    printf("my_strdup: %s\n", a);
    printf("my_strndup: %s\n", b);
    free(a);
    free(b);
    return 0;
}