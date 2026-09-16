#include <stdio.h>
int main(){
    int arr[10]={0,1,2,3,4,5,6,7,8,9};
    int *p;
    p = arr;
    printf("Size of array: %lu\n", sizeof(arr));
    printf("Size of pointer: %lu\n", sizeof(p));
    return 0;
}