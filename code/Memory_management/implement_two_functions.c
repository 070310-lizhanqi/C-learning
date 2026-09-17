#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>

char *my_strdup(const char *s)
{
    if(s==NULL)//防止传进来的字符串指针为空，若为空则返回NULL
    {
        return NULL;
    }
    size_t n=0;//定义一个整型变量n，用于存储字符串的长度
    while (s[n]) n++;//计算字符串长度，字符串以\0结尾，所以当while(s[n])为0时，n停止++。
    char *p=malloc(n+1);//为字符串分配内存空间，+1是为了存储字符串结尾的\0
    if(p==NULL) // 
    {
        return NULL;
    }
    int i;
    for(size_t i=0;i<=n;i++)//循环将字符串s的内容复制到新分配的内存空间p中，<=n是为了复制字符串结尾的\0
    {
        p[i]=s[i];
    }
    return p;//返回新分配的内存空间的首地址
}
char *my_strndup(const char *s, size_t n)
{

}

int main()
{
    char array[] = "Hello, World!";
    my_strdup(array);
    printf("%s\n", my_strdup(array));
    return 0;
}