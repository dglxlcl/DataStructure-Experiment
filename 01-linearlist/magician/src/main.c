#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"

int main()
{
    LinkList_CL card;
    InitList_CL(&card);
    Link s;
    int i,j;
    for(i=1;i<=13;i++){
        MakeNode(&s,0);
        InsEnd_CL(&card,s);
    }
    Link p = card.head;
    for(i=1;i<=13;i++){
        j=1;
        while(j<=i){//找到牌i的位置
            p=LocatePos_CL(&card,p,1);
            while(p->data!=0){
                p=p->next;
            }
            j++;
        }
        p->data=i;
    }
    ListPrint_CL("%d ",&card);
    return 0;
}
