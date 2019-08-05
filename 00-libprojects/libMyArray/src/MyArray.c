#include <stdio.h>
#include <stdlib.h>
#include "MyArray.h"
#include <stdarg.h>

Status InitArray(Array *A,int dim,...){//初始化一个数组A，其维度是dim，可变变量为各个维度的长度。
    if(dim<1||dim>MAX_ARRAY_DIM)
        return ERROR;
    A->dim = dim;
    A->bounds = (int *)malloc(dim * sizeof(int));
    if(!A->bounds)
        exit(OVERFLOW);
    int elemtotal = 1;
    va_list ap;//stdarg.h里定义的宏va_list，实际上是一个指针，用来接收变长参数信息
    va_start(ap, dim);//stdarg.h里的宏，dim是函数的最后一个固定参数，执行后，ap指向第一个可变参数。
    for (int i = 0; i < dim;i++){
        A->bounds[i] = va_arg(ap, int);//va_vag(ap,int)作用是先获取当前ap所值的值（int类型），然后再指向下一个。
        if(A->bounds[i]<0){
            printf("InitArray:Argument input error!\n");
        }
        elemtotal *= A->bounds[i];//为了计算总共的空间大小
    }
    A->base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
    if(!A->base)
        exit(OVERFLOW);
    A->constans=(int *)malloc(dim*sizeof(int));
    A->constans[dim - 1] = 1;
    for (int i = dim - 2; i >= 0;i--){
        A->constans[i] = A->bounds[i + 1] * A->constans[i + 1];
    }
    return OK;
}

Status DestroyArray(Array *A){//销毁一个数组
    if(!A->base)    return ERROR;
    free(A->base);  A->base = NULL;
    if(!A->bounds)  return ERROR;
    free(A->bounds); A->bounds = NULL;
    if(!A->constans) return ERROR;
    free(A->constans); A->constans = NULL;
    return OK;
}

Status Locate(Array A, va_list ap, int *offset){//只用再Assign函数和Value函数里面，根据参数列表，得到元素在A中的相对地址off
    *offset = 0;
    int ind;//用于临时存放各个维度坐标参数
    for(int i=0;i<A.dim;i++){
        ind=va_arg(ap, int);
        if(ind<0||ind>=A.bounds[i]){
            printf("Locate:Argument input error!\n");
            return OVERFLOW;
        }
        *offset+=A.constans[i]*ind;
    }
    return OK;
}

Status Value(Array A,ElemType *e,...){
    va_list ap;
    va_start(ap, e);
    int offset;
    int result;
    if( (result=Locate(A, ap, &offset))<=0 ){
        printf("Value:failed to locate elemtype!\n");
        return OVERFLOW;
    }
    *e=*(A.base+offset);
    return OK;
}

Status Assign(Array *A,ElemType e,...){
    va_list ap;
    va_start(ap, e);
    int offset;
    int result;
    if( (result=Locate(*A, ap, &offset))<=0 ){
        printf("Assign:failed to locate elemtype!\n");
        return OVERFLOW;
    }
    *(A->base+offset)=e;
    return OK;
}
