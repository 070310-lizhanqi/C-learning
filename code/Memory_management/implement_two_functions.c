#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

/* 题目：
   复制整个字符串到新分配的堆内存；失败返回 NULL； s == NULL 返回 NULL
   最多复制 n 个字符并补 '\0'；失败返回 NULL； s == NULL 返回 NULL
*/

/* 复制整个字符串到新分配的堆内存(连同结尾的 '\0')；失败返回 NULL；s == NULL 返回 NULL */
char *my_strdup(const char *s)
{
    if(s==NULL)//传入空指针无法解引用，直接返回 NULL
    {
        printf("传入的字符串指针为空\n");//必须先打印再返回，写在 return 后面永远执行不到
        return NULL;
    }
    size_t n=0;//n 用于存储字符串的长度(不包含结尾的 '\0')
    while (s[n]) n++;//字符串以\0结尾，所以当while(s[n])为0时，n停止++。
    char *p=malloc(n+1);//为字符串分配内存空间，+1是为了存储字符串结尾的\0
    if(p==NULL)
    {
        printf("内存分配失败\n");//同上：打印要放在 return 前面
        return NULL;
    }
    for(size_t i=0;i<=n;i++)//循环将字符串s的内容复制到新分配的内存空间p中，<=n是为了复制字符串结尾的\0
    {
        p[i]=s[i];
    }
    return p;//返回新分配的内存空间的首地址，由调用者负责 free
}

/* 最多复制 n 个字符并补 '\0'；失败返回 NULL；s == NULL 返回 NULL */
char *my_strndup(const char *s, size_t n)
{
    if(s==NULL)//传入空指针无法解引用，直接返回 NULL
    {
        printf("传入的字符串指针为空\n");
        return NULL;
    }
    size_t len=0;//len 表示实际要复制的字符数，最多不超过 n
    //两个条件缺一不可：len<n 保证不超过 n 个字符；
    //s[len] 保证遇到 '\0' 就停，所以 s 比 n 短时不会越界读到字符串以外的内存
    while(len<n && s[len]) len++;
    char *p=malloc(len+1);//按实际长度分配，+1 用于存放结尾的 '\0'
    if(p==NULL)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    for(size_t i=0;i<len;i++)
    {
        p[i]=s[i];//循环将字符串s的前len个字符复制到新分配的内存空间p中
    }
    p[len]='\0';//在字符串末尾添加结束符(n==0 时这里也能正确得到空串)
    return p;//返回新分配的内存空间的首地址，由调用者负责 free
}

int main()
{
    const char *src = "Hello, World!";
    size_t n = strlen(src);

    /* ---------- my_strdup ---------- */
    char *a = my_strdup(src);
    assert(a != NULL);//分配必须成功
    assert(strcmp(a, src) == 0);//复制出来的内容要和源字符串完全一致
    printf("my_strdup       : %s\n", a);
    free(a);

    assert(my_strdup(NULL) == NULL);//s == NULL 时必须返回 NULL

    /* ---------- my_strndup ---------- */
    //用例1：n 等于原串长度，结果应与原串相同
    char *b = my_strndup(src, n);
    assert(b != NULL && strcmp(b, src) == 0);
    printf("my_strndup(n)   : %s\n", b);
    free(b);

    //用例2：n 小于原串长度，截断，只取前 n 个字符
    char *c = my_strndup(src, 5);
    assert(c != NULL && strcmp(c, "Hello") == 0);
    printf("my_strndup(5)   : %s\n", c);
    free(c);

    //用例3：n 大于原串长度，s 提前遇到 '\0' 就停，不能越界读
    char *d = my_strndup("Hi", 5);
    assert(d != NULL && strcmp(d, "Hi") == 0);
    printf("my_strndup(Hi,5): %s\n", d);
    free(d);

    //用例4：n == 0，返回空字符串
    char *e = my_strndup(src, 0);
    assert(e != NULL && e[0] == '\0');
    printf("my_strndup(0)   : [%s]\n", e);
    free(e);

    assert(my_strndup(NULL, 5) == NULL);//s == NULL 时必须返回 NULL

    printf("全部测试通过\n");
    return 0;
}