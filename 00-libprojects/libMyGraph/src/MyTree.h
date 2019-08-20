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

typedef enum
{
    Link,
    Thread
} PointerTag;

typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;

typedef struct TreeNode{
    TElemType data;
    struct TreeNode *firstchild,*nextsibling;
} TreeNode, *Tree;

typedef struct ForstNode{
    TElemType data;
    struct ForstNode *firstsubforst, *nextforst;
}ForstNode, *Forst;



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

//层序遍历一个二叉链表
Status LevelOrderTranverseBiTree(BiTree T, Status (*visit)(TElemType e));

//先序创建一个二叉线索链表，递归算法实现
Status PreCreatBiThrTree(BiThrTree *T);

//中序线索化一颗二叉线索链表
Status InOrderThreadingBiThrTree(BiThrTree *T);

//中序线索遍历一颗二叉线索链表
Status InOrderTranverseBiThrTree(BiThrTree T,Status (*visit)(TElemType e));

//创建一个孩子兄弟表示法的树结点，返回其指针
Tree GetTreeNode(TElemType root,Tree firstchild,Tree nextsibling);

//先根创建一颗树
Status PreRootCreatTree(Tree *T);

//先根遍历一颗树（孩子兄弟表示法）
Status PreRootTranverseTree(Tree T, Status (*visit)(TElemType e));

//后根遍历一颗树（孩子兄弟表示法）
Status PostRootTranverseTree(Tree T, Status (*visit)(TElemType e));

//创建一个二叉链表存储结构的森林结点，返回其指针
Forst GetForstNode(TElemType root,Forst firstsubforst,Forst nextforst);

//先序创建一个森林
Status PreOrderCreatForst(Forst *F);

//先序遍历森林
Status PreOrderTranverseForst(Forst F, Status (*visit)(TElemType e));

//中序遍历一个森林（孩子兄弟表示法）
Status InOrderTranverseForst(Forst F, Status (*visit)(TElemType e));

#endif //MY_TREE_H_INCLUDED
