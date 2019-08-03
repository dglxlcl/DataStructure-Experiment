#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinearList.h"




//初始化一个单循环链表为空表
Status InitList_CL(LinkList_CL *L){
    Link HeadNode = NULL;
    if(!MakeNode(&HeadNode,0)) return ERROR;
    L->head=HeadNode;
    L->rear=HeadNode;
    L->head->next=HeadNode;//单循环链表为空时，头结点的next指针指向自己
    L->length=0;
    return OK;
}

//初始化一个双向循环链表为空表
Status InitList_DuCL(LinkList_DuL *L){
    DuLink HeadNode;
    if(!MakeDuLNode(&HeadNode,0)) return ERROR;
    L->head=HeadNode;
    L->tail=HeadNode;
    L->head->next=HeadNode;//双向链表为空时，头结点next指针指向自己
    L->head->prior=HeadNode;//双向链表为空时，头结点prior指针指向自己
    L->length=0;
    return OK;
}

//销毁一个单链循环表
Status DestroyList_CL(LinkList_CL *L){
    if(!(L->head)){
        printf("DestroyList_CL:LinkList_CL has not been Initiallized!\n");
        return ERROR;
    }
    Link p,q;
    p=L->head;
    do{
        q=p->next;
        free(p);
        p=q;
    }while(q!=L->head);
    free(L);
    printf("DestroyList_CL:LinkList_CL has been Destroyed.\n");
    return OK;
}


//销毁一个双向循环链表
Status DestroyList_DuCL(LinkList_DuL *L){
    if(!(L->head)) return ERROR;
    DuLink p,q;
    p=L->head;
    do{
        q=p->next;
        free(p);
        p=q;
    }while(q!=(L->head));
    L->head=NULL;
    L->tail=NULL;
    L->length=0;
    return OK;
}

//将单循环链表重置为空表，并释放原链表的空间
Status ClearList_CL(LinkList_CL *L){
    if(!(L->head)){
        printf("ClearList_CL:LinkList_CL has not been Initiallized!\n");
        return ERROR;
    }
    if(0==L->length) return OK;//如果表的长度为0，则什么也不做，直接返回OK
    Link p=L->head->next;
    Link q=NULL;
    do{
        q=p->next;
        free(p);
        p=q;
    }while(q!=L->head);
    L->rear=L->head;
    L->head->next=L->head;
    L->length=0;
    printf("ClearList_CL:LinkList_CL has been set to empty.\n");
    return OK;
}

//将双向循环链表重置为空表，并释放原链表的空间
Status ClearList_DuCL(LinkList_DuL *L){
    if(!(L->head)) return ERROR;
    DuLink p=L->head;
    DuLink q=p->next;
    while(q!=p){
        p->next=q->next;
        free(q);
        q=p->next;
    }
    L->tail=L->head;
    L->head->next=L->head;
    L->head->prior=L->head;
    L->length=0;
    return OK;
}

//头插法
Status InsFirst_CL(LinkList_CL *L,Link s){
    if( (!L->head) || (NULL==s) ){
        printf("InsFirst_CL:LinkList_CL or Link s has not been Initiallized!\n");
        return ERROR;
    }
    Link h = L->head;
    s->next=h->next;
    h->next=s;
    if(0==L->length) L->rear=s;
    L->length++;
    return OK;
}

//已知p指向线性循环链表L中的一个结点，将s所指结点插入在p所指结点之后，并修改p指向新插入的结点。该操作必须保证p在表中，不然会出错，而且很难调试
Status InsAfter_CL(LinkList_CL *L,Link *p,Link s){
    if( (!L->head) || (NULL==(*p)) ||(NULL==s) ){
        printf("InsFirst_CL:LinkList_CL or Link has not been Initiallized!\n");
        return ERROR;
    }
    s->next=(*p)->next;
    (*p)->next=s;
    if(*p==L->rear) L->rear=s;
    *p=s;
    L->length++;
    return OK;
}

//尾插法
Status InsEnd_CL(LinkList_CL *L,Link s){
    if( (!L->head) || (NULL==s) ){
    printf("InsEnd_CL:LinkList_CL or Link s has not been Initiallized!\n");
    return ERROR;
    }
    Link r = L->rear;
    s->next=r->next;
    r->next=s;
    L->rear=s;
    L->length++;
    return OK;
}

//获取p指针的前一个结点
Link PriorPos_CL(LinkList_CL *L,Link p){
    if((!L->head) ||0==(L->length) ) {
        printf("PriorPos_CL:The LinkList_CL is empty or not Initialized!\n");
        return NULL;
    }
    Link q1=L->head;
    Link q2=q1->next;
    while( (q2!= p) && (q2!=L->head) ){
        q1=q2;
        q2=q2->next;
    }
    if(q2==L->head){
        printf("PriorPos:Find not Link p\n");
        return NULL;
    }
    else return q1;
}

//获取循环表表L中p指针后的第i个元素的地址(查找过程中遇到头指针自动跳过)
Link LocatePos_CL(LinkList_CL *L,Link p ,int i){
    if( (!L->head) || (NULL==p) ){
        printf("LocatePos_CL:LinkList_CL or Link s has not been Initiallized!\n");
        return NULL;
    }
    if( L->head->next==L->head ) {        //如果L是空表，则立刻跳出，防止进入死循环
        printf("LocatePos_CL:LinkList_CL is empty!\n");
        return NULL;
    }
    Link q = p;

    for(int j = 0;j<i;j++){
        q=q->next;
        if(q==L->head) j--;
    }
    if(q==L->head) q=q->next;
    return q;
}

//删除p指针所指的结点，并将p指针指向下一个结点
Status ListDelete_CL(LinkList_CL *L,Link *p){
    if( (!L->head) || (NULL==(*p)) ){
        printf("ListDelete_CL:LinkList_CL or Link p has not been Initiallized!\n");
        return ERROR;
    }
    if( (*p) == L->head) {
        printf("ListDelete_CL:Can't delete the head node!\n");
        return ERROR;
    }
    Link prior = PriorPos_CL(L,*p);
    prior->next=(*p)->next;
    free(*p);
    *p=prior->next;
    L->length--;
    return OK;
}

Status ListPrint_CL(const char *format,LinkList_CL *L){
    if(NULL==L->head){
        printf("ListPrint_CL:LinkList_CL has not been initiallized!\n");
        return ERROR;
    }
    if(0==L->length||L->head==L->head->next){
        return OK;
    }
    Link p=L->head->next;
    while(p!=L->head){
        printf(format,p->data);
        p=p->next;
    }
    printf("Lenth:%d\n",L->length);
    return OK;
}








