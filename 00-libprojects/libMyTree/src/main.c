#include <stdio.h>
#include <stdlib.h>
#include "MyTree.h"
#include "StackAndQueue.h"

int main(){
    Forst F=NULL;
    PreOrderCreatForst(&F);
    PreOrderTranverseForst(F, PrintElem);
    // InOrderTranverseForst(F, PrintElem);
    // Tree T;
    // PreRootCreatTree(&T);
    // PostRootTranverseTree(T,PrintElem);
    return 0;
} 

