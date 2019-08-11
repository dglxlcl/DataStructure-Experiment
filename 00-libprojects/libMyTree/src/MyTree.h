#ifndef MY_TREE_H_INCLUDED
#define MY_TREE_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_TREE_SIZE 127 //对于完全二叉树,深度为[log_2^n]+1即7层

typedef int Status;

typedef char TElemType;

typedef TElemType SqBiTree[MAX_TREE_SIZE];//二叉树的顺序存储结构,仅适用于完全二叉树，用来存储一般的二叉树会造成空间很大的浪费

typedef struct BiTNode{//二叉链表的定义
    TElemType data;//存储数据
    struct BiTNode *lchild, *rchild;//左子树和右子树的根节点指针
} BiTNode, *BiTree;

//初始化一个顺序存储结构的二叉树，全部赋值为0
Status InitBiTree_Sq(SqBiTree *T);

//一个visit函数特例，作用是打印元素。
Status PrintElem(TElemType e);

//以编号index为根，按先序次序,输入顺序二叉树中结点的值，空格字符表示空树，
Status PreCreatBiTree_Sq(SqBiTree *T, int index);

//先序遍历顺序二叉树T中编号SerialNum为根的子树(调用visit函数)，编号为1时就是遍历整个树。
Status PreOrderTranverseBiTree_Sq(SqBiTree T, int SerialNum, Status (*visit)(TElemType e));

//中序遍历顺序二叉树T中编号SerialNum为根的子树(调用visit函数)，编号为1时就是遍历整个树。
Status InOrderTranverseBiTree_Sq(SqBiTree T, int SerialNum, Status (*visit)(TElemType e));

//后序遍历顺序二叉树T中编号SerialNum为根的子树(调用visit函数)，编号为1时就是遍历整个树。
Status PostOrderTranverseBiTree_Sq(SqBiTree T, int SerialNum, Status (*visit)(TElemType e));

//层序遍历顺序二叉树T中编号SerialNum为根的子树(调用visit函数)，编号为1时就是遍历整个树。没法用递归，只能用栈
Status LevelOrderTranverseBitree_Sq(SqBiTree T, int SerialNum, Status (*visit)(TElemType e));




//先序创建一个二叉链表，递归算法实现
Status PreCreatBiTree(BiTree *T);

//先序遍历一个二叉链表
Status PreOrderTranverseBiTree(BiTree T, Status (*visit)(TElemType e));

//中序遍历一个二叉链表
Status InOrderTranverseBiTree(BiTree T, Status (*visit)(TElemType e));

//后序遍历一个二叉链表
Status PostOrderTranverseBiTree(BiTree T, Status (*visit)(TElemType e));


#endif //MY_TREE_H_INCLUDED