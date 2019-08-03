#include <stdio.h>
#include <stdlib.h>
#include "MyString.h"

int main(){
    HString S;
    HString T;
    HString V;
    HString SUB;
    S.ch = T.ch = V.ch=SUB.ch= NULL;
    S.length = T.length = 0;
    StrAssign_H(&S, "aa");
    StrAssign_H(&T, "3");
    StrAssign_H(&V, "abcdefghijklmnopqrstuvwxyz");
    PrintStr_H(S);
    putchar('\n');
    Replace_H(&S, T, V);
    PrintStr_H(S);
    return 0;
}