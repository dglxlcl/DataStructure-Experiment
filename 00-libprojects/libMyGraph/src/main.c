#include <stdio.h>
#include <stdlib.h>
#include "MyGraph.h"
#include "StackAndQueue.h"
#include "MyTree.h"

int main(){
    // ALGraph G;
    // G.vexnum = 0;
    // G.arcnum = 0;
    // G.kind = UDG;
    // CreateUDG_AdjList(&G);

    // MGraph G;
    // G.vexnum = 0;
    // G.arcnum = 0;
    // // CreateDN_AdjMatrix(&G);
    // // SaveDN_AdjMatrix(G,"../GraphData/AdjMatrix_DN01.txt");
    // LoadDN_AdjMatrix(&G,"../GraphData/AdjMatrix_DN01.txt");
    // DFSTranverAdjMatrix_DN(G, 2,PrintVertex);

    // CreateDG_AdjMatrix(&G);
    // SaveDG_AdjMatrix(G,"../GraphData/AdjMatrix_DG01.txt");
    // LoadDG_AdjMatrix(&G,"../GraphData/AdjMatrix_DG01.txt");
    // DFSTranverAdjMatrix_DG(G, PrintVertex);


    // OLGraph G;
    // G.vexnum = 0;
    // G.arcnum = 0;
    // G.kind = DG;
    // CreateDG_OLGraph(&G);

    // AMLGraph G;
    // G.vexnum = 0;
    // G.edgenum = 0;
    // CreateUDG_AMLGraph(&G);
    // DFSTranverAMLGraph(G, PrintVertex);

    AMLGraph G;
    G.vexnum = 0;
    G.edgenum = 0;
    // CreateUDG_AMLGraph(&G);
    // SaveAMLGraph(G,"../GraphData/AMLGraph04.txt");
    LoadAMLGraph(&G,"../GraphData/AMLGraph04.txt");
    // DFSTranverAMLGraph(G,0, PrintVertex);
    Tree F;
    DFSForst(G,&F);

    return 0;
}