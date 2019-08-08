#include <stdio.h>
#include <stdlib.h>
#include "MyArray.h"

int main(){
    SMatrix M,N,Q;
    M.data = NULL;
    N.data = NULL;
    Q.data = NULL;
    // CreateSMatrix(&M);
    LoadSMatrix(&M, "..\\MatrixData\\SMatrix_M.txt");
    PrintSMatrix(M);
    // SaveSMatrix(M, "..\\MatrixData\\SMatrix_M.txt");
    putchar('\n');

    // CreateSMatrix(&N);
    LoadSMatrix(&N, "..\\MatrixData\\SMatrix_N.txt");
    PrintSMatrix(N);
    // SaveSMatrix(N, "..\\MatrixData\\SMatrix_N.txt");
    putchar('\n');

    MultSMatrix(M, N, &Q);
    SaveSMatrix(Q, "..\\MatrixData\\SMatrix_Q.txt");
    PrintSMatrix(Q);

    return 0;
}

