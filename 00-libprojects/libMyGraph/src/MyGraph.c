#include <stdio.h>
#include <stdlib.h>
#include "MyGraph.h"
#include "StackAndQueue.h"
#include "MyTree.h"

static char visitmark[MAX_VERTEX_NUM];//使用一个封装的静态全部变量存储图中每个结点访问标志
static Status (*VisitFunc)(VertexType vertex);//使用一个全局变量函数指针，用来借来接收遍历图的visit函数的地址

//打印一个结点，visit函数的一个特例
Status PrintVertex(VertexType vertex){
    printf("%c", vertex);
    return OK;
}


//查找定位邻接矩阵图中第一个值为value的定点，返回其在顶点向量中的下标，若没有找到就返回-1
int LocateVex_AdjMatrix(MGraph G,VertexType value){
    int i=0;
    while(i<G.vexnum){
        if(G.vexs[i]==value){
            return i;
        }else{
            i++;
        }
    }
    return INFEASIBLE;
}

//创建一个用邻接矩阵表示的有向图
Status CreateDG_AdjMatrix(MGraph *G){
    //如果图不空，则返回错误(查看图的顶点个数)
    if(G->vexnum>0){
        printf("CreateDG_AdjMatrix:The AdjMatrixGraph is not empty.\n");
        return ERROR;
    }
    //初始化图的类型
    G->kind = DG;
    printf("DG_AdjMatrix is Creating:\n");
    //首先输入顶点个数、弧个数，和弧是否有相关信息标志。
    printf("Please input the total number of vertex:");
    scanf("%d", &G->vexnum);
    printf("Please input the total number of arc:");
    scanf("%d", &G->arcnum);
    int IncInfo;
    printf("If the ArcCell include extra information,please input '1',else input '0'\n");
    scanf("%d", &IncInfo);
    //根据顶点个数创建顶点向量
    scanf("%*[^\n]");
    scanf("%*c");
    printf("Please input the vertex one bye one,use space key to split.\n");
    for (int i = 0; i < G->vexnum;i++){
        scanf("%c", &G->vexs[i]);
        scanf("%*[ ]");
    }
    //初始化邻接矩阵
    for (int i = 0; i < G->vexnum;i++){
        for (int j = 0; j < G->vexnum;j++){
            G->arcs[i][j].adj = 0;
            G->arcs[i][j].info = NULL;
        }
    }
    //根据弧的个数创建邻接矩阵(包含是否需要录入弧的相关信息)
    VertexType v1,v2;

    int p1, p2;
    for (int k = 0; k < G->arcnum;k++){
        printf("Please input arc[%d]:..(format:vertex,vertex)\n", k);
        scanf("%*[^\n]");
        scanf("%*c");
        scanf("%c,%c", &v1, &v2);
        p1 = LocateVex_AdjMatrix(*G, v1);
        p2 = LocateVex_AdjMatrix(*G, v2);
        if(p1>=0&&p2>=0){
            G->arcs[p1][p2].adj = 1;
            if(IncInfo){
                InfoType *info = (InfoType *)malloc(sizeof(InfoType));
                printf("Please input the extra information for arc[%c][%c]:\n", v1, v2);
                scanf("%d", info);
                G->arcs[p1][p2].info=info;
            }
        }else{
            printf("CreateDG_AdjMatrix:Can't find vertex %c or vertex %c\n", v1, v2);
            k -= 1;
        }
    }
    return OK;
}

int FirstAdjVex_DG(MGraph G,int v0){
    for(int j = 0;j<G.vexnum;j++){
        if(G.arcs[v0][j].adj==1){
            return j;
        }
    }
    return -1;
}

int NextAdjVex_DG(MGraph G,int v0,int w){
    for (int j = w+1; j < G.vexnum;j++){
        if(G.arcs[v0][j].adj==1){
            return j;
        }        
    }
    return -1;
}

//保存一个用邻接矩阵表示的有向图
Status SaveDG_AdjMatrix(MGraph G,char *filename){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        printf("SaveDG_AdjMatrix:failed to open file '%s'\n",filename);
        return ERROR;        
    }
    fprintf(fp,"Graphkind:%d\n",G.kind);

    int IncInfo=0;//边信息指针标记
    int arc;
    for (int i = 0; i < G.vexnum;i++){//遍历每个顶点的第一条边，只要找到一条边的info指针不等于空，说明输入了info信息，则将IncInfo置1，然后退出循环。
        arc = FirstAdjVex_DG(G, i);
        if(arc>=0&&G.arcs[i][arc].info!=NULL){
            IncInfo = 1;
            break;
        }
    }

    fprintf(fp, "IncInfo=%d\n", IncInfo);
    fprintf(fp, "vexnum:%d,arcnum:%d\n", G.vexnum, G.arcnum);//存储顶点个数和边数个数信息
    fprintf(fp, "vertex:");
    for (int i = 0; i < G.vexnum; i++){//存储顶点数据
        fprintf(fp, "%c", G.vexs[i]);
    }
    fprintf(fp, "\n");
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            if(G.arcs[i][j].adj!=0){
                fprintf(fp, "<%c,%c>",G.vexs[i],G.vexs[j]);
                if(IncInfo){
                    fprintf(fp, " Info:%d\n",*G.arcs[i][j].info);
                }else{
                    fprintf(fp, " Info:NULL\n");
                }
            }
        }
    }
    fclose(fp);
    return OK;
}

//加载一个用邻接矩阵表示的有向图
Status LoadDG_AdjMatrix(MGraph *G,char *filename){
    char tmp[20];//临时接收回车等垃圾字符
    if(G->vexnum>0){//如果图不空，则返回错误，只能用空图接收
        printf("LoadDG_AdjMatrix:The AdjMatrixGraph is not empty.\n");
        return ERROR;
    }
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("LoadDG_AdjMatrix:failed to open file '%s'\n",filename);
        return ERROR;        
    }

    fscanf(fp,"Graphkind:%d\n",&G->kind);
    fscanf(fp, "%1[\n]",tmp);
    if(G->kind!=DG){
        printf("LoadDG_AdjMatrix:Graphkind is not compitible!\n");
        return ERROR;           
    }
    int IncInfo=0;//边信息指针标记
    fscanf(fp, "IncInfo=%d\n",&IncInfo);
    fscanf(fp, "%1[\n]",tmp);
    fscanf(fp, "vexnum:%d,arcnum:%d\n", &G->vexnum, &G->arcnum);   
    fscanf(fp, "%7s",tmp);
    
    for (int i = 0; i < G->vexnum;i++){//初始化邻接矩阵
        for (int j = 0; j < G->vexnum;j++){
            G->arcs[i][j].adj = 0;
            G->arcs[i][j].info = NULL;
        }
    }

    for (int i = 0; i < G->vexnum; i++){//存储顶点数据
        fscanf(fp, "%c", &G->vexs[i]);
    }

    fscanf(fp, "%1[\n]",tmp);
    VertexType v1,v2;
    int p1,p2;
    for(int k=0;k<G->arcnum;k++){
        fscanf(fp,"<%c,%c>", &v1, &v2);
        p1 = LocateVex_AdjMatrix(*G, v1);
        p2 = LocateVex_AdjMatrix(*G, v2);
        if(p1>=0&&p2>=0){
            G->arcs[p1][p2].adj=1;
            if(IncInfo){
                InfoType *info = (InfoType *)malloc(sizeof(InfoType));
                fscanf(fp," Info:%d\n", info);
                G->arcs[p2][p1].info = G->arcs[p1][p2].info = info;
            }else{
                fscanf(fp, "%10s", tmp);
                fscanf(fp, "%*1[\n]");
            }
        }else{
            printf("LoadDG_AdjMatrix:Can't find vertex %c or vertex %c\n", v1, v2);
            return ERROR;
        }
    }
    fclose(fp);
    return OK;
}

void DFS_DG(MGraph G,int v0){
    visitmark[v0]=1;
    VisitFunc(G.vexs[v0]);
    int v1 = FirstAdjVex_DG(G, v0);
    while(v1>=0){
        if(!visitmark[v1]){
            DFS_DG(G, v1);
        }
        v1 = NextAdjVex_DG(G, v0, v1);
    }
}

//从下标为index的顶点开始，深度优先遍历一个邻接矩阵有向图
Status DFSTranverAdjMatrix_DG(MGraph G,int index,Status (*visit)(VertexType vertex)){
    if(index<0||index>=G.vexnum){
        printf("DFSTranverAdjMatrix_DG:error,vertex index is not existed.\n");
        return ERROR;
    }
    VisitFunc = visit;
    for (int i = 0; i < G.vexnum;i++){
        visitmark[i] = 0;
    }
    for (int i = index; i < G.vexnum+index;i++){
        if(!visitmark[i%G.vexnum]){
            DFS_DG(G, i%G.vexnum);
        }
    }
    return OK;
}


//创建一个用邻接矩阵表示的有向网
Status CreateDN_AdjMatrix(MGraph *N){
    //如果网不空，则返回错误(查看图的顶点个数)
    if(N->vexnum>0){
        printf("CreateDN_AdjMatrix:The AdjMatrixGraph is not empty.\n");
        return ERROR;
    }
    //初始化图的类型
    N->kind = DN;
    //首先输入顶点个数、弧个数，和弧是否有相关信息标志。
    printf("DN_AdjMatrix is Creating:\n");
    printf("Please input the total number of vertex:");
    scanf("%d", &N->vexnum);
    printf("Please input the total number of arc:");
    scanf("%d", &N->arcnum);
    int IncInfo;
    printf("If the ArcCell include extra information,please input '1',else input '0'\n");
    scanf("%d", &IncInfo);
    //根据顶点个数创建顶点向量
    scanf("%*[^\n]");
    scanf("%*c");
    printf("Please input the vertex one bye one,use space key to split.\n");
    for (int i = 0; i < N->vexnum;i++){
        scanf("%c", &N->vexs[i]);
        scanf("%*[ ]");
    }
    //初始化邻接矩阵
    for (int i = 0; i < N->vexnum;i++){
        for (int j = 0; j < N->vexnum;j++){
            N->arcs[i][j].adj = INFINITY;
            N->arcs[i][j].info = NULL;
        }
    }
    //根据弧的个数创建邻接矩阵(包含是否需要录入弧的相关信息)
    VertexType v1,v2;
    VRType adj;
    int p1, p2;
    for (int k = 0; k < N->arcnum;k++){
        printf("Please input arc[%d]:..(format:vertex,vertex weight)\n", k);
        scanf("%*[^\n]");
        scanf("%*c");
        scanf("%c,%c %d", &v1, &v2,&adj);
        p1 = LocateVex_AdjMatrix(*N, v1);
        p2 = LocateVex_AdjMatrix(*N, v2);
        if(p1>=0&&p2>=0){
            N->arcs[p1][p2].adj = adj;
            if(IncInfo){
                InfoType *info = (InfoType *)malloc(sizeof(InfoType));
                printf("Please input the extra information for arc[%c][%c]:\n", v1, v2);
                scanf("%d", info);
                N->arcs[p2][p1].info = N->arcs[p1][p2].info=info;
            }
        }else{
            printf("CreateDN_AdjMatrix:Can't find vertex %c or vertex %c\n", v1, v2);
            k -= 1;
        }
    }
    return OK;
}

int FirstAdjVex_DN(MGraph N,int v0){//在邻接矩阵表示的网中寻找指定结点的第一条边
    for(int j = 0;j<N.vexnum;j++){
        if(N.arcs[v0][j].adj!=INFINITY){
            return j;
        }
    }
    return -1;
}

int NextAdjVex_DN(MGraph N,int v0,int w){//在邻接矩阵表示的网中寻找指定结点的下一条边
    for (int j = w+1; j < N.vexnum;j++){
        if(N.arcs[v0][j].adj!=INFINITY){
            return j;
        }        
    }
    return -1;
}

//保存一个用邻接矩阵表示的有向网
Status SaveDN_AdjMatrix(MGraph N,char *filename){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        printf("SaveDN_AdjMatrix:failed to open file '%s'\n",filename);
        return ERROR;        
    }
    fprintf(fp,"Graphkind:%d\n",N.kind);

    int IncInfo=0;//边信息指针标记
    int arc;
    for (int i = 0; i < N.vexnum;i++){//遍历每个顶点的第一条边，只要找到一条边的info指针不等于空，说明输入了info信息，则将IncInfo置1，然后退出循环。
        arc = FirstAdjVex_DN(N, i);
        if(arc>=0&&N.arcs[i][arc].info!=NULL){
            IncInfo = 1;
            break;
        }
    }

    fprintf(fp, "IncInfo=%d\n", IncInfo);
    fprintf(fp, "vexnum:%d,arcnum:%d\n", N.vexnum, N.arcnum);//存储顶点个数和边数个数信息
    fprintf(fp, "vertex:");
    for (int i = 0; i < N.vexnum; i++){//存储顶点数据
        fprintf(fp, "%c", N.vexs[i]);
    }
    fprintf(fp, "\n");
    for(int i=0;i<N.vexnum;i++){
        for(int j=0;j<N.vexnum;j++){
            if(N.arcs[i][j].adj!=INFINITY){
                fprintf(fp, "<%c,%c> weight:%d",N.vexs[i],N.vexs[j],N.arcs[i][j].adj);
                if(IncInfo){
                    fprintf(fp, " Info:%d\n",*(N.arcs[i][j].info));
                }else{
                    fprintf(fp, " Info:NULL\n");
                }
            }
        }
    }
    fclose(fp);
    return OK;
}

//加载一个用邻接矩阵表示的有向网
Status LoadDN_AdjMatrix(MGraph *N,char *filename){
    char tmp[20];//临时接收回车等垃圾字符
    if(N->vexnum>0){//如果图不空，则返回错误，只能用空图接收
        printf("LoadDN_AdjMatrix:The AdjMatrixGraph is not empty.\n");
        return ERROR;
    }
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("LoadDN_AdjMatrix:failed to open file '%s'\n",filename);
        return ERROR;        
    }

    fscanf(fp,"Graphkind:%d\n",&N->kind);
    fscanf(fp, "%1[\n]",tmp);
    if(N->kind!=DN){
        printf("LoadDN_AdjMatrix:Graphkind is not compitible!\n");
        return ERROR;           
    }
    int IncInfo=0;//边信息指针标记
    fscanf(fp, "IncInfo=%d\n",&IncInfo);
    fscanf(fp, "%1[\n]",tmp);
    fscanf(fp, "vexnum:%d,arcnum:%d\n", &N->vexnum, &N->arcnum);   
    fscanf(fp, "%7s",tmp);
    
    for (int i = 0; i < N->vexnum;i++){//初始化邻接矩阵
        for (int j = 0; j < N->vexnum;j++){
            N->arcs[i][j].adj = INFINITY;
            N->arcs[i][j].info = NULL;
        }
    }

    for (int i = 0; i < N->vexnum; i++){//存储顶点数据
        fscanf(fp, "%c", &N->vexs[i]);
    }

    fscanf(fp, "%1[\n]",tmp);
    VertexType v1,v2;
    VRType weight;
    int p1,p2;
    for(int k=0;k<N->arcnum;k++){
        fscanf(fp,"<%c,%c> weight:%d", &v1, &v2,&weight);
        p1 = LocateVex_AdjMatrix(*N, v1);
        p2 = LocateVex_AdjMatrix(*N, v2);
        if(p1>=0&&p2>=0){
            N->arcs[p1][p2].adj = weight;
            if(IncInfo){
                InfoType *info = (InfoType *)malloc(sizeof(InfoType));
                fscanf(fp," Info:%d\n", info);
                N->arcs[p2][p1].info = N->arcs[p1][p2].info = info;
            }else{
                fscanf(fp, "%10s", tmp);
                fscanf(fp, "%*1[\n]");
            }
        }else{
            printf("LoadDN_AdjMatrix:Can't find vertex %c or vertex %c\n", v1, v2);
            return ERROR;
        }
    }
    fclose(fp);
    return OK;
}

void DFS_DN(MGraph N,int v0){
    visitmark[v0]=1;
    VisitFunc(N.vexs[v0]);
    int v1 = FirstAdjVex_DN(N, v0);
    while(v1>=0){
        if(!visitmark[v1]){
            DFS_DN(N, v1);
        }
        v1 = NextAdjVex_DN(N, v0, v1);
    }
}

//从下标为index的顶点开始，深度优先遍历一个邻接矩阵有向网
Status DFSTranverAdjMatrix_DN(MGraph N,int index,Status (*visit)(VertexType vertex)){
    if(index<0||index>=N.vexnum){
        printf("DFSTranverAdjMatrix_DN:error,vertex index is not existed.\n");
        return ERROR;
    }
    VisitFunc = visit;
    for (int i = 0; i < N.vexnum;i++){
        visitmark[i] = 0;
    }
    for (int i = index; i < N.vexnum+index;i++){
        if(!visitmark[i%N.vexnum]){
            DFS_DN(N, i%N.vexnum);
        }
    }
    return OK;
}


//创建一个用邻接矩阵表示的无向图
Status CreateUDG_AdjMatrix(MGraph *G){
    //如果图不空，则返回错误(查看图的顶点个数)
    if(G->vexnum>0){
        printf("CreateUDG_AdjMatrix:The AdjMatrixGraph is not empty.\n");
        return ERROR;
    }
    //初始化图的类型
    G->kind = UDG;
    printf("UDG_AdjMatrix is Creating:\n");
    //首先输入顶点个数、弧个数，和弧是否有相关信息标志。
    printf("Please input the total number of vertex:");
    scanf("%d", &G->vexnum);
    printf("Please input the total number of edge:");
    scanf("%d", &G->arcnum);
    int IncInfo;
    printf("If the ArcCell include extra information,please input '1',else input '0'\n");
    scanf("%d", &IncInfo);
    //根据顶点个数创建顶点向量
    scanf("%*[^\n]");
    scanf("%*c");
    printf("Please input the vertex one bye one,use space key to split.\n");
    for (int i = 0; i < G->vexnum;i++){
        scanf("%c", &G->vexs[i]);
        scanf("%*[ ]");
    }
    //初始化邻接矩阵
    for (int i = 0; i < G->vexnum;i++){
        for (int j = 0; j < G->vexnum;j++){
            G->arcs[i][j].adj = 0;
            G->arcs[i][j].info = NULL;
        }
    }
    //根据弧的个数创建邻接矩阵(包含是否需要录入弧的相关信息)
    VertexType v1,v2;

    int p1, p2;
    for (int k = 0; k < G->arcnum;k++){
        printf("Please input edge[%d]:..(format:vertex,vertex)\n", k);
        scanf("%*[^\n]");
        scanf("%*c");
        scanf("%c,%c", &v1, &v2);
        p1 = LocateVex_AdjMatrix(*G, v1);
        p2 = LocateVex_AdjMatrix(*G, v2);
        if(p1>=0&&p2>=0){
            G->arcs[p1][p2].adj =G->arcs[p2][p1].adj= 1;
            if(IncInfo){
                InfoType *info = (InfoType *)malloc(sizeof(InfoType));
                printf("Please input the extra information for edge[%c][%c]:\n", v1, v2);
                scanf("%d", info);
                G->arcs[p2][p1].info = G->arcs[p1][p2].info=info;
            }
        }else{
            printf("CreateUDG_AdjMatrix:Can't find vertex %c or vertex %c\n", v1, v2);
            k -= 1;
        }
    }
    return OK;
}

int FirstAdjVex_UDG(MGraph G,int v0){
    for(int j = 0;j<G.vexnum;j++){
        if(G.arcs[v0][j].adj==1){
            return j;
        }
    }
    return -1;
}

int NextAdjVex_UDG(MGraph G,int v0,int w){
    for (int j = w+1; j < G.vexnum;j++){
        if(G.arcs[v0][j].adj==1){
            return j;
        }        
    }
    return -1;
}

//保存一个用邻接矩阵表示的无向图
Status SaveUDG_AdjMatrix(MGraph G,char *filename){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        printf("SaveUDG_AdjMatrix:failed to open file '%s'\n",filename);
        return ERROR;        
    }
    fprintf(fp,"Graphkind:%d\n",G.kind);

    int IncInfo=0;//边信息指针标记
    int edge;
    for (int i = 0; i < G.vexnum;i++){//遍历每个顶点的第一条边，只要找到一条边的info指针不等于空，说明输入了info信息，则将IncInfo置1，然后退出循环。
        edge = FirstAdjVex_UDG(G, i);
        if(edge>=0&&G.arcs[i][edge].info!=NULL){
            IncInfo = 1;
            break;
        }
    }

    fprintf(fp, "IncInfo=%d\n", IncInfo);
    fprintf(fp, "vexnum:%d,edgenum:%d\n", G.vexnum, G.arcnum);//存储顶点个数和边数个数信息
    fprintf(fp, "vertex:");
    for (int i = 0; i < G.vexnum; i++){//存储顶点数据
        fprintf(fp, "%c", G.vexs[i]);
    }
    fprintf(fp, "\n");
    for(int i=0;i<G.vexnum;i++){
        for(int j=i;j<G.vexnum;j++){
            if(G.arcs[i][j].adj!=0){
                fprintf(fp, "(%c,%c)",G.vexs[i],G.vexs[j]);
                if(IncInfo){
                    fprintf(fp, " Info:%d\n",*G.arcs[i][j].info);
                }else{
                    fprintf(fp, " Info:NULL\n");
                }
            }
        }
    }
    fclose(fp);
    return OK;
}

//加载一个用邻接矩阵表示的无向图
Status LoadUDG_AdjMatrix(MGraph *G,char *filename){
    char tmp[20];//临时接收回车等垃圾字符
    if(G->vexnum>0){//如果图不空，则返回错误，只能用空图接收
        printf("LoadUDG_AdjMatrix:The AdjMatrixGraph is not empty.\n");
        return ERROR;
    }
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("LoadUDG_AdjMatrix:failed to open file '%s'\n",filename);
        return ERROR;        
    }

    fscanf(fp,"Graphkind:%d\n",&G->kind);
    fscanf(fp, "%1[\n]",tmp);
    if(G->kind!=UDG){
        printf("LoadUDG_AdjMatrix:Graphkind is not compitible!\n");
        return ERROR;           
    }
    int IncInfo=0;//边信息指针标记
    fscanf(fp, "IncInfo=%d\n",&IncInfo);
    fscanf(fp, "%1[\n]",tmp);
    fscanf(fp, "vexnum:%d,edgenum:%d\n", &G->vexnum, &G->arcnum);   
    fscanf(fp, "%7s",tmp);
    
    for (int i = 0; i < G->vexnum;i++){//初始化邻接矩阵
        for (int j = 0; j < G->vexnum;j++){
            G->arcs[i][j].adj = 0;
            G->arcs[i][j].info = NULL;
        }
    }

    for (int i = 0; i < G->vexnum; i++){//存储顶点数据
        fscanf(fp, "%c", &G->vexs[i]);
    }

    fscanf(fp, "%1[\n]",tmp);
    VertexType v1,v2;
    int p1,p2;
    for(int k=0;k<G->arcnum;k++){
        fscanf(fp,"(%c,%c)", &v1, &v2);
        p1 = LocateVex_AdjMatrix(*G, v1);
        p2 = LocateVex_AdjMatrix(*G, v2);
        if(p1>=0&&p2>=0){
            G->arcs[p1][p2].adj =G->arcs[p2][p1].adj= 1;
            if(IncInfo){
                InfoType *info = (InfoType *)malloc(sizeof(InfoType));
                fscanf(fp," Info:%d\n", info);
                G->arcs[p2][p1].info = G->arcs[p1][p2].info = info;
            }else{
                fscanf(fp, "%10s", tmp);
                fscanf(fp, "%*1[\n]");
            }
        }else{
            printf("LoadUDG_AdjMatrix:Can't find vertex %c or vertex %c\n", v1, v2);
            return ERROR;
        }
    }
    fclose(fp);
    return OK;
}

void DFS_UDG(MGraph G,int v0){
    visitmark[v0]=1;
    VisitFunc(G.vexs[v0]);
    int v1 = FirstAdjVex_UDG(G, v0);
    while(v1>=0){
        if(!visitmark[v1]){
            DFS_UDG(G, v1);
        }
        v1 = NextAdjVex_UDG(G, v0, v1);
    }
}

//从下标为index的顶点开始，深度优先遍历一个邻接矩阵图
Status DFSTranverAdjMatrix_UDG(MGraph G,int index,Status (*visit)(VertexType vertex)){
    if(index<0||index>=G.vexnum){
        printf("DFSTranverAdjMatrix_UDG:error,vertex index is not existed.\n");
        return ERROR;
    }
    VisitFunc = visit;
    for (int i = 0; i<G.vexnum;i++){
        visitmark[i] = 0;
    }
    for (int i = index; i<G.vexnum+index;i++){//从第index个顶点开始，遍历所有顶点
        if(!visitmark[i%G.vexnum]){
            DFS_UDG(G,i%G.vexnum);
        }
    }
    return OK;
}


//创建一个用邻接矩阵表示的无向网
Status CreateUDN_AdjMatrix(MGraph *N){
    //如果网不空，则返回错误(查看图的顶点个数)
    if(N->vexnum>0){
        printf("CreateUDN_AdjMatrix:The AdjMatrixGraph is not empty.\n");
        return ERROR;
    }
    //初始化图的类型
    N->kind = UDN;
    //首先输入顶点个数、弧个数，和弧是否有相关信息标志。
    printf("UDN_AdjMatrix is Creating:\n");
    printf("Please input the total number of vertex:");
    scanf("%d", &N->vexnum);
    printf("Please input the total number of edge:");
    scanf("%d", &N->arcnum);
    int IncInfo;
    printf("If the ArcCell include extra information,please input '1',else input '0'\n");
    scanf("%d", &IncInfo);
    //根据顶点个数创建顶点向量
    scanf("%*[^\n]");
    scanf("%*c");
    printf("Please input the vertex one bye one,use space key to split.\n");
    for (int i = 0; i < N->vexnum;i++){
        scanf("%c", &N->vexs[i]);
        scanf("%*[ ]");
    }
    //初始化邻接矩阵
    for (int i = 0; i < N->vexnum;i++){
        for (int j = 0; j < N->vexnum;j++){
            N->arcs[i][j].adj = INFINITY;
            N->arcs[i][j].info = NULL;
        }
    }
    //根据弧的个数创建邻接矩阵(包含是否需要录入弧的相关信息)
    VertexType v1,v2;
    VRType adj;
    int p1, p2;
    for (int k = 0; k < N->arcnum;k++){
        printf("Please input edge[%d]:..(format:vertex,vertex weight)\n", k);
        scanf("%*[^\n]");
        scanf("%*c");
        scanf("%c,%c %d", &v1, &v2,&adj);
        p1 = LocateVex_AdjMatrix(*N, v1);
        p2 = LocateVex_AdjMatrix(*N, v2);
        if(p1>=0&&p2>=0){
            N->arcs[p1][p2].adj =N->arcs[p2][p1].adj= adj;
            if(IncInfo){
                InfoType *info = (InfoType *)malloc(sizeof(InfoType));
                printf("Please input the extra information for edge[%c][%c]:\n", v1, v2);
                scanf("%d", info);
                N->arcs[p2][p1].info = N->arcs[p1][p2].info=info;
            }
        }else{
            printf("CreateUDN_AdjMatrix:Can't find vertex %c or vertex %c\n", v1, v2);
            k -= 1;
        }
    }
    return OK;
}

int FirstAdjVex_UDN(MGraph N,int v0){//在邻接矩阵表示的网中寻找指定结点的第一条边
    for(int j = 0;j<N.vexnum;j++){
        if(N.arcs[v0][j].adj!=INFINITY){
            return j;
        }
    }
    return -1;
}

int NextAdjVex_UDN(MGraph N,int v0,int w){//在邻接矩阵表示的网中寻找指定结点的下一条边
    for (int j = w+1; j < N.vexnum;j++){
        if(N.arcs[v0][j].adj!=INFINITY){
            return j;
        }        
    }
    return -1;
}

//保存一个用邻接矩阵表示的无向网
Status SaveUDN_AdjMatrix(MGraph N,char *filename){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        printf("SaveUDN_AdjMatrix:failed to open file '%s'\n",filename);
        return ERROR;        
    }
    fprintf(fp,"Graphkind:%d\n",N.kind);

    int IncInfo=0;//边信息指针标记
    int edge;
    for (int i = 0; i < N.vexnum;i++){//遍历每个顶点的第一条边，只要找到一条边的info指针不等于空，说明输入了info信息，则将IncInfo置1，然后退出循环。
        edge = FirstAdjVex_UDN(N, i);
        if(edge>=0&&N.arcs[i][edge].info!=NULL){
            IncInfo = 1;
            break;
        }
    }

    fprintf(fp, "IncInfo=%d\n", IncInfo);
    fprintf(fp, "vexnum:%d,edgenum:%d\n", N.vexnum, N.arcnum);//存储顶点个数和边数个数信息
    fprintf(fp, "vertex:");
    for (int i = 0; i < N.vexnum; i++){//存储顶点数据
        fprintf(fp, "%c", N.vexs[i]);
    }
    fprintf(fp, "\n");
    for(int i=0;i<N.vexnum;i++){
        for(int j=i;j<N.vexnum;j++){
            if(N.arcs[i][j].adj!=INFINITY){
                fprintf(fp, "(%c,%c) weight:%d",N.vexs[i],N.vexs[j],N.arcs[i][j].adj);
                if(IncInfo){
                    fprintf(fp, " Info:%d\n",*(N.arcs[i][j].info));
                }else{
                    fprintf(fp, " Info:NULL\n");
                }
            }
        }
    }
    fclose(fp);
    return OK;
}

//加载一个用邻接矩阵表示的无向网
Status LoadUDN_AdjMatrix(MGraph *N,char *filename){
    char tmp[20];//临时接收回车等垃圾字符
    if(N->vexnum>0){//如果图不空，则返回错误，只能用空图接收
        printf("LoadUDN_AdjMatrix:The AdjMatrixGraph is not empty.\n");
        return ERROR;
    }
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("LoadUDN_AdjMatrix:failed to open file '%s'\n",filename);
        return ERROR;        
    }

    fscanf(fp,"Graphkind:%d\n",&N->kind);
    fscanf(fp, "%1[\n]",tmp);
    if(N->kind!=UDN){
        printf("LoadUDN_AdjMatrix:Graphkind is not compitible!\n");
        return ERROR;           
    }
    int IncInfo=0;//边信息指针标记
    fscanf(fp, "IncInfo=%d\n",&IncInfo);
    fscanf(fp, "%1[\n]",tmp);
    fscanf(fp, "vexnum:%d,edgenum:%d\n", &N->vexnum, &N->arcnum);   
    fscanf(fp, "%7s",tmp);
    
    for (int i = 0; i < N->vexnum;i++){//初始化邻接矩阵
        for (int j = 0; j < N->vexnum;j++){
            N->arcs[i][j].adj = 0;
            N->arcs[i][j].info = NULL;
        }
    }

    for (int i = 0; i < N->vexnum; i++){//存储顶点数据
        fscanf(fp, "%c", &N->vexs[i]);
    }

    fscanf(fp, "%1[\n]",tmp);
    VertexType v1,v2;
    VRType weight;
    int p1,p2;
    for(int k=0;k<N->arcnum;k++){
        fscanf(fp,"(%c,%c) weight:%d", &v1, &v2,&weight);
        p1 = LocateVex_AdjMatrix(*N, v1);
        p2 = LocateVex_AdjMatrix(*N, v2);
        if(p1>=0&&p2>=0){
            N->arcs[p1][p2].adj =N->arcs[p2][p1].adj= weight;
            if(IncInfo){
                InfoType *info = (InfoType *)malloc(sizeof(InfoType));
                fscanf(fp," Info:%d\n", info);
                N->arcs[p2][p1].info = N->arcs[p1][p2].info = info;
            }else{
                fscanf(fp, "%10s", tmp);
                fscanf(fp, "%*1[\n]");
            }
        }else{
            printf("LoadUDN_AdjMatrix:Can't find vertex %c or vertex %c\n", v1, v2);
            return ERROR;
        }
    }
    fclose(fp);
    return OK;
}

void DFS_UDN(MGraph N,int v0){
    visitmark[v0]=1;
    VisitFunc(N.vexs[v0]);
    int v1 = FirstAdjVex_UDN(N, v0);
    while(v1>=0){
        if(!visitmark[v1]){
            DFS_UDN(N, v1);
        }
        v1 = NextAdjVex_UDN(N, v0, v1);
    }
}

//从下标为index的顶点开始，深度优先遍历一个邻接矩阵图
Status DFSTranverAdjMatrix_UDN(MGraph N,int index,Status (*visit)(VertexType vertex)){
    if(index<0||index>=N.vexnum){
        printf("DFSTranverAdjMatrix_UDN:error,vertex index is not existed.\n");
        return ERROR;
    }
    VisitFunc = visit;
    for (int i = 0; i < N.vexnum;i++){
        visitmark[i] = 0;
    }
    for (int i = index; i < N.vexnum+index;i++){
        if(!visitmark[i%N.vexnum]){
            DFS_UDN(N, i%N.vexnum);
        }
    }
    return OK;
}





//销毁一个用邻接矩阵表示的图/网
Status DestroyAdjMatrix(MGraph *G){
    if(G->vexnum<=0){
        printf("DestroyAdjMatrix:failed to destroy,because the Graph have not been Created.\n");
        return ERROR;
    }
    for (int i = 0; i < G->vexnum;i++){
        for (int j = 0; j < G->vexnum;j++){
            if(G->arcs[i][j].adj==1||G->arcs[i][j].adj==INFINITY){
                free(G->arcs[i][j].info);
                G->arcs[i][j].adj = 0;
            }
        }
    }
    for (int i = 0; i < G->vexnum;i++){
        G->vexs[i] = 0;
    }
    G->vexnum = 0;
    G->arcnum = 0;
    G->kind = 0;
    return OK;
}


//查找定位邻接表图中第一个值为value的定点，返回其在顶点向量中的下标，若没有找到就返回-1
int LocateVex_AdjList(ALGraph G,VertexType value){
    int i=0;
    while(i<G.vexnum){
        if(G.vertexs[i].data==value){
            return i;
        }else{
            i++;
        }
    }
    return INFEASIBLE;
}

//创建一个用邻接表表示的无向图
Status CreateUDG_AdjList(ALGraph *G){
    //如果图不空，则返回错误(查看图的顶点个数)
    if(G->vexnum>0){
        printf("CreateUDG_AdjList:The AdjListGraph is not empty.\n");
        return ERROR;
    }
    //首先输入顶点个数、弧个数，和弧是否有相关信息标志。
    printf("Please input the total number of vertex:");
    scanf("%d", &G->vexnum);
    printf("Please input the total number of arc:");
    scanf("%d", &G->arcnum);
    int IncInfo;
    printf("If the ArcNode include extra information,please input '1',else input '0'\n");
    scanf("%d", &IncInfo);
    //根据顶点个数创建顶点向量
    scanf("%*[^\n]");
    scanf("%*c");
    printf("Please input the vertex one bye one,use a space char to split.\n");
    for (int i = 0; i < G->vexnum;i++){
        scanf("%c", &G->vertexs[i].data);
        scanf("%*[ ]");
        G->vertexs[i].firstarc = NULL;
    }
    //根据弧的个数，创建相应顶点的弧链表结点
    VertexType v1, v2;
    ArcNode *node1, *node2;//在使用时分别和V1，v2对应，分别表示v1顶点的一个弧结点，v2顶点的一个弧结点
    int p1, p2;
    for (int k = 0; k < G->arcnum;k++){
        printf("Please input arc[%d]:..(format:vertex,vertex)\n", k);
        scanf("%*[^\n]");
        scanf("%*c");
        scanf("%c,%c", &v1, &v2);
        p1 = LocateVex_AdjList(*G, v1);
        p2 = LocateVex_AdjList(*G, v2);
        if(p1>=0&&p2>=0){
            node1 = (ArcNode *)malloc(sizeof(ArcNode));
            node2 = (ArcNode *)malloc(sizeof(ArcNode));
            if(IncInfo){
                printf("Please input the extra information for arc[%c][%c]:\n", v1, v2);
                scanf("%d", node1->info);
                node2->info = node1->info;
            }else{
                node1->info = node2->info = NULL;
            }
            node1->adj = node2->adj = 1;//这里因为是创建无向图，所以给结点的关系类型赋值1，如果是网络，应该改为相应的权重
            node1->adjvex = p2;
            node2->adjvex = p1;
            node1->nextarc = G->vertexs[p1].firstarc;
            G->vertexs[p1].firstarc = node1;
            node2->nextarc = G->vertexs[p2].firstarc;
            G->vertexs[p2].firstarc = node2;
        }else{
            printf("CreateUDG_AdjList:Can't find vertex %c or vertex %c\n", v1, v2);
            k -= 1;
        }
    }
    return OK;
}

//查找定位十字链表图中第一个值为value的定点，返回其在顶点向量中的下标，若没有找到就返回-1
int LocateVex_OLGraph(OLGraph G, VertexType value){
    int i;
    for (i = 0; i < G.vexnum;i++){
        if(G.xlist[i].data==value){
            return i;
        }
    }
    return INFEASIBLE;
}


//创建一个用十字链表表示的有向图
Status CreateDG_OLGraph(OLGraph *G){
    //如果图不空，则返回错误(查看图的顶点个数)
    if(G->vexnum>0){
        printf("CreateDG_OLGraph:The CrossList Graph is not empty.\n");
        return ERROR;
    }
    
    //首先输入顶点个数、弧个数，和弧是否有相关信息标志。
    printf("Please input the total number of vertex:");
    scanf("%d", &G->vexnum);
    printf("Please input the total number of arc:");
    scanf("%d", &G->arcnum);
    int IncInfo;
    printf("If the ArcNode include extra information,please input '1',else input '0'\n");
    scanf("%d", &IncInfo);
    //根据顶点个数创建顶点向量
    scanf("%*[^\n]");
    scanf("%*c");
    printf("Please input the vertex one bye one,use a space char to split.\n");
    for (int i = 0; i < G->vexnum;i++){
        scanf("%c", &G->xlist[i].data);
        scanf("%*[ ]");
        G->xlist[i].firstin=G->xlist[i].firstout = NULL;
    }
    //根据弧的个数，创建相应顶点的弧结点
    VertexType v1, v2;//接收输入的顶点值
    ArcBox *newArc;//用来暂存新创建的弧结点指针
    int p1, p2;//用来存放v1和v2在G中的位置下标
    for (int k = 0; k < G->arcnum;k++){
        printf("Please input arc[%d]:..(format:vertex,vertex)\n", k);
        scanf("%*[^\n]");
        scanf("%*c");
        scanf("%c,%c", &v1, &v2);
        p1 = LocateVex_OLGraph(*G, v1);
        p2 = LocateVex_OLGraph(*G, v2);
        if(p1>=0&&p2>=0){
            newArc = (ArcBox *)malloc(sizeof(ArcBox));
            if(IncInfo){
                printf("Please input the extra information for arc[%c][%c]:\n", v1, v2);
                scanf("%d", newArc->info);
            }else{
                newArc->info = NULL;
            }
            newArc->adj = 1;//这里因为是创建图，所以给结点的关系类型赋值1，如果是网络，应该改为相应的权重
            newArc->tailvex = p1;//新弧结点的弧尾是p1（v1）
            newArc->headvex = p2;//新弧结点的弧头是p2（v2）
            newArc->tlink = G->xlist[p1].firstout;//将新弧结点的下一个弧尾相同的结点的指针，指向原来p1.firstout指向的弧
            newArc->hlink = G->xlist[p2].firstin;//将新弧结点的下一个弧头相同的结点的指针，指向原来p2.firstin指向的弧
            G->xlist[p1].firstout = newArc;//新弧结点代替原来p1的firstout
            G->xlist[p2].firstin = newArc;//新弧结点代替原来p2的firstin
        }else{
            printf("CreateDG_OLGraph:Can't find vertex %c or vertex %c\n", v1, v2);
            k -= 1;
        }
    }
    return OK;
}


//查找定位十字链表图中第一个值为value的定点，返回其在顶点向量中的下标，若没有找到就返回-1
int LocateVex_AMLGraph(AMLGraph G, VertexType value){
    int i;
    for (i = 0; i < G.vexnum;i++){
        if(G.adjmulist[i].data==value){
            return i;
        }
    }
    return INFEASIBLE;
}


//创建一个用邻接多重表表示的无向图
Status CreateUDG_AMLGraph(AMLGraph *G){
    //如果图不空，则返回错误(查看图的顶点个数)
    if(G->vexnum>0){
        printf("CreateUDG_AMLGraph:The Adjacency Mulity List Graph is not empty.\n");
        return ERROR;
    }

    printf("UDG_AMLGraph is Creating:\n");    
    //首先输入顶点个数、弧个数，和弧是否有相关信息标志。
    printf("Please input the total number of vertex:");
    scanf("%d", &G->vexnum);
    printf("Please input the total number of edge:");
    scanf("%d", &G->edgenum);
    int IncInfo;
    printf("If the ArcNode include extra information,please input '1',else input '0'\n");
    scanf("%d", &IncInfo);//IncInfo是个标记，为0时不创建弧的相关信息
    //根据顶点个数创建顶点向量
    scanf("%*[^\n]");
    scanf("%*c");
    printf("Please input the vertex one bye one,use a space char to split.\n");
    for (int i = 0; i < G->vexnum;i++){
        scanf("%c", &G->adjmulist[i].data);
        scanf("%*[ ]");
        G->adjmulist[i].firstedge = NULL;
    }
    //根据弧的个数，创建相应顶点的弧结点
    VertexType v1, v2;//接收输入的顶点值
    EdgeBox *newEdge;//用来暂存新创建的弧结点指针
    int p1, p2;//用来存放v1和v2在G中的位置下标
    for (int k = 0; k < G->edgenum;k++){
        printf("Please input edge[%d]:..(format:vertex,vertex)\n", k);
        scanf("%*[^\n]");
        scanf("%*c");
        scanf("%c,%c", &v1, &v2);
        p1 = LocateVex_AMLGraph(*G, v1);
        p2 = LocateVex_AMLGraph(*G, v2);
        if(p1>=0&&p2>=0){
            newEdge = (EdgeBox *)malloc(sizeof(EdgeBox));
            if(IncInfo){
                printf("Please input the extra information for arc[%c][%c]:\n", v1, v2);
                newEdge->info = (InfoType *)malloc(sizeof(InfoType));
                scanf("%d", newEdge->info);
                scanf("%*[^\n]");
                scanf("%*c");
            }else{
                newEdge->info = NULL;
            }
            newEdge->ivex = p1;//新边结点的一头p1（v1）
            newEdge->jvex = p2;//新边结点的另一头是p2（v2）
            newEdge->ilink = G->adjmulist[p1].firstedge;//将新边结点的下一个依附点为i的边结点的指针，指向原来p1.firstedge指向的边
            newEdge->jlink = G->adjmulist[p2].firstedge;//将新边结点的下一个依附点为j的边结点的指针，指向原来p2.frestedge指向的边
            G->adjmulist[p1].firstedge = newEdge;//新弧结点代替原来p1的firstout
            G->adjmulist[p2].firstedge = newEdge;//新弧结点代替原来p2的firstin
        }else{
            printf("CreateUDG_AMLGraph:Can't find vertex %c or vertex %c\n", v1, v2);
            k -= 1;
        }
    }
    return OK;
}

//保存一个无向图或无向网（权值保存在info中）（邻接多重表）的信息到文件中
Status SaveAMLGraph(AMLGraph G,char *filename){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        printf("SaveAMLGraph:failed to open file '%s'\n",filename);
        return ERROR;        
    }
    EdgeBox *p=G.adjmulist[0].firstedge;//初始化边指针

    int IncInfo=0;//存储图的基本信息，图的类别，边指针是否有其他信息等。
    if(p->info!=NULL){
        IncInfo = 1;//边是否有其他信息的标记
        fprintf(fp, "Graphkind:3\n");//3：是枚举类型Granphkind的UDN
        fprintf(fp, "IncInfo=%d\n", IncInfo);
    }else{
        fprintf(fp, "Graphkind:2\n");//2，是枚举类型Granphkind的UDG
        fprintf(fp, "IncInfo=%d\n", IncInfo);
    }

    fprintf(fp, "vexnum:%d,edgenum:%d\n", G.vexnum, G.edgenum);//存储顶点个数和边数个数信息
    fprintf(fp, "vertex:");

    for (int i = 0; i < G.vexnum; i++){//存储顶点数据
        fprintf(fp, "%c", G.adjmulist[i].data);
    }
    fprintf(fp, "\n");

    for (int i = 0; i < G.vexnum;i++){//初始化边的访问标记位
        p = G.adjmulist[i].firstedge;
        while(p){
            p->mark = unvisited;
            if(p->ivex==i){
                p = p->ilink;
            }else{
                p = p->jlink;
            }
        }
    }
    for (int i = 0; i < G.vexnum;i++){//依次从每个顶点的第一条边开始搜索
        p = G.adjmulist[i].firstedge;
        while(p){//遍历顶点i的所有边
            if(p->mark==unvisited){
                fprintf(fp, "(%c,%c)", G.adjmulist[p->ivex].data, G.adjmulist[p->jvex].data);//将边信息存储数组
                p->mark = visited;
                if(IncInfo){//如果边有其他信息，就另起一行存进去
                    fprintf(fp, " Info:%d\n", *p->info);
                }else{
                    fprintf(fp, " Info:NULL\n");
                }
            }
            if(p->ivex==i){//将边指针p指向下一条边
                p = p->ilink;
            }else{
                p = p->jlink;
            }
        }
    }
    fclose(fp);
    return OK;
}

//加载一个无向图（邻接多重表）文件的信息到图中
Status LoadAMLGraph(AMLGraph *G,char *filename){
    if(G->vexnum>0){
        printf("LoadAMLGraph:The Adjacency Mulity List Graph is not empty.\n");
        return ERROR;
    }
    char tmp[20];//用来接收并抛弃回车，空格，无用字符等信息

    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("LoadAMLGraph:failed to open file '%s'\n",filename);
        return ERROR;        
    }
    int IncInfo;
    GraphKind kind;
    fscanf(fp, "Graphkind:%d\n",&kind);
    if(kind<2){
        printf("LoadAMLGraph:Graphkind error!Can't load a DG/DN to AMLGraph\n");
        return ERROR;     
    }
    fscanf(fp, "IncInfo=%d\n", &IncInfo);
    
    fscanf(fp, "vexnum:%d,edgenum:%d\n", &G->vexnum, &G->edgenum);
    fscanf(fp, "%7s",tmp);
    for (int i = 0; i < G->vexnum; i++){//存储顶点数据
        fscanf(fp, "%c", &G->adjmulist[i].data);
        G->adjmulist[i].firstedge = NULL;
    }
    fscanf(fp, "%1[\n]",tmp);


//根据弧的个数，创建相应顶点的弧结点
    VertexType v1, v2;//接收输入的顶点值
    EdgeBox *newEdge;//用来暂存新创建的弧结点指针
    int p1, p2;//用来存放v1和v2在G中的位置下标
    for (int k = 0; k < G->edgenum;k++){
        fscanf(fp,"(%c,%c)", &v1, &v2);
        p1 = LocateVex_AMLGraph(*G, v1);
        p2 = LocateVex_AMLGraph(*G, v2);
        if(p1>=0&&p2>=0){
            newEdge = (EdgeBox *)malloc(sizeof(EdgeBox));
            if(IncInfo){
                newEdge->info = (InfoType *)malloc(sizeof(InfoType));
                fscanf(fp," Info:%d\n", newEdge->info);
            }else{
                fscanf(fp,"%11s", tmp);
                newEdge->info = NULL;
            }
            fscanf(fp, "%1[\n]",tmp);
            newEdge->ivex = p1;//新边结点的一头p1（v1）
            newEdge->jvex = p2;//新边结点的另一头是p2（v2）
            newEdge->ilink = G->adjmulist[p1].firstedge;//将新边结点的下一个依附点为i的边结点的指针，指向原来p1.firstedge指向的边
            newEdge->jlink = G->adjmulist[p2].firstedge;//将新边结点的下一个依附点为j的边结点的指针，指向原来p2.frestedge指向的边
            G->adjmulist[p1].firstedge = newEdge;//新弧结点代替原来p1的firstout
            G->adjmulist[p2].firstedge = newEdge;//新弧结点代替原来p2的firstin
        }else{
            printf("LoadAMLGraph:Data error,Can't find vertex %c or vertex %c\n", v1, v2);
            k -= 1;
        }    
    }
    return OK;
}



//取得并返回邻接多重图G中v0顶点的第一个邻接点
int FirstAdjVex(AMLGraph G,int v0){//v0指图G的顶点向量中下标为v0的顶点
    if(G.adjmulist[v0].firstedge==NULL){
        return -1;
    }
    if(G.adjmulist[v0].firstedge->ivex==v0){
        return G.adjmulist[v0].firstedge->jvex;
    }else{
        return G.adjmulist[v0].firstedge->ivex;
    }
}

//取得并返回邻接多重图G中v0顶点的以p为边的下一条边的邻接点位置
int NextAdjVex(AMLGraph G,int v0,EdgeBox **p){
    if( (*p)->ivex==v0){//先找以v0为顶点的下一条边，如果p的ivex=v0，则下一条边是p->ilink，否则p的jvex=v0,那么下一条边是p->jlink
        *p = (*p)->ilink;
    }else{
        *p = (*p)->jlink;
    }
    if(*p&&(*p)->ivex==v0){//找到下一条边(非空，否则返回-1)对应的邻接点，如果边的ivex=v0,那么邻接点是jvex，否则是ivex
        return (*p)->jvex;
    }else if(*p&&(*p)->jvex==v0){
        return (*p)->ivex;
    }else{
        return INFEASIBLE;
    }
}

//从邻接多重表G的v0结点开始递归地深度优先遍历整个图，这个函数只能用在DFSTranverseAMLGraph函数内部
void DFS(AMLGraph G,int v0){
    visitmark[v0] = 1;
    VisitFunc(G.adjmulist[v0].data);
    EdgeBox *p = G.adjmulist[v0].firstedge;//创建一个边指针，初始化指向第一条边
    int v1 = FirstAdjVex(G, v0);
    while(v1>=0){//遍历v0的每一个邻接点
        if(!visitmark[v1]){
            DFS(G, v1);
        }
        v1 = NextAdjVex(G, v0, &p);
    }
}

//从下标为index的顶点开始，利用visit函数深度优先遍历邻接多重图G
Status DFSTranverAMLGraph(AMLGraph G,int index,Status (*visit)(VertexType vertex)){//深度遍历和二叉树的先序遍历有类似
    if(index<0||index>G.vexnum){
        printf("DFSTranverAMLGraph:error,the vertex is not exsited.\n");
        return ERROR;
    }
    //递归实现
    // VisitFunc = visit;
    // for (int i = 0; i < G.vexnum;i++){
    //     visitmark[i] = 0;
    // }
    // for (int i = index; i < G.vexnum+index;i++){
    //     if(!visitmark[i%G.vexnum]){
    //         DFS(G, i%G.vexnum);
    //     }
    // }
    // return OK;

    //非递归实现
    LinkStack S;
    InitStack_L(&S);
    for (int i = 0; i < G.vexnum;i++){
        visitmark[i] = 0;
    }
    int v1;
    EdgeBox *p;
    for(int i=index;i<G.vexnum+index;i++){//为防止G是非连通图，应当将每个顶点当做根，访问一遍
        if(!visitmark[i%G.vexnum]){//如果没被访问过，就开始遍历
            v1 = i%G.vexnum;//v1指针赋值为作为深度遍历时这一颗最小生成树的根(i)
            while(v1>=0||!StackEmpty_L(&S)){
                if(v1>=0&&visitmark[v1]==0){//只要当前树未被访问，就访问后压栈，然后将当前顶点的第一个邻接点赋值指针v1
                    visitmark[v1] = 1;
                    visit(G.adjmulist[v1].data);
                    Push_L(&S, v1);
                    p = G.adjmulist[v1].firstedge;//这个地方，从抽象的角度来看，实际上v1和p应该是同一个含义，都是用来指向下一个邻接点，所以他们的压栈和弹栈操作应当一起进行
                    v1 = FirstAdjVex(G, v1);
                }else{
                    if(v1>=0){//来到这里是因为visitmark=1，说明是因为上个顶点的第一个邻接点被访问过了的缘故
                        GetTop_L(&S, &v1);//让人想起树的后续遍历，实际上只要是不能马上弹栈，而又需要用到栈顶数据时，都可以gettop
                        v1 = NextAdjVex(G, v1, &p);
                    }else{//来到这里是因为v1<0,即邻接点访问完了。
                        Pop_L(&S, &v1);
                        p = G.adjmulist[v1].firstedge;//这个地方，从抽象的角度来看，实际上v1和p应该是同一个含义，都是用来指向下一个邻接点，所以他们的压栈和弹栈操作应当一起进行
                    }
                }
            }
        }
    }
    return OK;
}

//利用visit函数广度优先遍历邻接多重图G
Status BFSTranverAMLGraph(AMLGraph G,Status (*visit)(VertexType vertex)){//广度优先和二叉树的后序遍历类似
    LinkQueue Q;
    InitQueue_L(&Q);
    for(int i=0;i<G.vexnum;i++){
        visitmark[i]=0;
    }
    int v1;
    EdgeBox *p;
    for(int i=0;i<G.vexnum;i++){
        if(!visitmark[i]){//如果结点i没有被访问，就访问，否则什么也不做
            visit(G.adjmulist[v1].data);//先访问
            visitmark[v1]=1;//将访问标记置1
            EnQueue_L(&Q, i);//访问完一个就将它入队列，方便后面再次获得其下标
            while(!QueueEmpty_L(Q)){
                DeQueue_L(&Q, &v1);
                p=G.adjmulist[v1].firstedge;
                v1=FirstAdjVex(G, v1);
                while(v1>=0){//依次访问顶点i的每一个邻接点
                    visit(G.adjmulist[v1].data);
                    visitmark[v1]=1;
                    EnQueue_L(&Q, v1);
                    v1=NextAdjVex(G, v1, &p);
                }
            }
        }
    }
    return OK;
}


//从图G的第v0个顶点开始，递归建立生成树
void DFSTree(AMLGraph G,int v0,Tree *T){
    visitmark[v0] = 1;
    Tree new, last;
    int v1 = FirstAdjVex(G, v0);
    EdgeBox *p = G.adjmulist[v0].firstedge;
    int first = 1;//建立一个首次访问标记，如果是首次访问v1顶点，就置1。在下面的循环体中，只要v1创建了孩子，就置0；
    while(v1>=0){
        if(!visitmark[v1]){
            new = GetTreeNode(G.adjmulist[v1].data, NULL, NULL);
            if(first){
                (*T)->firstchild = new;
                first = 0;
            }else{
                last->nextsibling = new;
            }
            last = new;
            DFSTree(G, v1, &new);//对新创建的结点进行递归遍历
        }
        v1 = NextAdjVex(G, v0, &p);
    }
}

//建立无向图G的深度优先生成森林的孩子兄弟链表T
void DFSForst(AMLGraph G,Tree *F){
    //递归实现
    *F=NULL;
    Tree new,last;
    for (int i = 0; i < G.vexnum;i++){
        visitmark[i] = 0;
    }
    for (int i = 0; i < G.vexnum;i++){
        if(!visitmark[i]){
            new = GetTreeNode(G.adjmulist[i].data, NULL, NULL);
            if(!*F){
                *F = new;
            }else{
                last->nextsibling = new;
            }
            last = new;
            DFSTree(G, i, &new);
        }
    }
    //非递归实现,实际上需要两个栈，一个存图的顶点指针，一个存树的结点指针。采取先序遍历即可实现。在这里没有函数重载，就放弃了。
//     LinkStack S;
//     InitStack_L(&S);
//     for (int i = 0;i<G.vexnum;i++){
//         visitmark[i] = 0;
//     }
    
//     int v1;
//     int first[G.vexnum];
//     for (int i = 0;i<G.vexnum;i++){
//         first[i] = 1;
//     }
//     Tree new, last;
//     EdgeBox *p;
//     *F = NULL;
//     for (int i = 0;i<G.vexnum;i++){
//         if(!visitmark[i]){
//             new = GetTreeNode(G.adjmulist[i].data, NULL, NULL);
//             if(*F){
//                 *F = new;
//             }else{
//                 last->nextsibling = new;
//             }
//             last = new;
//             v1 = FirstAdjVex(G, i);
//             p = G.adjmulist[i].firstedge;

//             v1 = i;
//             while(v1>=0||!StackEmpty_L(&S)){
//                 if(v1>=0&&visitmark[v1]==0){
//                     visitmark[v1] = 1;
//                     new = GetTreeNode(G.adjmulist[v1].data, NULL, NULL);
//                     if(first[v1]){
//                         last->firstchild = new;
//                         first[v1] = 0;
//                     }else{
//                         last->nextsibling = new;
//                     }
//                     last = new;

//                     Push_L(&S, v1);
//                     p = G.adjmulist[v1].firstedge;
//                     v1 = FirstAdjVex(G, v1);
//                 }else{
//                     if(v1>=0){
//                         GetTop_L(&S, &v1);
//                         v1 = NextAdjVex(G, v1, &p);
//                     }else{
//                         Pop_L(&S, &v1);
//                         p = G.adjmulist[v1].firstedge;
//                     }
//                 }
//             }
//         }
//     }
// }
}
