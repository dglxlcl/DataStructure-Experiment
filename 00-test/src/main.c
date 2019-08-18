#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void test(int **p){
    *p += 1;
}

int main(){
    int a[4]={1,2,3,4};
    int *p = &a[0];
    int **p2 = &p;
    test(p2);
    return 0;
}