#include <stdio.h>
#include <stdlib.h>
#include "StackAndQueue.h"
#include "LinearList.h"

//用栈迭代实现，两次实验，第一次118.648秒，第二次119.834秒，性能优于递归法


#define row 8
#define col 8

typedef int ChessTable[row][col];

Status PrintTable(ChessTable table);

Status InitTable(ChessTable table);

Status NotDanger(ChessTable table,int i,int j);//判断row=i,col=j的位置，是否能够摆放棋子

Status PutChess(ChessTable table,int i,int j);//在i,j位置摆放棋子

Status RemoveChess(ChessTable table,int i,int j);//移除i,j位置的棋子

int main(){
    ChessTable table;
    InitTable(table);

    SqStack S;
    InitStack_Sq(&S);
    SElemType CurPos;
    int count=0;
    CurPos.i=-1; CurPos.j=0;
    Push_Sq(&S,CurPos);//将状态转换树的根节点(-1,0)压栈

    CurPos.i=0; CurPos.j=0;//将当前指针指向(0,0)

    do{
        if( NotDanger(table,CurPos.i,CurPos.j) ){

            PutChess(table,CurPos.i,CurPos.j);

//                PrintTable(table);
//                printf("Num:%d\n\n",count);//调试代码

            Push_Sq(&S,CurPos);
            CurPos.i++;  CurPos.j=0;//如果摆棋成功就将指针指向下一行的第一列

            if(CurPos.i>(row-1) ){//指针行数等于8表明已经摆了8个棋子，找到一个解
               PrintTable(table);
                count++;
               printf("Num:%d\n\n",count);
                Pop_Sq(&S,&CurPos);
                RemoveChess(table,CurPos.i,CurPos.j);
                while( CurPos.j>=(col-1)&&!StackEmpty_Sq(&S) ){
                    Pop_Sq(&S,&CurPos);
                    RemoveChess(table,CurPos.i,CurPos.j);
                }
                CurPos.j++;
            }

        }
        else{
            while( CurPos.j>=(col-1)&&!StackEmpty_Sq(&S) ){
                Pop_Sq(&S,&CurPos);
                if(CurPos.i>=0) RemoveChess(table,CurPos.i,CurPos.j);//不要去删除根节点位置的棋子

//                PrintTable(table);
//                printf("Num:%d\n\n",count);//调试代码

            }
            CurPos.j++;
        }

    }while(!StackEmpty_Sq(&S));
    printf("Total result is %d!",count);

    return 0;
}


Status InitTable(ChessTable table){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            table[i][j]=0;
        }
    }
    return OK;
}

Status PrintTable(ChessTable table){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf(" %d",table[i][j]);
        }
        printf("\n");
    }
    return OK;
}

Status NotDanger(ChessTable table,int i,int j){
    int x,y;
    for(x=0;x<col;x++){
        if(table[i][x]>0) return FALSE;//说明第i行已经摆了棋子
    }

    for(y=0;y<row;y++){
        if(table[y][j]>0) return FALSE;//说明第j列已经摆了棋子
    }

    x=j-1;y=i-1;
    while(x>=0&&y>=0){
        if(table[y][x]>0) return FALSE;//左上方摆了棋子
        else {
            x--;y--;
        }
    }

    x=j+1;y=i+1;
    while(x<col&&y<row){
        if(table[y][x]>0) return FALSE;//右下方摆了棋子
        else {
            x++;y++;
        }
    }

    x=j+1;y=i-1;
    while(x<col&&y>=0){
        if(table[y][x]>0) return FALSE;//右上方摆了棋子
        else {
            x++;y--;
        }
    }

    x=j-1;y=i+1;
    while(x>=0&&y<row){
        if(table[y][x]>0) return FALSE;//左下方摆了棋子
        else {
            x--;y++;
        }
    }
    return TRUE;
}

Status PutChess(ChessTable table,int i,int j){
    if(i<0||i>row||j<0||j>col) {
        printf("PutChess:Error,the coordinate is out!\n");
        return ERROR;
    }else{
        table[i][j]=1;
        return OK;
    }
}

Status RemoveChess(ChessTable table,int i,int j){
    if( (i<0)||(i>row-1)||(j<0)||(j>col-1)) {
        printf("RemoveChess:Error,the coordinate is out!\n");
        return ERROR;
    }else{
        table[i][j]=0;
        return OK;
    }
}

