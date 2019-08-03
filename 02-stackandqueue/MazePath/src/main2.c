#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"
#include "StackAndQueue.h"

//按照回溯思想进行修改的版本

//typedef char MazeType[10][11];
//
//Status MakeMaze(MazeType maze){
//    int i,j;
//    for(i=0;i<10;i++){
//        for(j=0;j<11;j++){//第11列用来存放回车，便于在notepad中修改
//            scanf("%c",&maze[i][j]);
//        }
//    }
//    return OK;
//}
//
//Status PrintMaze(MazeType maze){
//    int i,j;
//    for(i=0;i<10;i++){
//        for(j=0;j<11;j++){
//            printf(" %c",maze[i][j]);
//        }
//    }
//    printf("\n");
//    return OK;
//}
//
//Status SaveMaze(const char *filename,MazeType maze){
//    FILE *fp=fopen(filename,"w");
//    if(fp==NULL){
//        printf("Failed to open file.\n");
//        exit(0);
//    }
//    fwrite(maze,sizeof(MazeType),1,fp);//fwrite函数向文件中写入数据块，返回成功写入的块数。
//    if(ferror(fp)){
//        printf("Failed to save file.\n");
//        return ERROR;
//    }
//    fclose(fp);
//    return OK;
//}
//
//Status LoadMaze(const char *filename,MazeType maze){
//    FILE *fp=fopen(filename,"r");
//    if(fp==NULL){
//        printf("Failed to open file.\n");
//        exit(0);
//    }
//    fread(maze,sizeof(MazeType),1,fp);//fwrite函数从文件中读出数据块，返回成功读取的块数。
//    if(ferror(fp)){
//        printf("Failed to save file.\n");
//        return ERROR;
//    }
//    fclose(fp);
//    return OK;
//}
//
//
//
//
//Status PosEquel(PosType a,PosType b){
//    if( (a.x==b.x)&&(a.y==b.y) ) return TRUE;
//    else return FALSE;
//}
//
//void FootPrint(MazeType maze,PosType pos){
//    maze[pos.y][pos.x]='0';
//}
//
//Status pass(MazeType maze,PosType pos){
//    if(maze[pos.y][pos.x]==' ') return TRUE;
//    else return FALSE;
//}
//
//
//void MarkMaze(MazeType maze,PosType pos){
//    maze[pos.y][pos.x]='S';
//}
//
//PosType NextPos(PosType CurPos,int di){//
//    PosType nextpos;
//    nextpos.x=CurPos.x;
//    nextpos.y=CurPos.y;
//    if(di==1){
//        nextpos.x++;
//    }
//    if(di==2){
//        nextpos.y++;
//    }
//    if(di==3){
//        nextpos.x--;
//    }if(di==4){
//        nextpos.y--;
//    }
//    return nextpos;
//}
//
//void changemaze(MazeType maze,SqStack *S){//将栈S中存储的路径信息写到迷宫maze数据中去
//    SElemType e;
//    while(!StackEmpty_Sq(S)){
//        Pop_Sq(S,&e);
//        if( (e.di==1)||(e.di==3) ){
//            maze[e.seat.y][e.seat.x]='-';
//        }else if( (e.di==2)||(e.di==4) ){
//            maze[e.seat.y][e.seat.x]='|';
//        }
//    }
//}
//
////若迷宫maze中存在一条从start到end的路径，则将它存储栈中，并返回TRUE。否则返回FALSE
//Status MazePath(MazeType maze,PosType start,PosType end,SqStack *S){
//
//    MazeType temp_maze;//声明一个临时迷宫，用来标记不能通过的地方，可以简化 判断是否可以通过的函数的代码
//    for(int i=0;i<10;i++){//给临时迷宫赋值，在这里出了个小BUG，i的初始值赋了个1，导致temp_maze不能正确复制原maze的值
//        for(int j=0;j<11;j++){
//            temp_maze[i][j]=maze[i][j];
//        }
//    }
//    SElemType e;
//    PosType CurPos;
//    int CurStep;
//    CurPos.x=start.x;  CurPos.y=start.y;
//    CurStep = 0;
//
//    do{
//        if( pass(temp_maze,CurPos) ){
//            FootPrint(temp_maze,CurPos);
//            e.di=1; e.ord=CurStep; e.seat.x=CurPos.x; e.seat.y=CurPos.y;
//            Push_Sq(S,e);
//            if( CurPos.x==end.x && CurPos.y==end.y ) return TRUE;
//            CurPos=NextPos(CurPos,1);//1代表先探索东边
//            CurStep++;
//        }else{
//            if(!StackEmpty_Sq(S)){
//                Pop_Sq(S,&e);
//                while(e.di==4&&!StackEmpty_Sq(S)){
//                    MarkMaze(temp_maze,e.seat);
//                    Pop_Sq(S,&e);
//                }
//                if(e.di<4){
//                    e.di++;
//                    Push_Sq(S,e);
//                    CurPos=NextPos(e.seat,e.di);
//                }
//            }
//        }
//    }while(!StackEmpty_Sq(S));
//    return FALSE;
//}
//
//
//int main(){
//    MazeType maze;
//
//    LoadMaze("MazeData/maze3.txt",maze);
//    PrintMaze(maze);
//    SqStack S;
//    InitStack_Sq(&S);
//    PosType start,end;
//    start.x=1;start.y=1;
//    end.x=8;end.y=8;
//    MazePath(maze,start,end,&S);
//    changemaze(maze,&S);
//    PrintMaze(maze);
//
//
//
//    return 0;
//}
