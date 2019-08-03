#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinearList.h"
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
    S->top=S->base;
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