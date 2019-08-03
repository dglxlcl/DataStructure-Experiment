#include <stdio.h>
#include <stdlib.h>
#include "StackAndQueue.h"
#include "LinearList.h"

//用递归代实现,两次实验：第一次136.591秒，第二次137.001秒，性能弱于迭代法。

//
//#define row 15
//#define col 15
//
//typedef int ChessTable[row][col];
//
//Status PrintTable(ChessTable table);
//
//Status InitTable(ChessTable table);
//
//Status NotDanger(ChessTable table,int i,int j);//判断row=i,col=j的位置，是否能够摆放棋子
//
//Status PutChess(ChessTable table,int i,int j);//在i,j位置摆放棋子
//
//Status RemoveChess(ChessTable table,int i,int j);//移除i,j位置的棋子
//
//Status EightQueen(int n,ChessTable table);
//
//int count=0;
//
//int main(){
//    ChessTable table;
//    EightQueen(0,table);
//    printf("Total result is :%d",count);
//    return 0;
//}
//
//
//Status InitTable(ChessTable table){
//    for(int i=0;i<row;i++){
//        for(int j=0;j<col;j++){
//            table[i][j]=0;
//        }
//    }
//    return OK;
//}
//
//Status PrintTable(ChessTable table){
//    for(int i=0;i<row;i++){
//        for(int j=0;j<col;j++){
//            printf(" %d",table[i][j]);
//        }
//        printf("\n");
//    }
//    return OK;
//}
//
//Status NotDanger(ChessTable table,int i,int j){
//    int x,y;
//    for(x=0;x<col;x++){
//        if(table[i][x]>0) return FALSE;//说明第i行已经摆了棋子
//    }
//
//    for(y=0;y<row;y++){
//        if(table[y][j]>0) return FALSE;//说明第j列已经摆了棋子
//    }
//
//    x=j-1;y=i-1;
//    while(x>=0&&y>=0){
//        if(table[y][x]>0) return FALSE;//左上方摆了棋子
//        else {
//            x--;y--;
//        }
//    }
//
//    x=j+1;y=i+1;
//    while(x<col&&y<row){
//        if(table[y][x]>0) return FALSE;//右下方摆了棋子
//        else {
//            x++;y++;
//        }
//    }
//
//    x=j+1;y=i-1;
//    while(x<col&&y>=0){
//        if(table[y][x]>0) return FALSE;//右上方摆了棋子
//        else {
//            x++;y--;
//        }
//    }
//
//    x=j-1;y=i+1;
//    while(x>=0&&y<row){
//        if(table[y][x]>0) return FALSE;//左下方摆了棋子
//        else {
//            x--;y++;
//        }
//    }
//    return TRUE;
//}
//
//Status PutChess(ChessTable table,int i,int j){
//    if(i<0||i>row||j<0||j>col) {
//        printf("PutChess:Error,the coordinate is out!\n");
//        return ERROR;
//    }else{
//        table[i][j]=1;
//        return OK;
//    }
//}
//
//Status RemoveChess(ChessTable table,int i,int j){
//    if( (i<0)||(i>row-1)||(j<0)||(j>col-1)) {
//        printf("RemoveChess:Error,the coordinate is out!\n");
//        return ERROR;
//    }else{
//        table[i][j]=0;
//        return OK;
//    }
//}
//
//Status EightQueen(int n,ChessTable table){
//    int i=0,j=0;
//    ChessTable table2;
//    for(i=0;i<row;i++){
//        for(j=0;j<col;j++){
//            table2[i][j]=table[i][j];
//        }
//    }
//    if (n==0){
//        for(j=0;j<col;j++){
//            InitTable(table2);
//            table2[0][j]=1;
//            EightQueen(1,table2);
//        }
//    }else if(n<row-1){
//        for(j=0;j<col;j++){
//            if( NotDanger(table2,n,j) ){
//                table2[n][j]=1;
//                EightQueen(n+1,table2);
//                table2[n][j]=0;
//            }
//        }
//    }else if(n==row-1){
//        for(j=0;j<col;j++){
//            if ( NotDanger(table2,n,j) ){
//                table2[n][j]=1;
////                PrintTable(table2);
//                count++;
////                printf("Num:%d\n\n",count);
//                table2[n][j]=0;
//            }
//        }
//        return OK;
//    }
//    return OK;
//}



