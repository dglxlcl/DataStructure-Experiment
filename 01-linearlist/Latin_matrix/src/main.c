#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"

int main()
{
    LinkList_CL line;
    InitList_CL(&line);
    Link s;
    int i,j;
    for(i=1;i<=9;i++){
        MakeNode(&s,i);
        InsEnd_CL(&line,s);
    }
    Link p = line.head;
    for (i=1;i<=9;i++){
        p=LocatePos_CL(&line,p,1);
        for (j=1;j<=9;j++){
            printf("%d ",p->data);
            p=LocatePos_CL(&line,p,1);
        }
        printf("\n");
    }
    return 0;
}
