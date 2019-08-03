#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinearList.h"



//分配由P指向的值为e的单链表结点，并返回OK，若分配失败，则返回ERROR
Status MakeNode(Link *p,ElemType e){
    *p=(Link)malloc(sizeof(LNode));
    if(!(*p)) return ERROR;
    else{
        (*p)->data=e;
        return OK;
    }
}

//分配由P指向的值为e的双向链表结点，并返回OK，若分配失败，则返回ERROR
Status MakeDuLNode(DuLink *p,ElemType e){
    *p=(DuLink)malloc(sizeof(DuLNode));
    if(!(*p)) return ERROR;
    else{
        (*p)->data=e;
        return OK;
    }
}

//初始化一个单链表为空表
Status InitList_L(LinkList_L *L){
    Link HeadNode;
    if(!MakeNode(&HeadNode,0)) return ERROR;
    L->head=HeadNode;
    L->tail=HeadNode;
    L->head->next=NULL;//单链表为空时，头结点的next指针为NULL
    L->length=0;
    return OK;
}


//初始化一个双向链表为空表
Status InitList_DuL(LinkList_DuL *L){
    DuLink HeadNode;
    if(!MakeDuLNode(&HeadNode,0)) return ERROR;
    L->head=HeadNode;
    L->tail=HeadNode;
    L->head->next=NULL;//双向链表为空时，头结点next指针为NULL
    L->head->prior=NULL;//双向链表为空时，头结点的prior指针为空
    L->length=0;
    return OK;
}



//销毁一个单链表
Status DestroyList_L(LinkList_L *L){
    if(!(L->head)) {//当单链表没有头结点时，表示单链表尚未初始化或不存在
        printf("DestroyList_L:LinkList_L has not been Initiallized!\n");
        return ERROR;
    }
    Link p,q;
    p=L->head;
    while(p){//单链表最后一个结点的next为NULL，当p指向最后一个节点的下一个结点时，跳出循环
        q=p->next;
        free(p);
        p=q;
    }
    L->head=NULL;
    L->tail=NULL;
    L->length=0;
    printf("DestroyList_L:LinkList_L has been Destroyed.\n");
    return OK;
}



//销毁一个双向链表
Status DestroyList_DuL(LinkList_DuL *L){
    if(!(L->head)) return ERROR;
    DuLink p,q;
    p=L->head;
    while(p){
        q=p->next;
        free(p);
        p=q;
    }
    L->head=NULL;
    L->tail=NULL;
    L->length=0;
    return OK;
}



//将单链表重置为空表，并释放原链表的空间
Status ClearList_L(LinkList_L *L){
    if(!(L->head)) {
        printf("ClearList_L:LinkList_L has not been Initiallized!\n");
        return ERROR;
    }
    Link p=L->head;
    Link q=p->next;
    while(q){
        p->next=q->next;
        free(q);
        q=p->next;
    }
    L->tail=L->head;
    L->length=0;
    printf("ClearList_L:LinkList_L has been set to empty.\n");
    return OK;
}



//将双向链表重置为空表，并释放原链表的空间
Status ClearList_DuL(LinkList_DuL *L){
    if(!(L->head)) return ERROR;
    DuLink p=L->head;
    DuLink q=p->next;
    while(q){
        p->next=q->next;
        free(q);
        q=p->next;
    }
    L->tail=L->head;
    L->head->prior=NULL;
    L->head->next=NULL;
    L->length=0;
    return OK;
}



//已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
Status InsFirst_L(LinkList_L *L,Link s){
    Link h= L->head;
    if((h==NULL)||(s==NULL)) return ERROR;
    s->next=h->next;
    h->next=s;
    return OK;
}

//已知h指向线性链表的头结点，删除链表中的第一个结点并以q返回
Status DelFirst_L(LinkList_L *L,Link *q){
    if(L->head->next==NULL) return ERROR;
    Link h= L->head;
    *q=h->next;
    h->next=(*q)->next;
    (*q)->next=NULL;
    L->length--;
    return OK;
}

//将指针s所指的一串结点连接在线性链表的最后一个结点,之后改变链表L的尾指针指向新的尾结点。s串必须是单链表
Status Append_L(LinkList_L *L,Link s){
    if(!(L->head)) return ERROR;
    L->tail->next = s;
    Link p = L->tail;
    Link q = p->next;
    while(q){
        p=q;
        q=q->next;
        L->length++;
    }
    L->tail=p;
    return OK;
}

//删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
Status DelEnd_L(LinkList_L *L,Link *q){
    if(L->tail==L->head){
        printf("Remove_L:The LinkList_L is empty!\n");
        return ERROR;
    }
    *q = L->tail;
    (*q)->next=NULL;
    Link p1 = L->head;
    Link p2 = p1->next;
    while(p2!=(*q)){
        p1=p2;
        p2=p2->next;
    }
    p1->next=NULL;
    L->length--;
    L->tail=p1;
    return OK;
}

//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前，并修改指针p指向新插入的结点
Status InsBefore_L(LinkList_L *L,Link *p,Link s){
    if((*p)==NULL||(*p)==L->head) return ERROR;
    Link q1 = L->head;
    Link q2 = q1->next;
    while( (q2!= (*p)) && q2){
        q1=q2;
        q2=q2->next;
    }if(!q2) return ERROR;
    q1->next=s;
    s->next= (*p);
    (*p)=s;
    L->length++;
    return OK;
}

//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后，并修改p指向新插入的结点。该操作必须保证p在表中，不然会出错，而且很难调试
Status InsAfter_L(LinkList_L *L,Link *p,Link s){
    if((*p)== NULL ) return ERROR;
    s->next = (*p)->next;
    (*p)->next=s;
    (*p)=s;
    L->length++;
    return OK;
}

//已知p指向线性链表中的一个结点，用e更新p所指结点中的数据元素的值
Status SetCurElem_L(Link *p,ElemType e){
    (*p)->data=e;
    return OK;
}

//已知p指向线性链表中的一个结点，返回p所指结点中的数据元素的值
ElemType GetCurElem_L(Link p){
    return p->data;
}

//若线性表L为空表，则返回TRUE，否则返回FALSE
Status ListEmpty_L(LinkList_L *L){
    if( (L->head)&&(L->length==0) ) return TRUE;
    else return FALSE;
}

//返回线性链表L中元素个数
int ListLength_L(LinkList_L *L){
    if( !(L->head) ) return ERROR;
    else return L->length;
}

//返回线性链表L中头结点的位置
Link GetHead_L(LinkList_L *L){
    if( !(L->head) ) return NULL;
    else return L->head;
}

//返回线性链表L中最后一个结点的位置
Link GetLast_L(LinkList_L *L){
    if( !(L->head) ) return NULL;
    else return L->tail;
}

//已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置
Link PriorPos_L(LinkList_L *L,Link p){
    if( !(L->head) || L->length ==0 || p==L->head) return NULL;
    Link q1 = L->head;
    Link q2 = q1->next;
    while((q2!=p)&&q2){
        q1=q2;
        q2=q2->next;
    }
    if(!q2) return NULL;
    else return q1;
}

//已知p指向线性链表L中的一个结点，返回p所指结点的直接后驱的位置
Link NextPos_L(LinkList_L *L,Link p){
    if(!p) return NULL;
    else return p->next;
}

//返回p指示线性链表L中第i个结点的位置并返回OK，i值不合法时返回ERROR
Status LocatePos_L(LinkList_L *L,int i,Link *p){
    if( i<0||i>L->length ){
        printf("LocatePos_L:the value of index i is illegal!\n");
        return ERROR;
    }
    int j=0;
    Link q=L->head;
    for(j=0;j<i;j++){
        if(!q) break;
        q=q->next;
    }
    if( j<i || (!q) ) return ERROR;
    else {
        *p=q;
        return OK;
    }
}

//返回线性链表L中第1个与e满足函数ompare()判定关系的元素的位置，若不存在这样的元素，则返回NULL；
Link LocateElem_L(LinkList_L *L,ElemType e,Status (*compare)(ElemType,ElemType)){
    if(!(L->head) || L->length ==0 ) {
        printf("LocateElem:The LinkList_L is not initialized or empty!\n");
        return NULL;
    }
    int i=1;
    Link p=L->head->next;
    do{
        if ( (*compare)(e,p->data) ) {
            printf("LocateElem:The index of ElemType %d is %d.\n",e,i);
            return p;
        }
        else {
            p=p->next;
            i++;
        }
    }while(p);
    printf("LocateElem:Can't find ElemType %d\n",e);
    return NULL;
}

//依次对L的每个元素调用函数visit（），一旦visit()失败，就操作失败。
Status ListTraverse_L( LinkList_L *L, Status (*visit)() ){
    if( !L->head ) return ERROR;
    Link p=L->head;
    while( p ){
        p=p->next;
        if( (*visit)() ) continue;
        else return ERROR;
    }
    return OK;
}

Status ListDelete_L(LinkList_L *L,int i,Link *p){
    if(i<=0||i>L->length) return ERROR;
    Link q;
    LocatePos_L(L,i-1,&q);
    *p=q->next;
    q->next=(*p)->next;
    L->length--;
    return OK;

}

Status ListInput_L(const char *format,LinkList_L *L){
    char ch = 0;
    Link newNode;
    ElemType newdata;
    int temp = sizeof(ElemType);
    if(1==temp){
        printf("请输入单链表的字符，按回车结束输入。\n");
        while(1){
            scanf(format,&ch);
            if(ch=='\n') break;
            else {
                if(!MakeNode(&newNode,ch)) return ERROR;
                newNode->next=NULL;
                L->tail->next=newNode;
                L->tail=newNode;
                L->length++;
            }
        }
        printf("CharType data received\n");

    }else{
        printf("请输入单链表的数值，数值之间用空格隔开，按回车结束输入。\n");
        do{
            scanf("%*[ ]");
            if( (scanf("%1[\n]",&ch)) ) break;
            if ( scanf(format,&newdata) ) {
                if(!MakeNode(&newNode,newdata)) return ERROR;
                newNode->next=NULL;
                L->tail->next=newNode;
                L->tail=newNode;
                L->length++;
            }else break;
            ch=getchar();
            if(ch=='\n') break;
            scanf("%*[ ]");
            if( (scanf("%1[\n]",&ch)) ) break;

        }while( ch==' ');
        if((ch!=10)) {scanf("%*[^\n]");scanf("%*c");}
        printf("NumType data received\n");
    }
    return OK;
}

Status ListPrint_L(const char *format,LinkList_L *L){
    if(NULL==L->head){
        printf("ListPrint_L:LinkList_L has not been initiallized!\n");
        return ERROR;
    }
    if(0==L->length||NULL==L->head->next){
        printf("ListPrint_L:LinkList_L is empty!\n");
        return OK;
    }
    Link p=L->head->next;
    while(p){
        printf(format,p->data);
        p=p->next;
    }
    printf("Lenth:%d\n",L->length);
    return OK;
}

Status MergeList_L(LinkList_L *L1,LinkList_L *L2,LinkList_L *L3){
    if(!InitList_L(L3)) return ERROR;

    Link p1 = L1->head->next;
    Link p2 = L2->head->next;
    Link q = NULL;
    while (p1&&p2){
        if ( (p1->data) <= (p2->data) ) {
            p1=p1->next;
            DelFirst_L(L1,&q);
            Append_L(L3,q);

        }else {
            p2=p2->next;
            DelFirst_L(L2,&q);
            Append_L(L3,q);
        }
    }
    if (p1) {
        Append_L(L3,p1);
        L1->head->next=NULL;//断开L1剩余元素
        L1->tail=L1->head;
        DestroyList_L(L2);
    }
    else {
        Append_L(L3,p2);
        L2->head->next=NULL;//断开L2剩余元素
        L2->tail=L2->head;
        DestroyList_L(L2);
    }

    return OK;
}



