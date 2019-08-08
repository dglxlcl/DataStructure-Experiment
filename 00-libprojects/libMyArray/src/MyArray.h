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
#define MAX_MATRIX_SIZE 3000
#define MAXRC 1000

typedef int Status;

typedef int ElemType;

typedef struct {
    ElemType *base;
    int dim;
    int *bounds;
    int *constans;
}Array;

typedef struct{
    int i;
    int j;
    ElemType e;
} Triple;//稀疏矩阵非零元素的三元组定义

typedef struct{
    Triple *data; //非零元三元组表，data[0]不要用
    int *rpos;//存放每一行第一个非零元的位置
    int mu,nu,tu;//矩阵的行数、列数、非零元个数。
}SMatrix;

Status InitArray(Array *A,int dim,...);//初始化一个数组A，其维度是dim，可变变量为各个维度的长度。

Status DestroyArray(Array *A);//销毁一个数组。

Status Locate(Array A, va_list ap, int *offset);//只用再Assign函数和Value函数里面，根据参数列表，得到元素在A中的相对地址off。

Status Value(Array A,ElemType *e,...);//根据坐标参数信息读取数组元素的值，赋值给e。

Status Assign(Array *A,ElemType e,...);//根据坐标参数信息，用e给数组元素赋值。

Status CreateSMatrix(SMatrix *M);//利用键盘输入创建一个SMatrix。

Status PrintSMatrix(SMatrix M);//在屏幕上打印输出一个SMatrix矩阵

Status SaveSMatrix(SMatrix M,char *filename);//将SMatrix保存至文件名为filename的文件中

Status LoadSMatrix(SMatrix *M,char *filename);//从文件名为filename的文件中读取一个SMatrix

Status CopySMatrix(SMatrix M, SMatrix *T); //由稀疏矩阵SparseMatrix M得到SparseMatrix T

Status AddSMtrix(SMatrix M, SMatrix N, SMatrix *Q); //SparseMatrix M和N的行列数相等，将矩阵M和N相加得到SparseMatrix Q，Q必须是未初始化的,否则行列数必须和M，N匹配。

Status SubtSMtrix(SMatrix M, SMatrix N, SMatrix *Q);//SparseMatrix M和N的行列数相等，将矩阵M和N相减得到SparseMatrix Q，Q必须是未初始化的,否则行列数必须和M，N匹配。

Status MultSMatrix(SMatrix M, SMatrix N, SMatrix *Q);//对符合规格要求的两个矩阵M，N，进行相乘，结果存入矩阵Q;

Status TransposeSMatrix(SMatrix M, SMatrix *T); //对SMartrix M进行转置处理，得到SMatrix T

#endif // MY_ARRAY_H_INCLUDED
