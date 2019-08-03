#ifndef STACKANDQUEUE_H_INCLUDED
#define STACKANDQUEUE_H_INCLUDED

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;

typedef long long SElemType;
//typedef struct PosType{
//    int x,y;
//}PosType;
//typedef struct{
//    int ord;
//    PosType seat;
//    int di;
//}SElemType;

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


typedef struct StackNode{
    SElemType data;
    struct StackNode *next;
}StackNode,*Stack_pt;

typedef struct{
    Stack_pt top,base;
    int length;
}LinkStack;


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



























#endif // STACKANDQUEUE_H_INCLUDED
