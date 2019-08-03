#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StackAndQueue.h"

int PrecedeTable[7][7]={ {1,  1, -1, -1, -1,  1,  1},
                         {1,  1, -1, -1, -1,  1,  1},
                         {1,  1,  1,  1, -1,  1,  1},
                         {1,  1,  1,  1, -1,  1,  1},
                        {-1, -1, -1, -1, -1,  0, -2},
                         {1,  1,  1,  1, -2,  1,  1},
                        {-1, -1, -1, -1, -1, -2,  0} };
//format:PrecedeTable[i][j]
//1:i precede j。    -1:j precede i 。  0:i equal j;   -2:illegal
//about data_index:  + - * / ( ) #
//                   0 1 2 3 4 5 6


int Flag_Opnd=0;//上一次读到操作数是，将标志位置1；否则置0；
int Flag_Optr=0;//上一次读到+-*/这四个运算符，将运算符标志位置1.
int Flag_LeftBrace=1;//上一次读到( ,将该标志位置1，默认为1，表示前面压栈的#。
int Flag_RightBrace=0;//上一次读到) ,将该标志位置1，默认为0


int ReadElem(char *str,int *offset,float *num,char *optr);

int Precede(char optrA,char optrB);

SElemType Evaluator(SElemType OpndA,SElemType OpndB,char TopOptr);



//这个程序目前只支持双运算符，单运算符比如-2一类的输入是不接受的。
int main(){
    SqStack OpndStack;
    charSqStack OptrStack;
    InitStack_Sq(&OpndStack);
    InitStack_charSq(&OptrStack);
    Push_charSq(&OptrStack,'#');//在运算符栈底压一个#，简化操作

    char str[101];//用于存放输入的中缀表达式
    int length;
    printf("请输入一个中缀表达式：\n");
    scanf("%[^\n]%n",str,&length);//得到输入的表达式，并用%n控制符输入读取的字符个数到length变量
    str[length]='#';//在得到的中缀表达式后面加上#
    str[length+1]=0;

    float CurOpnd = 0;//存放当前读到的操作数
    char CurOptr = 0;//存放当前读到的运算符
    char TopOptr;
    int str_offset=0;//用于存放每次读取时的字符地址偏移量，初始化值为0；
    int Flag_illegal=0;//flag为0表示读取错误，输入的表达式非法（读到了+-*/()#以外的运算符）。flag为1时表示读到一个操作数;    flag为2时表示读到一个运算符，
    int Flag_precede=-2;//存放优先级判断函数的返回值，-2：优先级出现非法情况。 -1，前者小于后者。  0，两者相同。  1：前者大于后者
    int Flag_end=0;//flag=1时，程序运行结束标记
    SElemType OpndA,OpndB,temp;

    do{
        Flag_illegal=ReadElem(str,&str_offset,&CurOpnd,&CurOptr);
        printf("CurOpnd=%f     ",CurOpnd);printf("CurOptr=%c     \n",CurOptr);
        if(Flag_illegal==0){
            printf("Flag_illigal:expression error!\n");
            Flag_end=1;
            break;
        }else if (Flag_illegal==1){
            Push_Sq(&OpndStack,CurOpnd);
            printf("Opnd:%f is pushed\n",CurOpnd);
            continue;
        }else if (Flag_illegal==2){
            do{
                GetTop_charSq(&OptrStack,&TopOptr);
                Flag_precede=Precede(TopOptr,CurOptr);
                if(Flag_precede==-2){
                    Flag_end=1;
                    printf("Flag_precede==-2:expression error!maybe contain: )( 、#)、(#。\n");
                    break;
                }
                if(Flag_precede==-1){
                    Push_charSq(&OptrStack,CurOptr);//这里因为Flag_precede<0，所以只会执行一次，不需要加break；
                    printf("Optr:%c is pushed\n",CurOptr);
                }else if(Flag_precede==0){
                    Pop_charSq(&OptrStack,&CurOptr);//这里因为Flag_precede==0，所以只会执行一次，不需要加break；
                    printf("brace:%c is erased\n",CurOptr);
                }else {
                    Pop_Sq(&OpndStack,&OpndB);
                    printf("OpndB:%f  ",OpndB);
                    if( StackEmpty_Sq(&OpndStack) ){
                        Flag_end=1;
                        printf("Flag_precede>0:expression error!（The OpndStack is empty!）\n");
                        break;
                    }
                    Pop_Sq(&OpndStack,&OpndA);
                    printf("OpndA:%f  ",OpndA);
                    Pop_charSq(&OptrStack,&TopOptr);
                    printf("OpTR:%c  ",TopOptr);
                    temp=Evaluator(OpndA,OpndB,TopOptr);
                    printf("value:%f",temp); printf("\n");
                    Push_Sq(&OpndStack,temp );
                }
            }while(Flag_precede>0);
        }
    }while( !StackEmpty_charSq(&OptrStack) &&Flag_end==0  );
    if(Flag_end==0){
        Pop_Sq(&OpndStack,&CurOpnd);
        if(StackEmpty_Sq(&OpndStack)) printf("The result is :%f\n",CurOpnd);
        else printf("Expression Error!\n");
    }

    return 0;
}

//参数str存放待读取字符串的地址，参数offset表示待读取字符串
int ReadElem(char *str,int *offset,float *opnd,char *optr){
    int n = 0;//存放读取字符的个数

//一、进行中缀表达式合法性检查或自动补齐

//1.先丢弃前面所有的空格
    sscanf(str+(*offset),"%*[ ]%n",&n);
    (*offset)+=n;
    char *p=str+*(offset);//将p指向下一个即将读取的位置
    printf("p->:%c\n",*p);

//2.检查是否在上一次读到左括号的情况下，此次读到+-，则在前面补操作数0，如果这一次读到*/，则弹出错误信息
    if(Flag_LeftBrace){
        if( *p=='+' || *p=='-' ){
            *opnd=0;
            Flag_Opnd=1;
            Flag_LeftBrace=0;
            Flag_Optr=0;
            Flag_RightBrace=0;
            return 1;
        }else if( *p=='*' || *p=='/' ){
            printf("ReadElem:ERROR!LeftBrace+(*,/)!\n");
            return 0;
        }
    }
//3.检查是否在上一次读到操作数的情况下，这一次读到左括号（，则自动补*
    if(Flag_Opnd&& *p=='(' ){
        *optr='*';
        Flag_Optr=1;
        Flag_LeftBrace=0;
        Flag_Opnd=0;
        Flag_RightBrace=0;
        return 2;
    }
//4.检查是否在上一次读到+-*/的情况下，这一次又读到+-*/
    if(Flag_Optr&& ( *p=='+' || *p=='-' || *p=='*' || *p=='/' )  ){
        printf("ReadElem:ERROR!Successiv read Optr(+-*/)!\n");//如果上次读到运算符，这一次又出现+-*/运算符，则输出错误信息
        return 0;
    }
//5.检查是否在上一次读到）的情况下，这一次读到操作数，非法输入
    if(Flag_RightBrace&& *p>='0' && *p <= '9' ){
        printf("ReadElem:ERROR!RightBrace+Opnd!\n");
        return 0;
    }
//6.排除上述所有情况后，监测下一个将读取的字符串，如果是数字，就尝试读取浮点数
    if( *p>='0' && *p <= '9'){//在这里一定不能直接sscanf,不然会将+号-号连同后面的数字一起被当成浮点数
        sscanf(p,"%f%n",opnd,&n);
        (*offset)+=n;//读取浮点数成功后，及时调整偏移位置
        Flag_Opnd=1;//将flag置1，若下次还读到操作数，就可以返回0（错误）.
        Flag_Optr=0;
        Flag_LeftBrace=0;
        Flag_RightBrace=0;
        return 1;//返回1，表示读到的是操作数
    }else{//如果不是数字，则尝试读一个运算符，读取成功就执行下面的代码
        sscanf(str+(*offset),"%c%n",optr,&n);
        (*offset)+=1;//读取运算符成功后，及时调整偏移位置
        if(*optr=='('){
            Flag_LeftBrace=1;//读到左括号，将左括号标志位置1
            Flag_RightBrace=0;
            Flag_Opnd=0;
            Flag_Optr=0;
            return 2;
        }
        if(*optr==')'){
            Flag_LeftBrace=0;
            Flag_RightBrace=1;//读到右括号，将右括号标志位置1
            Flag_Opnd=0;
            Flag_Optr=0;
            return 2;
        }
        if( (*optr=='+')||(*optr=='-')||(*optr=='*')||(*optr=='/') ){
            Flag_LeftBrace=0;
            Flag_RightBrace=0;
            Flag_Opnd=0;
            Flag_Optr=1;//读到+-*/，将+-*/标志位置1
            return 2;
        }
        if(*optr=='#'){
            return 2;
        }
        else{
            printf("ReadElem:ERROR!Read a illegal charset!\n");
            return 0;
        }
    }
}


int Precede(char optrA,char optrB){
    int i,j;
    switch(optrA){
        case '+':i=0;break;
        case '-':i=1;break;
        case '*':i=2;break;
        case '/':i=3;break;
        case '(':i=4;break;
        case ')':i=5;break;
        case '#':i=6;break;
        default:i=7;break;
    }
    switch(optrB){
        case '+':j=0;break;
        case '-':j=1;break;
        case '*':j=2;break;
        case '/':j=3;break;
        case '(':j=4;break;
        case ')':j=5;break;
        case '#':j=6;break;
        default:j=7;break;
    }
    if(i==7||j==7){
        printf("Precede():occurd a error!\n");
        exit(0);
    }
    return PrecedeTable[i][j];
}

SElemType Evaluator(SElemType OpndA,SElemType OpndB,char TopOptr){
    switch(TopOptr){
        case '+':return OpndA+OpndB;
        case '-':return OpndA-OpndB;
        case '*':return OpndA*OpndB;
        case '/':
            if(OpndB==0){
                printf("The divider can't be zero!\n");
                exit(0);
            }else return OpndA/OpndB;
    }
}