#include<stdio.h>

typedef enum {
    INT,
    FLOAT,
    CHAR,
    STRING
} Type;

void print_type(void *p, Type type)
{
    switch(type) {
        case INT:
            printf("Type: INT, Value: %d\n", *(int *)p);
            break;
        case FLOAT:
            printf("Type: FLOAT, Value: %.2f\n", *(float *)p);
            break;
        case CHAR:
            printf("Type: CHAR, Value: %c\n", *(char *)p);
            break;
        case STRING:
            printf("Type: STRING, Value: %s\n", (char *)p);
            break;
        default:
            printf("Unknown type\n");
    }
}

int main()
{
    int a=5;
    float b=3.7;
    char c='A';
    char d[]="Hello";
    print_type(&a, INT);
    print_type(&b, FLOAT);
    print_type(&c, CHAR);
    print_type(&d, STRING);
    return 0;
}