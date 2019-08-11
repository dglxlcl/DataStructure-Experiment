#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StackAndQueue.h"

Status InitQueue_L(LinkQueue *Q){//
    Q->head = Q->rear = (LQNode *)malloc(sizeof(LQNode));
    if(!Q->head) return ERROR;
    Q->head->next=NULL;
    Q->head->data=0;
    Q->length=0;
    return OK;
}

Status DestroyQueue_L(LinkQueue *Q){
    if( Q->head==NULL ) return ERROR;
    LQueuePtr p=Q->head->next;
    while(!Q->head){
        free(Q->head);
        Q->head=p;
        p=p->next;
    }
    Q->head=Q->rear=NULL;
    Q->length=0;
    return OK;
}

Status ClearQueue_L(LinkQueue *Q){
    if( Q->head==NULL ) return ERROR;
    LQueuePtr p=Q->head->next;
    while(!p){
        free(Q->head);
        Q->head=p;
        p=p->next;
    }
    Q->length=0;
    return OK;
}

Status QueueEmpty_L(LinkQueue Q){
    if( Q.head==NULL) return ERROR;
    if( Q.length==0 ) return TRUE;
    else return FALSE;

}

int QueueLength_L(LinkQueue Q){
    return Q.length;
}

Status GetHead_L(LinkQueue *Q,QElemType *e){
    if( Q->head==NULL) return ERROR;
    *e=Q->head->next->data;
    return OK;
}

Status EnQueue_L(LinkQueue *Q,QElemType e){
    if( Q->head==NULL) return ERROR;
    LQueuePtr newNode = (LQNode *)malloc(sizeof(LQNode));
    if(!newNode) return ERROR;
    newNode->data = e;
    newNode->next = NULL;
    Q->rear->next = newNode;
    Q->rear = newNode;
    Q->length++;
    return OK;
}

Status DeQueue_L(LinkQueue *Q,QElemType *e){
    if ( Q->length == 0 ) return ERROR;
    LQueuePtr p = Q->head->next;
    *e = p->data;
    Q->head->next=p->next;
    free(p);
    if(Q->length==1) Q->rear=Q->head;//�˴���Ϊ������ͷ�ڵ㣬���Ե�����ֻʣ1��Ԫ��ʱ��ɾ����Ҫ��βָ��ָ��ͷ�ڵ㣬��Ȼ���������һ��������Ԫ�أ�head.next����Զָ��NULL
    Q->length--;
    return OK;
}




Status InitQueue_Sq(SqQueue *Q){//
    Q->base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
    if(!Q->base) return ERROR;
    Q->head=Q->rear=0;
    return OK;
}

Status DestroyQueue_Sq(SqQueue *Q){
    if( Q->base==NULL ) return ERROR;
    free(Q->base);
    Q->head=Q->rear=0;
    return OK;
}

Status ClearQueue_Sq(SqQueue *Q){
    if( Q->base==NULL ) return ERROR;
    Q->head=Q->rear=0;
    return OK;
}

Status QueueEmpty_Sq(SqQueue Q){
    if( Q.base==NULL) return ERROR;
    if( Q.head==Q.rear ) return TRUE;
    else return FALSE;

}

int QueueLength_Sq(SqQueue Q){
    return (Q.rear+MAXQSIZE-Q.head)%MAXQSIZE;
}

Status GetHead_Sq(SqQueue *Q,QElemType *e){
    if( Q->base==NULL) return ERROR;
    *e=*(Q->base+Q->head);
    return OK;
}

Status EnQueue_Sq(SqQueue *Q,QElemType e){
    if( Q->base==NULL) return ERROR;
    if ( ((Q->rear+1)%MAXQSIZE)==Q->head ){
        printf("EnQueue_Sq:The SqQueue is full!\n");
        return ERROR;
    }
    *(Q->base+Q->rear) = e;
    Q->rear=(Q->rear+1)%MAXQSIZE;
    return OK;
}

Status DeQueue_Sq(SqQueue *Q,QElemType *e){
    if ( Q->head == Q->rear ) return ERROR;
    *e = *(Q->base+Q->head);
    Q->head=(Q->head+1)%MAXQSIZE;
    return OK;
}







