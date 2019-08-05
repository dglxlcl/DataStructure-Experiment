#include <stdio.h>
#include <stdlib.h>
#include "MyArray.h"

int main(){
    Array A;
    InitArray(&A, 3,4,4,4);
    ElemType e,e1,e2,e3;
    e1=111;
    e2=222;
    e3=333;
    Assign(&A, e1,0,0,0);
    Assign(&A, e2,0,0,1);
    Assign(&A, e3,3,3,3);
    Value(A, &e,3,3,3);
    printf("e=%d\n",e);
    return 0;
}

