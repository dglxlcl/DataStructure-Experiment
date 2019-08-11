#ifndef STACKANDQUEUE_H_INCLUDED
#define STACKANDQUEUE_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAXQSIZE 10

#include "MyTree.h"

typedef int Status;

typedef BiTree SElemType;

typedef BiTree QElemType;

// typedef int SElemType;//当使用二叉树顺序结构时，使用这个定义

// typedef int QElemType;//当使用二叉树顺序结构时，使用这个定义




typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

typedef struct{
    char *base;
    char *top;
    int stacksize;
}charSqStack;



//链栈的元素结点定义
typedef struct StackNode{
    SElemType data;
    struct StackNode *next;
}StackNode,*StackNode_pt;

//链栈的定义
typedef struct{
    StackNode_pt top,base;
    int length;
}LinkStack;



//链队列的元素结点定义
typedef struct LQNode{
    SElemType data;
    struct LQNode *next;
}LQNode,*LQueuePtr;

//链队列的定义
typedef struct LinkQueue{
    LQueuePtr head,rear;
    int length;
}LinkQueue;

//循环队列的定义
typedef struct SqQueue{
    int head,rear;
    QElemType *base;
}SqQueue;


extern Status InitStack_Sq(SqStack *S);

extern void DestroyStack_Sq(SqStack *S);

extern void ClearStack_Sq(SqStack *S);

extern Status StackEmpty_Sq(SqStack *S);

extern int StackLength_Sq(SqStack *S);

extern Status GetTop_Sq(SqStack *S,SElemType *e);

extern Status Push_Sq(SqStack *S,SElemType e);

extern Status Pop_Sq(SqStack *S,SElemType *e);

extern Status LocateElem_Sqstack(SqStack *S,SElemType e,Status (*compare)(SElemType,SElemType));

extern Status InitStack_charSq(charSqStack *S);

extern void DestroyStack_charSq(charSqStack *S);

extern void ClearStack_charSq(charSqStack *S);

extern Status StackEmpty_charSq(charSqStack *S);

extern int StackLength_charSq(charSqStack *S);

extern Status GetTop_charSq(charSqStack *S,char *e);

extern Status Push_charSq(charSqStack *S,char e);

extern Status Pop_charSq(charSqStack *S,char *e);

extern Status LocateElem_charcharSqStack(charSqStack *S,char e,Status (*compare)(char,char));

extern Status InitStack_L(LinkStack *S);

extern void DestroyStack_L(LinkStack *S);

extern void ClearStack_L(LinkStack *S);

extern Status StackEmpty_L(LinkStack *S);

extern int StackLength_L(LinkStack *S);

extern Status GetTop_L(LinkStack *S,SElemType *e);

extern Status Push_L(LinkStack *S,SElemType e);

extern Status Pop_L(LinkStack *S,SElemType *e);

extern Status InitQueue_L(LinkQueue *Q);

extern Status DestroyQueue_L(LinkQueue *Q);

extern Status ClearQueue_L(LinkQueue *Q);

extern Status QueueEmpty_L(LinkQueue Q);

extern int QueueLength_L(LinkQueue Q);

extern Status GetHead_L(LinkQueue *Q,QElemType *e);

extern Status EnQueue_L(LinkQueue *Q,QElemType e);

extern Status DeQueue_L(LinkQueue *Q,QElemType *e);

extern Status InitQueue_Sq(SqQueue *Q);

extern Status DestroyQueue_Sq(SqQueue *Q);

extern Status ClearQueue_Sq(SqQueue *Q);

extern Status QueueEmpty_Sq(SqQueue Q);

extern int QueueLength_Sq(SqQueue Q);

extern Status GetHead_Sq(SqQueue *Q,QElemType *e);

extern Status EnQueue_Sq(SqQueue *Q,QElemType e);

extern Status DeQueue_Sq(SqQueue *Q,QElemType *e);


















#endif // STACKANDQUEUE_H_INCLUDED
