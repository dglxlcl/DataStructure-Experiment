#include <stdio.h>
#include <stdlib.h>
#include "MyTree.h"


int main(){
    BiTree T = NULL;
    PreCreatBiTree(&T);
    PostOrderTranverseBiTree(T, PrintElem);
    return 0;
} 