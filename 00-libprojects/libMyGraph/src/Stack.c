#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StackAndQueue.h"

Status InitStack_Sq(SqStack *S){//
    S->base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base) return ERROR;
    S->top=S->base;
    S->stacksize= STACK_INIT_SIZE;
    return OK;
}

void DestroyStack_Sq(SqStack *S){
    free(S->base);
    S->top=S->base=NULL;
    S->stacksize=0;
}

void ClearStack_Sq(SqStack *S){
    S->top = S->base;
}

Status StackEmpty_Sq(SqStack *S){
    if (S->top==S->base) return TRUE;
    else return FALSE;
}

int StackLength_Sq(SqStack *S){
    return S->top-S->base;
}

Status GetTop_Sq(SqStack *S,SElemType *e){
    if(S->top == S->base) return ERROR;
    else{
        *e = *(S->top-1);
        return OK;
    }
}

Status Push_Sq(SqStack *S,SElemType e){
    if( (S->top - S->base) >= S->stacksize ){
        S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType) );
    }
    *(S->top++)=e;
    return OK;
}

Status Pop_Sq(SqStack *S,SElemType *e){
    if(S->top==S->base) return ERROR;
    *e=*(--S->top);
    return OK;
}

Status LocateElem_Sqstack(SqStack *S,SElemType e,Status (*compare)(SElemType,SElemType)){
    SElemType *p=S->base;
    while(p!=S->top){
        if( (*compare)(e,*p) ){
            return OK;
        }else p++;
    }
    return ERROR;
}




Status InitStack_charSq(charSqStack *S){
    S->base = (char *)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!S->base) return ERROR;
    S->top=S->base;
    S->stacksize= STACK_INIT_SIZE;
    return OK;
}

void DestroyStack_charSq(charSqStack *S){
    free(S->base);
    S->top=S->base;
    S->stacksize=0;
}

void ClearStack_charSq(charSqStack *S){
    S->top = S->base;
}

Status StackEmpty_charSq(charSqStack *S){
    if (S->top==S->base) return TRUE;
    else return FALSE;
}

int StackLength_charSq(charSqStack *S){
    return S->top-S->base;
}

Status GetTop_charSq(charSqStack *S,char *e){
    if(S->top == S->base) return ERROR;
    else{
        *e = *(S->top-1);
        return OK;
    }
}

Status Push_charSq(charSqStack *S,char e){
    if( (S->top - S->base) >= S->stacksize ){
        S->base=(char *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(char) );
    }
    *(S->top++)=e;
    return OK;
}

Status Pop_charSq(charSqStack *S,char *e){
    if(S->top==S->base) return ERROR;
    *e=*(--S->top);
    return OK;
}

Status LocateElem_charcharSqStack(charSqStack *S,char e,Status (*compare)(char,char)){
    char *p=S->base;
    while(p!=S->top){
        if( (*compare)(e,*p) ){
            return OK;
        }else p++;
    }
    return ERROR;
}






Status InitStack_L(LinkStack *S){//
    S->base = (StackNode *)malloc(sizeof(StackNode));
    if(!S->base) return ERROR;
    S->top=S->base;
    S->base->next=NULL;
    S->base->data=0;
    S->length=0;
    return OK;
}

void DestroyStack_L(LinkStack *S){
    StackNode_pt p=S->top->next;
    while (!S->top){
        free(S->top);
        S->top=p;
        p=p->next;
    }
    S->base=S->top=NULL;
    S->length=0;
}

void ClearStack_L(LinkStack *S){
    StackNode_pt p=S->top->next;
    while (!p){
        free(S->top);
        S->top=p;
        p=p->next;
    }
    S->base->data=0;
    S->length=0;
}


Status StackEmpty_L(LinkStack *S){
    if (S->top==S->base) return TRUE;
    else return FALSE;
}

int StackLength_L(LinkStack *S){
    return S->length;
}

Status GetTop_L(LinkStack *S,SElemType *e){
    if(S->length == 0) return ERROR;
    else{
        *e = S->top->next->data;
        return OK;
    }
}

Status Push_L(LinkStack *S,SElemType e){
    S->top->data = e;
    StackNode_pt New_pt =(StackNode *)malloc( sizeof(StackNode) );
    New_pt->data = 0;
    New_pt->next=S->top;
    S->top=New_pt;
    S->length++;
    return OK;
}

Status Pop_L(LinkStack *S,SElemType *e){
    if( S->length==0 ) return ERROR;
    StackNode_pt p = S->top->next;
    *e = p->data;
    free(S->top);
    S->top=p;
    p->data=0;
    S->length--;
    return OK;
}





