#include <stdio.h>
#include <stdlib.h>
#include "MyString.h"

int main(){
    HString S;
    HString T;
    HString V;
    HString SUB;
    S.ch = T.ch = V.ch= SUB.ch = NULL;
    S.length = T.length = 0;
    StrAssign_H(&S, "abcdefghijklmnopqrstuvwxyz");
    StrAssign_H(&T, "a");
    StrAssign_H(&V, "123");
    PrintStr_H(S);
    putchar('\n');
    StrDelete_H(&S,1, 4);
    PrintStr_H(S);
    // SString S;
    // SString T;
    // SString V;
    // S[0] = T[0] = V[0] = 0;
    // StrAssign_S(&S, "aaaaaaaaaa");
    // StrAssign_S(&T, "a");
    // StrAssign_S(&V, "abcdefghijklmnopqrstuvwxyz");   
    // PrintStr_S(S); 
    // putchar('\n');
    // Replace_S(&S, T, V);
    // PrintStr_S(S);
    return 0;
}