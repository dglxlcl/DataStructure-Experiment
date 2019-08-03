#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"

int main()
{
    LinkList_CL Josephus;
    InitList_CL(&Josephus);
    Link NewNode_pt=NULL;
    for(int i =1;i<=41;i++){
        MakeNode(&NewNode_pt,i);
        InsEnd_CL(&Josephus,NewNode_pt);
    }
    ListPrint_CL("%d ",&Josephus);
    printf("\n");
    int temp =1;
    Link p = Josephus.head->next;//初始化p指针，指向Josephus的圈的第一个人
    while(Josephus.length>2){
        if(3==temp){
            printf("Killed:%d ->",p->data);
            ListDelete_CL(&Josephus,&p);
            if(p==Josephus.head) p=p->next;
            temp = 1;
        }else{
            p=LocatePos_CL(&Josephus,p,1);
            temp++;
        }
    }
    printf("\n");
    printf("Lived:");
    ListPrint_CL("%d ",&Josephus);
    system("pause");
    return 0;
}
