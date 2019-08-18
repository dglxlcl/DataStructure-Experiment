#ifndef MYGRAPH_H_INCLUDE
#define MYGRAPH_H_INCLUDE

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

#define INFINITY INT_MAX //定义INT_MAX为无穷大
#define MAX_VERTEX_NUM 20 //定义定点最大个数

typedef int VRType;//定义定点关系类型。对无权图，用1或0表示相邻否；对带权图，则为权值类型。
typedef int InfoType;//定义弧相关信息的数据类型
typedef char VertexType;//定义定点元素的数据类型

typedef enum {DG,DN,UDG,UDN} GraphKind; //定义图类型的枚举选项。DG：有向图   DN：有向网      UDG：无向图     UDN：无向网

typedef enum{unvisited,visited} VisitIF;//这个枚举类型定义主要用在邻接多重表的访问标记中。

//往下两个分别是邻接矩阵图的弧单元、图定义
typedef struct ArcCell{//邻接矩阵中弧元素的定义
    VRType adj;
    InfoType *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{//图的邻接矩阵表示法
    VertexType vexs[MAX_VERTEX_NUM];//顶点向量
    AdjMatrix arcs;//邻接矩阵
    int vexnum, arcnum;
    GraphKind kind;
} MGraph;



//往下三个定义，分别是邻接表的弧、顶点、图定义
typedef struct ArcNode{//用邻接表表示的图中，弧结点的定义
    VRType adj;
    int adjvex;//存储弧指向的顶点的位置
    struct ArcNode *nextarc;
    InfoType *info;
} ArcNode;

typedef struct VexNode{//用邻接表表示的图中，顶点结点的定义
    VertexType data;//顶点信息
    ArcNode *firstarc;
} VexNode, AdjList[MAX_VERTEX_NUM];

typedef struct{//用邻接表表示法的图ALGraph
    AdjList vertexs;
    int vexnum, arcnum;
    GraphKind kind;
} ALGraph;



//往下三个定义分别是十字链表（常用于有向图）的弧、顶点、图定义
typedef struct ArcBox{//用十字链表表示有向图的弧结点，因为我多加了一个VRType ，因此这个结构可以表示有向网，区别在于表示图时，adj=【1，0】，表示网时，adj表示权重weight.
    VRType adj;
    int tailvex, headvex;//本弧的弧尾，弧头；
    struct ArcBox *tlink, *hlink;//tlink指向下一个与本弧弧尾相同的弧，hlink指向下一个
    InfoType *info;
} ArcBox;

typedef struct VexNode_OL{//用十字链表表示有向图的顶点结点。
    VertexType data;
    ArcBox *firstout, *firstin;
} VexNode_OL;

typedef struct{//有向图（网）的十字链表结构
    VexNode_OL xlist[MAX_VERTEX_NUM];
    int arcnum, vexnum;
    GraphKind kind;
} OLGraph;



//往下三个定义分别是邻接多重表（常用于无向图）的边、顶点、图定义
typedef struct EdgeBox{
    VisitIF mark;//标记这条边是否被访问
    int ivex, jvex;//这条边依附的两个顶点
    struct EdgeBox *ilink, *jlink;//分别指向依附i,j这两个顶点的下一条边
    InfoType *info;//边的其他信息的指针
} EdgeBox;

typedef struct VexNode_AML{
    VertexType data;
    EdgeBox *firstedge;
} VexNode_AML;

typedef struct {
    VexNode_AML adjmulist[MAX_VERTEX_NUM];
    int edgenum, vexnum;
} AMLGraph;

//查找定位邻接矩阵图中第一个值为value的定点，返回其在顶点向量中的下标，若没有找到就返回-1
int LocateVex_AdjMatrix(MGraph G, VertexType value);

//创建一个用邻接矩阵表示的无向图
Status CreateGraph_AdjMatrix(MGraph *G);

//创建一个用邻接矩阵表示的无向图
Status CreateDG_AdjMatrix(MGraph *G);
//创建一个用邻接矩阵表示的无向图
Status CreateDN_AdjMatrix(MGraph *G);
//创建一个用邻接矩阵表示的无向图
Status CreateUDG_AdjMatrix(MGraph *G);
//创建一个用邻接矩阵表示的无向图
Status CreateUDN_AdjMatrix(MGraph *G);

//保存一个用邻接矩阵表示的无向图
Status SaveUDG_AdjMatrix(MGraph G,char *filename);


//查找定位邻接表图中第一个值为value的定点，返回其在顶点向量中的下标，若没有找到就返回-1
int LocateVex_AdjList(ALGraph G, VertexType value);

//创建一个用邻接表表示的无向图
Status CreateUDG_AdjList(ALGraph *G);

//创建一个用十字链表表示的有向图
Status CreateDG_OLGraph(OLGraph *G);

//创建一个用邻接多重表表示的无向图
Status CreateUDG_AMLGraph(AMLGraph *G);

//保存一个无向图（邻接多重表）的信息到文件中
Status SaveAMLGraph(AMLGraph G, char *filename);

//加载一个无向图（邻接多重表）文件的信息到图中
Status LoadAMLGraph(AMLGraph *G, char *filename);

//打印一个结点，visit函数的一个特例
Status PrintVertex(VertexType vertex);

//利用visit函数深度优先遍历邻接多重图G
Status DFSTranverAMLGraph(AMLGraph G, Status (*visit)(VertexType vertex));

//利用visit函数广度优先遍历邻接多重图G
Status BFSTranverAMLGraph(AMLGraph G,Status (*visit)(VertexType vertex));

#endif
