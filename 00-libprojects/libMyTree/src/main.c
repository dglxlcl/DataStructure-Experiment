#include <stdio.h>
#include <stdlib.h>
#include "MyTree.h"
#include "StackAndQueue.h"

int main(){
    Forst F=NULL;
    PreCreatForst(&F);
    PreTranverseForst(F, PrintElem);
    return 0;
} 

