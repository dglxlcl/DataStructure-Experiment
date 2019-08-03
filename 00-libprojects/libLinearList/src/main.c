#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"
int main(){
    Sqlist L1,L2;
    L1.elem = NULL;
    L2.elem = NULL;
    InitList_Sq(&L1);
    InitList_Sq(&L2);
    ListInput_Sq("%d", &L1);
    ListInput_Sq("%d", &L2);
    ListUnion_Sq(&L1, &L2);
    ListPrint_Sq("%d ", &L1);
    system("pause");
    return 0;
}