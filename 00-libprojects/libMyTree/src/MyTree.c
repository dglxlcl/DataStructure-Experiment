//递归算法实际上真的不需要过多的考虑函数过程，只需要把注意力集中在返回条件，即函数执行成功与否

#include <stdio.h>
#include <stdlib.h>
#include "MyTree.h"
#include "StackAndQueue.h"


//初始化一个顺序存储结构的二叉树，全部赋值为0
Status InitBiTree_Sq(SqBiTree *T){
    TElemType *ptr = (TElemType *)T;
    for (int i = 0; i < MAX_TREE_SIZE;i++){
        ptr[i] = 0;
    }
    return OK;
}

//一个visit函数特例，作用是打印元素。关于visit函数，必须要设定错误返回值，当遇到空树时返回错误。
Status PrintElem(TElemType e){
    printf("%c", e);
    return OK;
}

//以编号SerialNum(不是下标)为根，按先序次序,输入顺序二叉树中结点的值，空格字符表示空树
Status PreCreatBiTree_Sq(SqBiTree *T,int SerialNum){
//第一种算法：递归实现
    TElemType strtmp[2];//专门用来接收并抛弃回车
    TElemType tmp ;//临时接收字符
    if(SerialNum<1){
        printf("PreCreatBiTree_Sq:The SerialNum is illegal!\n");
        return OVERFLOW;
    }
    if (SerialNum>MAX_TREE_SIZE){
        scanf("%c", &tmp);
        scanf("%1[\n]", strtmp);//尝试读取回车并抛弃
        if(' '!=tmp){
            printf("PreCreatBiTree_Sq:The layer of SqBitree is overflow!\n");

            return OVERFLOW;
        }else{
            return ERROR;
        }
    }else{
        TElemType *ptr = (TElemType *)T;
        scanf("%c", &tmp);
        scanf("%1[\n]", strtmp);//尝试读取回车，并抛弃
        ptr[SerialNum - 1] = tmp;
        if( ptr[SerialNum-1]!=' ' ){//输入根节点元素，如果不是空格（空树），就继续遍历创建左子树则返回。
            if( (PreCreatBiTree_Sq(T, 2 * SerialNum ))>=0 )//当左子树没有溢出时，创建左子树，然后创建右子树
                if( (PreCreatBiTree_Sq(T, 2 * SerialNum+1)) >=0 )//创建右子树
                    return OK;//返回OK,说明创建了非空的树
            return OVERFLOW;
        }else {
            return ERROR;//返回ERROR，说明创建了空树
        }
    }
}

//先序遍历顺序二叉树T中编号SerialNum为根的子树(调用visit函数)，编号为1时就是遍历整个树。
Status PreOrderTranverseBiTree_Sq(SqBiTree T,int SerialNum,Status (*visit)(TElemType e)){
// //第一种算法：递归实现
//     TElemType *ptr = (TElemType *)T;
//     if(SerialNum>MAX_TREE_SIZE||SerialNum<1||ptr[SerialNum-1]==' '){//实际上也是判断本树是否为空，这一条语句时顺序二叉树的特例
//         return OK;
//     }else{
//         if( (visit(ptr[SerialNum - 1])) )
//             if (PreOrderTranverseBiTree_Sq(T, 2 * SerialNum, visit))              //先遍历左子树
//                 if(PreOrderTranverseBiTree_Sq(T, 2 * SerialNum + 1, visit))       //然后遍历右子树
//                     return OK;
//         return ERROR;            
//     }

//第二种算法，非递归实现（使用栈）
    SqStack S;
    InitStack_Sq(&S);
    TElemType *ptr = (TElemType *)T;
    int p = SerialNum;
    while( ( (p>=1&&p<=MAX_TREE_SIZE)&&ptr[p-1]!=' ')||!StackEmpty_Sq(&S) ){
        if( (p>=1&&p<=MAX_TREE_SIZE)&&ptr[p-1]!=' ' ){//如果指针p合法，且不空，那么先访问根节点然后遍历左子树
            if(!visit(ptr[p - 1]) ){
                return ERROR;
            }
            Push_Sq(&S, p);
            p = 2 * p;
        }else{
            Pop_Sq(&S, &p);//根指针退栈，然后遍历右子树
            p = 2 * p + 1;
        }
    }
    return OK;
}


//中序遍历顺序二叉树T中编号SerialNum为根的子树(调用visit函数)，编号为1时就是遍历整个树。
Status InOrderTranverseBiTree_Sq(SqBiTree T,int SerialNum,Status (*visit)(TElemType e)){
// //第一种算法：递归实现
//     TElemType *ptr = (TElemType *)T;
//     if(SerialNum>MAX_TREE_SIZE||SerialNum<1||ptr[SerialNum-1]==' '){//实际上也是判断本树是否为空，这一条语句时顺序二叉树的特例
//         return OK;
//     }else{
//         if (InOrderTranverseBiTree_Sq(T, 2 * SerialNum, visit))              //先遍历左子树
//             if( (visit(ptr[SerialNum - 1])) )
//                 if(InOrderTranverseBiTree_Sq(T, 2 * SerialNum + 1, visit))       //然后遍历右子树
//                     return OK;
//         return ERROR;       
//     }

//第二种算法，非递归实现（使用栈）
    SqStack S;
    InitStack_Sq(&S);
    TElemType *ptr = (TElemType *)T;
    int p = SerialNum;
    while( ( (p>=1&&p<=MAX_TREE_SIZE)&&ptr[p-1]!=' ')||!StackEmpty_Sq(&S) ){
        if( (p>=1&&p<=MAX_TREE_SIZE)&&ptr[p-1]!=' ' ){//如果指针p合法，且不空，那么先访问根节点然后遍历左子树
            Push_Sq(&S, p);
            p = 2 * p;
        }else{
            Pop_Sq(&S, &p);//根指针退栈，然后遍历右子树
            if(!visit(ptr[p - 1]) ){
                return ERROR;
            }
            p = 2 * p + 1;
        }
    }
    return OK;
}

//后序遍历顺序二叉树T中编号SerialNum为根的子树(调用visit函数)，编号为1时就是遍历整个树。
Status PostOrderTranverseBiTree_Sq(SqBiTree T,int SerialNum,Status (*visit)(TElemType e)){
// //第一种算法：递归实现
//     TElemType *ptr = (TElemType *)T;
//     if(SerialNum>MAX_TREE_SIZE||SerialNum<1||ptr[SerialNum-1]==' '){//实际上也是判断本树是否为空，这一条语句时顺序二叉树的特例
//         return OK;
//     }else{
//         if (PostOrderTranverseBiTree_Sq(T, 2 * SerialNum, visit))              //先遍历左子树
//             if(PostOrderTranverseBiTree_Sq(T, 2 * SerialNum + 1, visit))       //然后遍历右子树
//                 if( (visit(ptr[SerialNum - 1])) )
//                     return OK;
//         return ERROR;
//     }

//第二种算法，非递归实现（使用栈）
    SqStack S;
    InitStack_Sq(&S);
    TElemType *ptr = (TElemType *)T;
    int p = SerialNum;
    int top = 0;
    int last = 0;
    while( ( (p>=1&&p<=MAX_TREE_SIZE)&&ptr[p-1]!=' ')||!StackEmpty_Sq(&S) ){
        if( (p>=1&&p<=MAX_TREE_SIZE)&&ptr[p-1]!=' '&&p!=last ){//如果指针p合法，且不空，那么先访问根节点然后遍历左子树
            Push_Sq(&S, p);
            p = 2 * p;
        }else{
            GetTop_Sq(&S, &top);
            if( (2*top+1>MAX_TREE_SIZE) || (ptr[2*top]==' ') || last==2*top+1 ) {
                Pop_Sq(&S, &p);
                visit(ptr[p - 1]);
                last = p;
            }else{
                p = 2 * top + 1;
            }
        }
        if(last==SerialNum){
            break;
        }
    }
    return OK;
}


//层序遍历顺序二叉树T中编号SerialNum为根的子树(调用visit函数)，编号为1时就是遍历整个树。没法用递归，只能用栈
Status LevelOrderTranverseBitree_Sq(SqBiTree T,int SerialNum,Status (*visit)(TElemType e)){
    SqQueue Q;
    InitQueue_Sq(&Q);
    TElemType *ptr = (TElemType *)T;
    int p = SerialNum;
    if(p>=1&&p<=MAX_TREE_SIZE&&ptr[p-1]!=' '){
        EnQueue_Sq(&Q, p);                                      //第一步：根节点入队
        while(!QueueEmpty_Sq(Q)){
            DeQueue_Sq(&Q, &p);                                 //队首出队，visit，然后将它的两个子树入队（不能为空）
            visit(ptr[p - 1]);
            if(2*p>=1&&2*p<=MAX_TREE_SIZE&&ptr[2*p-1]!=' '){    //左子树根节点入队
                EnQueue_Sq(&Q, 2 * p);
            }
            if(2*p+1>=1&&2*p+1<=MAX_TREE_SIZE&&ptr[2*p]!=' '){  //右子树根节点入队
                EnQueue_Sq(&Q, 2 * p + 1);
            }
        }
    }else{
        return ERROR;
    }
    return OK;
}

//先序创建一个二叉链表，递归算法实现
Status PreCreatBiTree(BiTree *T){
    TElemType ch;
    TElemType tmp[2];
    scanf("%c", &ch);
    scanf("%1[\n]", tmp);
    if(ch==' '){
        *T = NULL;
    }else{
        *T = (BiTree)malloc(sizeof(BiTNode));
        if(!(*T)) exit(OVERFLOW);
        (*T)->data = ch;
        PreCreatBiTree( &((*T)->lchild) );
        PreCreatBiTree( &((*T)->rchild) );
    }
    return OK;
}

//先序遍历一个二叉链表
Status PreOrderTranverseBiTree(BiTree T,Status (*visit)(TElemType e)){
// //第一种方案，递归算法
//     if(T){
//         if( visit(T->data) )
//             if( PreOrderTranverseBiTree(T->lchild, visit) )
//                 if (PreOrderTranverseBiTree(T->rchild, visit) )
//                     return OK;
//         return ERROR;
//     }else{
//         return OK;
//     }

//第二种方案，非递归
    LinkStack S;
    InitStack_L(&S);
    BiTree p = T;
    while(p||!StackEmpty_L(&S)){
        if(p){    //如果当前指针非空，就visit后入栈，然后指向左子树
            if(!visit(p->data)){
                return ERROR;
            }
            Push_L(&S, p);
            p = p->lchild;
        }else{
            Pop_L(&S, &p);    //如果指针空，就弹栈，然后指向右子树
            p = p->rchild;
        }
    }
    return OK;
}

//中序遍历一个二叉链表
Status InOrderTranverseBiTree(BiTree T,Status (*visit)(TElemType e)){
// //第一种方案，递归算法
//     if(T){
//         if( InOrderTranverseBiTree(T->lchild, visit) )
//             if( visit(T->data) )
//                 if (InOrderTranverseBiTree(T->rchild, visit) )
//                     return OK;
//         return ERROR;
//     }else{
//         return OK;
//     }

//第二种方案，非递归
    LinkStack S;
    InitStack_L(&S);
    BiTree p = T;
    while(p||!StackEmpty_L(&S)){
        if(p){    //如果当前指针非空，就visit后入栈，然后指向左子树
            Push_L(&S, p);
            p = p->lchild;
        }else{
            Pop_L(&S, &p);    //如果指针空，就弹栈，然后指向右子树
            if(!visit(p->data)){
                return ERROR;
            }
            p = p->rchild;
        }
    }
    return OK;
}

//后序遍历一个二叉链表
Status PostOrderTranverseBiTree(BiTree T,Status (*visit)(TElemType e)){
    LinkStack S;
    InitStack_L(&S);
    BiTree p = T;
    BiTree top;
    BiTree last = NULL;
    while(p||!StackEmpty_L(&S)){
        if(p&&p!=last){
            Push_L(&S, p);
            p = p->lchild;
        }else{
            GetTop_L(&S, &top);
            if(top->rchild==NULL||top->rchild==last){
                Pop_L(&S, &p);
                if(!visit(p->data)){
                    return ERROR;
                }
                last = p;
            }else{
                p = p->rchild;
            }
        }
        if(last==T){
            break;
        }
    }
    return OK;
}