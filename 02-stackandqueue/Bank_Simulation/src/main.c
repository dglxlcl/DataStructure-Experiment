#include <stdio.h>
#include <stdlib.h>
#include "StackAndQueue.h"
#include "LinearList.h"

#define QUEUENUM 4
typedef LinkList_L EventList;

EventList ev;
Event en;
LinkQueue q[QUEUENUM];

int TotalTime,ArrivalCustomerNum,DeCustomerNum;

int cmp(Event a,Event b){
    if(a.OccurTime<b.OccurTime) return -1;
    else if(a.OccurTime==b.OccurTime) return 0;
    else return 1;
}

Status OrderInsert(EventList *ev,Event en,int (*cmp)(Event,Event) ){
    Link temp;
    MakeNode(&temp);
    temp->data=en;

    Link p = ev->head;
    Link q = p->next;
    while(q){
        if( (cmp(q->data,en) ) <=0 ){
            p=q;
            q=q->next;
        }else break;
    }
    temp->next=p->next;
    p->next=temp;
    ev->length++;
    return OK;
}

int MiniLength(LinkQueue Q[QUEUENUM]){
    int minIndex=0;
    int minLength=Q[0].length;//此处第一次写的时候，将minlength赋值为0，错误！！因为0肯定是最小的，所以将永远返回1，得不到正确答案
    for(int i=1;i<QUEUENUM;i++){
        if(Q[i].length < minLength) {
            minLength=Q[i].length;
            minIndex=i;
        }
    }
    return minIndex;
}


void OpenForDay(){
    InitList_L(&ev);//初始化事件链表
    TotalTime=0;ArrivalCustomerNum=0;DeCustomerNum=0;//初始化总逗留事件和总客户数。

    en.OccurTime=rand()%5;en.EventType=0;//将第一个事件加入
    OrderInsert(&ev,en,cmp);
    for( int i=0;i<QUEUENUM;i++){
        InitQueue_L(&q[i]);
    }
}

void CustomerArrived(){
    ArrivalCustomerNum++;
    Event NewArrivalEvent,NewDepartureEvent;
//    int InterTime = rand()%5;
//    int DurTime = 5+rand()%25;
    int InterTime = 10;
    int DurTime = 50;
    //再次增加一个客户到达事件
    NewArrivalEvent.EventType=0;
    NewArrivalEvent.OccurTime = en.OccurTime+InterTime;
    if(NewArrivalEvent.OccurTime<=480){//此处480代表银行关门时间
        OrderInsert(&ev,NewArrivalEvent,cmp);
    }

    //处理客户到达事件，将客户添加到长度最小的队列里
    int i= MiniLength(q);//q是 LinkQueue [QUEUENUM]类型
    QElemType NewCustomer;
    NewCustomer.ArrivalTime=en.OccurTime;
    NewCustomer.Duration=DurTime;
    EnQueue_L(&q[i],NewCustomer);
    printf("  CustomerArrived:Windows:%d,OccurTime:%d,DurTime:%d,NextArriveTime:%d\n",i,en.OccurTime,NewCustomer.Duration,NewArrivalEvent.OccurTime);


    //如果添加的队列是空的，那么新增加一个客户离开事件。
    if( q[i].length == 1){
        NewDepartureEvent.EventType=i+1;
        NewDepartureEvent.OccurTime=en.OccurTime+DurTime;
        OrderInsert(&ev,NewDepartureEvent,cmp);
    }
}

void CustomerDeparture(){
    DeCustomerNum++;
    QElemType Customer,NextCustomer;
    int i = en.EventType-1;
    DeQueue_L(&q[i],&Customer);
    TotalTime += (en.OccurTime-Customer.ArrivalTime);//客户离开时间-客户到达时间得到这个客户的逗留时间，将时间累加至总时间

    Event NewDepartureEvent;
    //如果队列不空，则根据队列中下一个客户的Duration得到另一个离开事件，并将这个离开事件插入到事件链表中
    if( !QueueEmpty_L(q[i]) ){
        GetHead_Lq( &q[i] ,&NextCustomer);//在设计过程中，此处由于GetHead函数写错了，没有考虑头节点（头节点的data不是第一个元素哦）
        NewDepartureEvent.EventType = i+1;
        NewDepartureEvent.OccurTime = en.OccurTime+NextCustomer.Duration;
        OrderInsert(&ev,NewDepartureEvent,cmp);
    }
    printf("CustomerDeparture:Windows:%d,OccurTime:%d,ArriveTime:%d,DurTime:%d,NextDeparture:%d\n",i,en.OccurTime,Customer.ArrivalTime,Customer.Duration,en.OccurTime+NextCustomer.Duration);
}

int main()
{
    OpenForDay();
    while( !ListEmpty_L(&ev)&&en.OccurTime<=480 ){
        DelFirst_L(&ev,&en);
         if (en.EventType==0){
            CustomerArrived();
        }else CustomerDeparture();
    }
    printf("The Total Num of Custormer is %d\n",DeCustomerNum);
    printf("The average time is %f\n",(float)TotalTime/DeCustomerNum);
    return 0;
}


//int main(){
//    Event a,b;
//    a.EventType=b.EventType=0;
//    a.OccurTime=20;
//    b.OccurTime=20;
//    int i = cmp(a,b);
//    printf("i=%d\n",i);
//}


