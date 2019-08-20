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


//创建一个二叉树链表结点，返回其指针

BiTree GetBiTreeNode(TElemType root,BiTree lchild,BiTree rchild){
    if(root == ' '){
        return NULL;
    }else{
        BiTree p = (BiTree)malloc(sizeof(BiTNode));
        p->data = root;
        p->lchild = lchild;
        p->rchild = rchild;
        return p;
    }
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
    BiTree last = NULL;
    while(p||!StackEmpty_L(&S)){
        if(p&&p!=last){
            Push_L(&S, p);
            p = p->lchild;
        }else{
            GetTop_L(&S, &p);//遍历完左子树后，先看一眼栈顶，如果栈顶元素的右子树为空或已访问，那么就弹栈并visit栈顶（就是根节点在最后访问），get是后序遍历的关键，因为根结点还没有访问，不能弹栈
            if(p->rchild==NULL||p->rchild==last){
                Pop_L(&S, &p);
                if(!visit(p->data)){
                    return ERROR;
                }
                last = p;//每访问了一个结点，就将last指针指向它
            }else{
                p = p->rchild;//遍历完左子树，先看一眼栈顶，如果栈顶的右子树还没有访问，那么先不慌弹栈，而是将p指针指向它的右子树。
            }
        }
        if(last==T){//如果是后序遍历，那么树的根结点是最后访问了，如果last等于根结点，那么访问完毕
            break;
        }
    }
    return OK;
}

//层序遍历一个二叉链表
Status LevelOrderTranverseBiTree(BiTree T,Status (*visit)(TElemType e)){
    LinkQueue Q;
    InitQueue_L(&Q);
    BiTree p = T;
    if(p){
        EnQueue_L(&Q, p);
        while(!QueueEmpty_L(Q)){
            DeQueue_L(&Q, &p);
            if( !visit(p->data) ){
                return ERROR;
            }
            if(p->lchild) EnQueue_L(&Q, p->lchild);
            if(p->rchild) EnQueue_L(&Q, p->rchild);
        }
    }else {
        return ERROR;
    }
    return OK;
}


//创建一个二叉线索链表，返回其指针
BiThrTree GetBiThrTreeNode(TElemType root,BiThrTree lchild,BiThrTree rchild,PointerTag LTag,PointerTag RTag){
    if(root == ' '){
        return NULL;
    }else{
        BiThrTree p = (BiThrTree)malloc(sizeof(BiThrNode));
        p->data = root;
        p->lchild = lchild;
        p->rchild = rchild;
        p->LTag = LTag;
        p->RTag = RTag;
        return p;
    }
}

//先序创建一个二叉线索链表，递归算法实现
Status PreCreatBiThrTree(BiThrTree *T){
    TElemType ch;
    TElemType tmp[2];
    scanf("%c", &ch);
    scanf("%1[\n]", tmp);
    if(ch==' '){
        *T = NULL;
    }else{
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if(!(*T)) exit(OVERFLOW);
        (*T)->data = ch;
        PreCreatBiThrTree( &((*T)->lchild) );
        PreCreatBiThrTree( &((*T)->rchild) );
    }
    return OK;
}


//中序线索化一个二叉连锁链表时使用的一个递归程序
Status InThreading(BiThrTree T,BiThrTree *Pre){
    if( T == NULL){
        return ERROR;
    }else{
        InThreading(T->lchild, Pre);
        if(!T->lchild){
            T->LTag = Thread;
            T->lchild = *Pre;
        }else{
            T->LTag = Link;
        }
        if(!(*Pre)->rchild){
            (*Pre)->RTag = Thread;
            (*Pre)->rchild = T;
        }else{
            (*Pre)->RTag = Link;
        }
        *Pre = T;
        InThreading(T->rchild, Pre);
        return OK;
    }
}


//中序线索化一颗二叉线索链表，线索完毕后，会新建一个线索头结点，其左链指向原树的根节点。
Status InOrderThreadingBiThrTree(BiThrTree *T){
    BiThrTree Thr = (BiThrNode *)malloc(sizeof(BiThrNode));
    if(!Thr){
        printf("InOrdThreadingBiThrTree:Failed to distribute memmory!\n");
        return ERROR;
    }
    Thr->data = ' ';
    Thr->RTag = Thread;
    Thr->rchild = Thr;
    Thr->LTag = Link;
    if(!*T){
        free(Thr);
        return OK;
    }else{
        Thr->lchild = *T;
        BiThrTree Pre;
        Pre = Thr;
        InThreading(*T, &Pre);
        Pre->RTag = Thread;
        Pre->rchild = Thr;
        Thr->rchild = Pre;
        *T = Thr;
        return OK;
    }
} 

//中序线索遍历一颗二叉线索链表
Status InOrderTranverseBiThrTree(BiThrTree T,Status (*visit)(TElemType e)){
    BiThrTree p;
    p = T->lchild;
    while(p!=T){
        while(p->LTag==Link){//找到二叉中序线索树的第一个结点
            p = p->lchild;
        }
        if(!visit(p->data)){
            return ERROR;
        }
        while(p->RTag==Thread&&p->rchild!=T){
            p = p->rchild;
            if(!visit(p->data)){
                return ERROR;
            }
        }
        p = p->rchild;
    }
    return OK;
}

//创建一个孩子兄弟表示法的树结点，返回其指针
Tree GetTreeNode(TElemType root,Tree firstchild,Tree nextsibling){
    if(root == ' '){
        return NULL;
    }else{
        Tree p = (Tree)malloc(sizeof(TreeNode));
        p->data = root;
        p->firstchild = firstchild;
        p->nextsibling = nextsibling;
        return p;
    }
}

//先根创建一颗树（孩子兄弟表示法）
Status PreRootCreatTree(Tree *T){
    TElemType ch;
    TElemType tmp[2];
    scanf("%c",&ch);
    scanf("%1[\n]", tmp);
    if(ch==' '){
        *T = NULL;
    }else{
        *T = (Tree)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        (*T)->nextsibling = NULL;
        PreRootCreatTree( &((*T)->firstchild) );
        Tree p = (*T)->firstchild;
        while(p){
            PreRootCreatTree(&p->nextsibling);
            p = p->nextsibling;
        }
    }
    return OK;
}

//先根遍历一颗树（孩子兄弟表示法）
Status PreRootTranverseTree(Tree T,Status (*visit)(TElemType e) ){
    // Tree p = T;
    // if(!T){//如果根节点不存在，直接返回
    //     return OK;
    // }else{
    //     if(!visit(T->data)){//根节点存在，先访问根节点
    //         return ERROR;
    //     }
    //     if(T->firstchild!=NULL){//只有当第一个孩子结点存在时才去遍历孩子，写这一判断语句，是因为孩子兄弟树的根节点和其他子树根节点的定义是不同的，根节点没有兄弟。
    //         PreTranverseTree(T->firstchild, visit);//如果有孩子，才开始递归，先遍历它的孩子，再遍历孩子的兄弟。（在递归里不涉及根结点的操作，根节点就是存在就打印，否则直接返回。）
    //         p = T->firstchild;
    //         while(p->nextsibling){
    //             PreTranverseTree(p->nextsibling, visit);
    //             p = p->nextsibling;
    //         }
            
    //     }
    //     return OK;
    // }

    //非递归实现
    LinkStack S;
    InitStack_L(&S);
    Tree p = T;
    if(!p){
        return OK;
    }else{
        if(!visit(T->data)){//根节点存在，先访问根节点
            return ERROR;
        }
        p = p->firstchild;
        while(p||!StackEmpty_L(&S)){
            if(p){
                if(!visit(p->data)){
                    return ERROR;
                }
                Push_L(&S, p);
                p = p->firstchild;
            }else{
                Pop_L(&S, &p);
                p = p->nextsibling;
            }
        }
        return OK;
    }
}

//后根遍历一颗树（孩子兄弟表示法）
Status PostRootTranverseTree(Tree T, Status (*visit)(TElemType e)){//使用二叉链表的中序遍历
    //递归实现
    // Tree p;
    // if(!T){
    //     return OK;
    // }else{
    //     p = T->firstchild;
    //     if(p){//如果T的第一个孩子存在，先遍历T的第一个孩子，然后遍历第一个孩子的其他兄弟，然后访问T。这是后根遍历的定义。
    //         PostRootTranverseTree(p, visit);
    //         while(p->nextsibling){
    //             PostRootTranverseTree(p->nextsibling, visit);
    //             p = p->nextsibling;
    //         }
    //     }
    //     if(!visit(T->data)){
    //         return ERROR;
    //     }
    //     return OK;
    // }

    //非递归实现
    LinkStack S;
    InitStack_L(&S);
    Tree p = T;
    if(!p){
        return OK;
    }else{
        p = p->firstchild;
        while(p||!StackEmpty_L(&S)){
            if(p){
                Push_L(&S, p);
                p = p->firstchild;
            }else{
                Pop_L(&S, &p);
                if(!visit(p->data)){
                    return ERROR;
                }
                p = p->nextsibling;
            }
        }
        if(!visit(T->data)){//根节点存在，先访问根节点
            return ERROR;
        }
        return OK;
    }    

}

//创建一个二叉链表存储结构的森林结点，返回其指针
Forst GetForstNode(TElemType root,Forst firstsubforst,Forst nextforst){
    if(root == ' '){
        return NULL;
    }else{
        Forst p = (Forst)malloc(sizeof(ForstNode));
        p->data = root;
        p->firstsubforst = firstsubforst;
        p->nextforst = nextforst;
        return p;
    }
}


//先序创建一个森林
Status PreOrderCreatForst(Forst *F){
    TElemType ch;
    TElemType tmp[2];
    scanf("%c",&ch);
    scanf("%1[\n]", tmp);
    if(ch==' '){
        *F = NULL;
    }else{
        *F = (Forst)malloc(sizeof(ForstNode));
        (*F)->data = ch;
        PreOrderCreatForst(&(*F)->firstsubforst);
        PreOrderCreatForst(&(*F)->nextforst);
    }
    return OK;
}


//先序遍历森林
Status PreOrderTranverseForst(Forst F,Status (*visit)(TElemType e)){
    //递归实现
    // if(!F){
    //     return OK;
    // }else{
    //     if(!visit(F->data)){
    //         return ERROR;
    //     }
    //     PreOrderTranverseForst(F->firstsubforst, visit);
    //     PreOrderTranverseForst(F->nextforst, visit);

    //     return OK;
    // }
    //非递归实现
    LinkStack S;
    InitStack_L(&S);
    Forst p=F;
    while(p||!StackEmpty_L(&S)){
        if(p){
            if(!visit(p->data)){
                return ERROR;
            }
            Push_L(&S, p);
            p = p->firstsubforst;
        }else{
            Pop_L(&S, &p);
            p = p->nextforst;
        }
    }
    return OK;
}

//中序遍历一个森林（孩子兄弟表示法）
Status InOrderTranverseForst(Forst F,Status (*visit)(TElemType e)){//先中序遍历第一棵树的子树森林，然后访问第一个树，然后访问其他树
    //递归实现
    // if(!F){
    //     return OK;
    // }else{
    //     InOrderTranverseForst(F->firstsubforst, visit);
    //     if(!visit(F->data)){
    //         return ERROR;
    //     }
    //     InOrderTranverseForst(F->nextforst, visit);
    //     return OK;
    // }

    //非递归实现
    LinkStack S;
    InitStack_L(&S);
    Forst p=F;
    while(p||!StackEmpty_L(&S)){
        if(p){
            if(!visit(p->data)){
                return ERROR;
            }
            Push_L(&S, p);
            p = p->firstsubforst;
        }else{
            Pop_L(&S, &p);
            p = p->nextforst;
        }
    }
    return OK;


}