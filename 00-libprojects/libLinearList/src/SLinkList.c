//静态链表需要自己实现malloc和free函数
//S[0].cur为备用链表第一个元素。S[MAXSIZE-1].cur为第一个结点的下标，为0时表示这是个空表。
//S[0]和S[MAXSIZE]有特殊用途。前者是备用链表头结点，后者是已用链表的头结点


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinearList.h"

void InitSpace_SL(SLinkList SL){
    for (int i=0;i<MAXSIZE-1;i++){
        SL[i].cur=i+1;
    }
    SL[MAXSIZE-1].cur=0;
}

int Malloc_SL(SLinkList SL){//若备用链表非空，则返回分配结点的下标，否则返回0
    int i = SL[0].cur;
    if(i) {
        SL[0].cur = SL[i].cur;
        return i;
    }else return 0;

}

void Free_SL(SLinkList SL,int k){//将下标为k的结点回收到备用链表
    SL[k].cur = SL[0].cur;
    SL[0].cur = k;
}

int LocatePOS_SL(SLinkList SL,int i){//找到链表第i个元素的下标
    if( i<1||i>(MAXSIZE-1) ) return 0;
    int k = MAXSIZE-1;//将k初始化为已用链表的头结点的下标。
    for(int j=1;j<=i;j++){
        if(0==k) break;
        k=SL[k].cur;
    }
    return k;
}

//在静态链表SL中查找第一个值为e的元素，若找到，返回它在L中的位序，否则返回0
int LocateElem_SL(SLinkList SL,ElemType e){
    int i = SL[MAXSIZE-1].cur;
    while(i){
        if(SL[i].data == e) break;
        else i=SL[i].cur;
    }
    return i;
}

//回收第i个结点，并将其值赋给e.当第i个结点不存在时，返回ERROR。
Status ListDelete_SL(SLinkList SL,int i,ElemType *e){
    int j= LocatePOS_SL(SL,i-1);//用做静态链表指针
    if (!j) return ERROR;
    int k= SL[j].cur;
    if ( k ){
        *e=SL[k].data;
        SL[j].cur = SL[k].cur;
        Free_SL(SL,k);
        return OK;
    }else return ERROR;
}

Status ListInsert_SL(SLinkList SL,int i,ElemType e){
    int j= LocatePOS_SL(SL,i-1);//找到第i-1个元素的下标
    if (!j) return ERROR;
    int k = Malloc_SL(SL);
    if (!k) return ERROR;
    SL[k].data = e;
    SL[k].cur=SL[j].cur;
    SL[j].cur = k;
    return OK;
}


int GetLast_SL(SLinkList SL){
    int tail = MAXSIZE-1;
    int tail_next = SL[tail].cur;
    while(tail_next){
        tail=tail_next;
        tail_next=SL[tail_next].cur;
    }//执行完毕后，tail指向静态链表最后一个元素
    return tail;

}

Status ListInput_SL(const char *format,SLinkList SL){
    if (0 == SL[0].cur) {
        printf("The SLinkList is full!\n");
        return ERROR;
    }
    int tail = GetLast_SL(SL);
    char ch = 0;//用ch来接收输入流缓冲区的非数值字符
    int temp = sizeof(ElemType);
    int NewIndex=0;
    ElemType NewData;
    if (1==temp){
        printf("请输入静态链表的字符，按回车结束输入。\n");
        while(1){
            scanf(format,&ch);
            if(ch=='\n') break;
            else {
                NewIndex= Malloc_SL(SL);
                if(!NewIndex) {
                    printf("The SLinkList is full\n");
                    return ERROR;
                }
                SL[NewIndex].data= ch;
                SL[NewIndex].cur=0;
                SL[tail].cur= NewIndex;
                tail=NewIndex;
            }
        }
        printf("CharType data received\n");
    }else{
        printf("请输入静态链表的数值，数值之间用空格隔开，按回车结束输入。\n");
        do{
            scanf("%*[ ]");
            if( (scanf("%1[\n]",&ch)) ) break;//这两行是清空空格，检查回车，防止输入光标停滞，也可实现直接按回车不输入任何数据的作用。
            NewIndex=Malloc_SL(SL);
            if(!NewIndex) {
                printf("The SLinkList is full\n");
                return ERROR;
            }
            if ( scanf(format,&NewData) ) {
                SL[NewIndex].data=NewData;
                SL[NewIndex].cur=0;
                SL[tail].cur=NewIndex;
                tail=NewIndex;
            }else break;
            ch=getchar();
            if(ch=='\n') break;

        }while( ch==' ' );
        if((ch!=10)) {scanf("%*[^\n]");scanf("%*c");}
        printf("NumType data received\n");
    }
    return OK;
}

Status ListPrint_SL(const char *format,SLinkList SL){
    if(0==SL[MAXSIZE-1].cur){
        printf("ListPrint_SL:SLinkList is empty!\n");
        return ERROR;
    }

    int i=SL[MAXSIZE-1].cur;//初始化i为静态链表的第一个结点的下标
    int count= 0;
    while(i){
        printf(format,SL[i].data);
        i=SL[i].cur;
        count++;
    }
    printf("Lenth:%d\n",count);
    return OK;
}

















