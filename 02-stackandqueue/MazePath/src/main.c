//#include <stdio.h>
//#include <stdlib.h>
//#include "LinearList.h"
//#include "StackAndQueue.h"
//
//typedef char MazeType[10][11];
//
//Status MakeMaze(MazeType maze){
//    int i,j;
//    for(i=0;i<10;i++){
//        for(j=0;j<11;j++){
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
//Status comparePath(SElemType a,SElemType b){
//    if( (a.seat.x==b.seat.x)&&(a.seat.y==b.seat.y) ) return TRUE;
//    else return FALSE;
//}
//
//void FootPrint(MazeType maze,SElemType path){
//    maze[path.seat.y][path.seat.x]='0';
//}
//
//int pass(MazeType maze,SElemType path){
//    if( (maze[path.seat.y][path.seat.x+1]!='*')&&(maze[path.seat.y][path.seat.x+1]!='0') ) return 1;
//    if( (maze[path.seat.y+1][path.seat.x]!='*')&&(maze[path.seat.y+1][path.seat.x]!='0') ) return 2;
//    if( (maze[path.seat.y][path.seat.x-1]!='*')&&(maze[path.seat.y][path.seat.x-1]!='0') ) return 3;
//    if( (maze[path.seat.y-1][path.seat.x]!='*')&&(maze[path.seat.y-1][path.seat.x]!='0') ) return 4;
//    return 0;
//}
//
//
//void MarkMaze(MazeType maze,SElemType path){
//    maze[path.seat.y][path.seat.x]='*';
//}
//
//Status nextpath(SElemType *path,int di){//写代码时这里出了问题，函数本来要改变元素的值，但定义函数时直接传变量，导致改写没有作用在实参上。
//    if(di==1){
//        path->seat.x++;
//        return OK;
//    }
//    if(di==2){
//        path->seat.y++;
//        return OK;
//    }
//    if(di==3){
//        path->seat.x--;
//        return OK;
//    }if(di==4){
//        path->seat.y--;
//        return OK;
//    }
//    return ERROR;
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
//
//    int nextdi = 0;
//    SElemType curpath;
//    curpath.di=1;  curpath.ord=1;  curpath.seat.x=start.x;  curpath.seat.y=start.y;   //初始化第一个路径数据
//    do{
//        if( (curpath.seat.x==end.x)&&(curpath.seat.y==end.y) ) {
//            Push_Sq(S,curpath);
//            printf("Succesed to end!\n");
//            return TRUE;
//        }else{//不是终点
//            nextdi=pass(temp_maze,curpath);
//            if( nextdi!=0 ){//判断是否可以通行
//                curpath.di=nextdi;
//                FootPrint(temp_maze,curpath);
//                Push_Sq(S,curpath);
//                curpath.ord++;
//                nextpath(&curpath,nextdi);
//
//            }else{//不能通行的情况
//                if(StackEmpty_Sq(S)) {//如果不能通行，而且迷宫为空，则返回错误。
//                    printf("Can't find to end.\n");
//                    return FALSE;
//                }else{
//                    MarkMaze(temp_maze,curpath);
//                    Pop_Sq(S,&curpath);
//                }
//            }
//
//        }
//    }while(1);
//
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
////    SElemType path;
////    path.di=1;path.ord=1;path.seat.x=1;path.seat.y=1;
////    FootPrint(maze,path);
////    PrintMaze(maze);
////    path.seat.x++;
////    int t_di = pass(maze,path);
////    printf("%d",t_di);
//
//    return 0;
//}
