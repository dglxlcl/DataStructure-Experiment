#ifndef LINEARLIST_H_INCLUDED
#define LINEARLIST_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配长度
#define LISTINCREMENT 10  //线性表存储空间的分配增量
#define MAXSIZE 1000 //用作静态链表的最大长度

typedef int Status;//状态值定义


//typedef int ElemType;//元素的定义

typedef struct {
    int OccurTime;//事件发生的时间
    int EventType;//事件类型,0表示客户到达事件，1~4表示从1~4号窗口客户离开事件
}Event,ElemType;

typedef struct{//顺序表的定义
	ElemType *elem;//顺序表第一个元素的起始地址
	int length;//顺序表的长度
	int listsize;//顺序表的容量
}Sqlist;

//定义单链表的结点
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*Link;

//定义双链表的结点
typedef struct DuLNode{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode,*DuLink;

//定义单链表
typedef struct{
    Link head,tail;//分别指向链表的头结点和最后一个结点
    int length;//表示链表中数据元素的个数
}LinkList_L;

//定义双向链表
typedef struct{
    DuLink head,tail;//分别指向链表的头结点和最后一个结点
    int length;//表示链表中数据元素的个数
}LinkList_DuL;

//定义单循环链表
typedef struct{
    Link head,rear;
    int length;
}LinkList_CL;

//定义一个静态链表
typedef struct{
    ElemType data;
    int cur;//静态链表数据项的游标，相当于链表中的next,S[0].cur表示第一个结点在数组中的位置
}component,SLinkList[MAXSIZE];

extern Status InitList_Sq(Sqlist *L);

extern Status IncListSize_Sq(Sqlist *L);

//销毁一个顺序表，释放这个顺序表的占用空间，同时将长度和容量都置0
extern void DestroyList_Sq(Sqlist *L);

//将顺序表清空为空表，长度为0
extern void ClearList_Sq(Sqlist *L);

//当L为空表时，返回TURE，否则返回FALSE。
extern Status ListEmpty_Sq(Sqlist *L);

//返回顺序表L的长度。
extern int ListLength_Sq(Sqlist *L);

//获取顺序表L的第i个元素，将其赋值给e。当i的取值非法时，返回ERROR
extern Status GetElem_Sq(const Sqlist *L,int i,ElemType *e);

//在顺序表L中，对e和所有元素的值，依次调用compare函数进行匹配，返回第一个匹配成功的元素的坐标。
extern int LocateElem_Sq(Sqlist *L,ElemType e,Status (*compare)(ElemType ,ElemType) );

//在顺序表L的第i个元素前插入元素e。如果表长=SIZE,则增加分配顺序表空间，增量为LISTINCREMENT，若i取值非法则返回错误，否则返回OK。
extern Status ListInsert_Sq(Sqlist *L,int i,ElemType e);

//删除顺序表L的第i个元素，将其赋值给e，如果操作成功返回OK，如果错误则返回ERROR。
extern Status ListDelete_Sq(Sqlist *L,int i,ElemType *e);

//当顺序表元素为字符串时，从键盘输入内容（长度在100个字符以内），添加至表的末尾，按回车结束输入，自动增加表的大小，操作成功返回OK。当表非字符串类型时，返回错误。
extern Status StrListInput_Sq(Sqlist *L);

//用键盘向表L中输入元素，若表中已经有内容，就在把输入内容添加在后面（自动更新表的大小）。format是格式控制字符，与scanf中的用法一样，但不支持字符串。
extern Status ListInput_Sq(const char *format,Sqlist *L);

//输出表L中的内容，format是格式控制符，与printf的格式控制符一样，但这里不支持字符串。
extern Status ListPrint_Sq(const char *format,Sqlist *L);

//一个compare()函数的特例，这里是判断两个元素是否相等。
extern Status equal(ElemType a,ElemType b);

//对顺序表L中的内容进行冒泡排序
extern Status ListBubbleSort_Sq(Sqlist *L);

//取顺序表L1和顺序表L2的并集。
extern Status ListUnion_Sq(Sqlist *L1,Sqlist *L2);

extern Status MakeNode(Link *p);

extern Status MakeDuLNode(DuLink *p);

extern Status InitList_L(LinkList_L *L);

extern Status DestroyList_L(LinkList_L *L);

extern Status ClearList_L(LinkList_L *L);

extern Status InsFirst_L(LinkList_L *L,Link s);

extern Status DelFirst_L(LinkList_L *L,ElemType *e);

extern Status DelEnd_L(LinkList_L *L,Link *q);

extern Status Append_L(LinkList_L *L,Link s);

extern Status ListInput_L(const char *format,LinkList_L *L);

extern Status ListPrint_L(const char *format,LinkList_L *L);

extern Status LocatePos_L(LinkList_L *L,int i,Link *p);

extern Link LocateElem_L(LinkList_L *L,ElemType e,Status (*compare)(ElemType,ElemType));

extern Status InsBefore_L(LinkList_L *L,Link *p,Link s);

extern Status InsAfter_L(LinkList_L *L,Link *p,Link s);

extern Status ListEmpty_L(LinkList_L *L);

extern Link PriorPos_L(LinkList_L *L,Link p);

extern Status MergeList_L(LinkList_L *L1,LinkList_L *L2,LinkList_L *L3);

extern void InitSpace_SL(SLinkList SL);

extern int Malloc_SL(SLinkList SL);//若备用链表非空，则返回分配结点的下标，否则返回0

extern void Free_SL(SLinkList SL,int k);//将下标为k的结点回收到备用链表

extern int LocatePOS_SL(SLinkList SL,int i);//找到链表第i个元素的下标

//在静态链表SL中查找第一个值为e的元素，若找到，返回它在L中的位序，否则返回0
extern int LocateElem_SL(SLinkList SL,ElemType e);

//回收第i个结点，并将其值赋给e.当第i个结点不存在时，返回ERROR。
extern Status ListDelete_SL(SLinkList SL,int i,ElemType *e);

extern Status ListInsert_SL(SLinkList SL,int i,ElemType e);

extern int GetLast_SL(SLinkList SL);

extern Status ListInput_SL(const char *format,SLinkList SL);

extern Status ListPrint_SL(const char *format,SLinkList SL);

//初始化一个单循环链表为空表
extern Status InitList_CL(LinkList_CL *L);


//销毁一个单链循环表
extern Status DestroyList_CL(LinkList_CL *L);


//将单循环链表重置为空表，并释放原链表的空间
extern Status ClearList_CL(LinkList_CL *L);


//单循环链表头插法
extern Status InsFirst_CL(LinkList_CL *L,Link s);

//已知p指向线性单循环链表L中的一个结点，将s所指结点插入在p所指结点之后，并修改p指向新插入的结点。该操作必须保证p在表中，不然会出错，而且很难调试
extern Status InsAfter_CL(LinkList_CL *L,Link *p,Link s);

//单循环链表尾插法
extern Status InsEnd_CL(LinkList_CL *L,Link s);

//获取p指针的前一个结点
extern Link PriorPos_CL(LinkList_CL *L,Link p);

//获取循环表表L中p指针后的第i个元素的地址(查找过程中遇到头指针自动跳过)
extern Link LocatePos_CL(LinkList_CL *L,Link p ,int i);

//删除p指针所指的结点，并将p指针指向下一个结点
extern Status ListDelete_CL(LinkList_CL *L,Link *p);

extern Status ListPrint_CL(const char *format,LinkList_CL *L);
#endif // LINEARLIST_H_INCLUDED
