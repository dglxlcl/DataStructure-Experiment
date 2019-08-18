#include <stdio.h>
#include <stdlib.h>
#include "MyGraph.h"
#include "StackAndQueue.h"

int main(){
    // ALGraph G;
    // G.vexnum = 0;
    // G.arcnum = 0;
    // G.kind = UDG;
    // CreateUDG_AdjList(&G);

    MGraph G;
    G.vexnum = 0;
    G.arcnum = 0;
    CreateUDG_AdjMatrix(&G);
    SaveUDG_AdjMatrix(G,"../GraphData/AdjMatrix_UDG01.txt");

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

    // AMLGraph G;
    // G.vexnum = 0;
    // G.edgenum = 0;
    // // CreateUDG_AMLGraph(&G);
    // // SaveAMLGraph(G,"../GraphData/AMLGraph01.txt");
    // LoadAMLGraph(&G,"../GraphData/AMLGraph01.txt");
    // DFSTranverAMLGraph(G, PrintVertex);

    return 0;
}