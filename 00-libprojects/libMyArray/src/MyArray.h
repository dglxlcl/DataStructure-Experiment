#ifndef MY_ARRAY_H_INCLUDED
#define MY_ARRAY_H_INCLUDED
#include <stdarg.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_ARRAY_DIM 8

typedef int Status;

typedef int ElemType;

typedef struct {
    ElemType *base;
    int dim;
    int *bounds;
    int *constans;
}Array;

Status InitArray(Array *A,int dim,...);//初始化一个数组A，其维度是dim，可变变量为各个维度的长度。

Status DestroyArray(Array *A);//销毁一个数组。

Status Locate(Array A, va_list ap, int *offset);//只用再Assign函数和Value函数里面，根据参数列表，得到元素在A中的相对地址off。

Status Value(Array A,ElemType *e,...);//根据坐标参数信息读取数组元素的值，赋值给e。

Status Assign(Array *A,ElemType e,...);//根据坐标参数信息，用e给数组元素赋值。

#endif // MY_ARRAY_H_INCLUDED
