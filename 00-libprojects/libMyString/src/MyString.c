#include <stdio.h>
#include <stdlib.h>
#include "MyString.h"
#include "StackAndQueue.h"

Status StrAssign_S(SString *T,const char *chars){//将串常量chars赋值给串T
    if(!T) return ERROR;
    char *t=(char *)(T);
    int i=1;
    while(i<256&& chars[i-1]!=0 ){
        t[i]=chars[i-1];
        i++;
    }
    t[0]=i-1;
    return OK;
}

Status StrCopy_S(SString *T,SString S){//将串S的值赋值给串T
    if(!T||!S) return ERROR;
    char *t=(char*)(T);
    char *s=(char*)(S);
    for(int i=0;i<=S[0];i++){
        t[i]=s[i];
    }
    return OK;
}

Status StrEmpty_S(SString S){//若S是空串，返回true；若S非空，则返回false
    if(S[0]==0) return TRUE;
    else return FALSE;
}

Status StrCompare_S(SString S,SString T){//若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0；
    int length=(S[0]>T[0])?S[0]:T[0];
    for(int i=1;i<=length;i++){
        if(S[i]==T[i]) continue;
        else if(S[i]<T[i]) return -1;
        else if(S[i]>T[i]) return 1;
    }
    return 0;
}

int StrLength_S(SString S){//返回串S的长度
    return S[0];
}

Status ClearString_S(SString *S){//将串S变成空串
    (*S)[0]=0;
    return OK;
}

Status Concat_S(SString *T,SString S1,SString S2){//连接串S1和S2，赋值给串T
    if(!S1||!S2) return ERROR;
    char *t=(char*)(T);//此处必须进行这个转换，不然t的偏移量会以MAXSTRLEN为步长
    if(S1[0]+S2[0]<=MAXSTRLEN){//S1长度+S2长度<MAXSTRLEN的情况
        for(int i=1;i<=S1[0];i++){
            t[i]=S1[i];
        }
        for(int i=S1[0]+1,j=1;j<=S2[0];i++,j++){
            t[i]=S2[j];
        }
        t[0]=S1[0]+S2[0];
    }else if(S1[0]<MAXSTRLEN){//S1长度+S2长度>MAXSTRLEN,但S1长度小于MAX的情况
        for(int i=1;i<=S1[0];i++){
            t[i]=S1[i];
        }
        for(int i=S1[0]+1,j=1;i<=MAXSTRLEN;i++,j++){
            t[i]=S2[j];
        }
        t[0]=(unsigned char)MAXSTRLEN;
    }else{//S1长度+S2长度>MAXSTRLEN，S1长度=MAX的情况
        for(int i=1;i<=MAXSTRLEN;i++){
            *(t+i)=S1[i];
        }
        t[0]=(unsigned char)MAXSTRLEN;
    }
    return OK;
}

Status SubString_S(SString *Sub,SString S,int pos,int len){//查找串S中从第pos个位置开始，长度为len的字串，并赋值给Sub串
    if( !S || pos<1 || pos>S[0] || len<0 || len>S[0]-pos+1 ) return ERROR;
    char *pSub = (char*)(Sub);
    int i,j;
    for(i=1,j=pos;j<pos+len;i++,j++){
        pSub[i]=S[j];
    }
    pSub[0]=(unsigned char)(len);//将len赋值给sub字串长度
    return OK;
}

int Index_S(SString S,SString T,int pos){
//穷举算法
//    if(!S || !T || T[0]==0 || pos<1 || pos>S[0]) return INFEASIBLE;
//    int i,j;
//    for(i=pos;i<=S[0]-T[0]+1;i++){
//        for(j=0;j<T[0];j++){
//            if(S[i+j]==T[j+1]) continue;
//            else break;
//        }
//        if(j==T[0]) return i;
//    }
//    return 0;

//改进的穷举算法
//    if(!S || !T || T[0]==0 || pos<1 || pos>S[0]) return ERROR;
//    int i=pos,j=1;
//    while(i<=S[0]&&j<=T[0]){
//        if(S[i]==T[j]){//若相等，继续比较下一个字符
//            i++;
//            j++;
//        }else{
//            i=i-j+2;//指针后退重新比较
//            j=1;
//        }
//    }
//    if(j>T[0]) return i-T[0];
//    else return 0;

//kmp算法
//第一步：求kmp数组
//    int next[T[0]+1];//这个next数组为了方便识别下标，数据从下标1开始。下标0的数据无效。
//    int i=1,j=0;
//    next[1]=0;
//    while(i<T[0]){
//        if(0==j||T[i]==T[j]){
//            i++;
//            j++;
//            next[i]=j;
//        }else j=next[j];
//    }
//（还是第一步）next数组改进型
    int next[T[0]+1];
    int i=1,j=0;
    next[1]=0;//模式串第1个字符的next值默认是前一个下标值。
    while(i<T[0]){//当i=T[0]时，已经在循环体内得到next值了。
        if(0==j||T[i]==T[j]){//如果主串第i个字符等于模式串第j个字符
            i++;
            j++;
            if(T[i]==T[j]) next[i]=next[j];//next数组改进的关键：本来若i+1位置上若S[i+1]!=T[i+1]失配，应该和next[i+1]=j+1再次比较(因为T[i]=T[j])，而这里因为T[i+1]=T[j+1],所以S[i+1]不可能和T[j+1]相等，只需要和next[j+1]比较，所以next[i+1]=next[j+1]
            else next[i]=j;
        }else j=next[j];
    }

    i=pos;j=1;//第二步，根据next数组查找子串T；
    while(i<=S[0]&&j<=T[0]){
        if(0==j||S[i]==T[j]){//匹配成功时，或j已经回溯到next[1]=0
            i++;
            j++;
        }else j=next[j];
    }
    if (j>T[0]) return i-T[0];
    else return 0;

}

int Replace_S(SString *S,SString T,SString V){//用V串替换主串S中所有与T串相等的不重叠的字串，返回替换的个数

// //第一个算法思路：每次在S串中找到一个T串，立刻将S串后面的字符调整相应位置，空出空间用V串替换T串。此方法找到几个T串就要对S串整体调整几次，效率低
//     if(!*S || !T || !V) return ERROR;
//     if(T[0]==0) return 0;
//     int count=0,pos=1,nextpos=1;//用count记录替换的个数，pos存储当前开始查找字串T的位置，nextpos存储下一个查找的位置，当nextpos=0（没有找到）时结束函数运行，返回count值。
//     unsigned char i=0,j=0;//用i作为主串S的指针，用j作为v串的指针
//     int length_temp;//此处必须定义一个整型变量存储长度，不然在计算length_temp>MAXSTRLEN时，会因为数据溢出而永远不执行这个判断内的代码
//     unsigned char *pStr = (unsigned char*)(S);
//     while( (nextpos=Index_S(*S,T,pos)) ){
//         if(T[0]==V[0]){//被替换串T长度等于替换串V的情况。
//             for(int i=nextpos,j=1;j<=V[0];i++,j++){
//                pStr[i]=V[j];
//             }
//         }else if(T[0]<V[0]){//被替换串长度小于替换串长度的情况
//             int dif = V[0]-T[0];//用dif变量存储V串比T串多多少。
//             length_temp=pStr[0]+dif;//S串的长度+差额dif后，赋值给length_temp
//             if( length_temp>MAXSTRLEN ) {//如果替换后，长度超过最大长度,输出错误信息，并终止函数。
//                 printf("Replace_S：The string is overflew!\n");
//                 return count;
//             }
//             for(i=pStr[0];i>=nextpos+T[0];i--){//将元素依次后移，挪出位置给V[0]
//                 pStr[i+dif]=pStr[i];
//             }
//             for(i=nextpos,j=1;j<=V[0];i++,j++){//将原来T串替换为V串
//                 pStr[i]=V[j];
//             }
//             pStr[0]+=dif;//S串长度增加
//         }else {//T[0]>V[0]的情况，即被替换串长度大于替换串长度的情况
//             int dif = T[0]-V[0];
//             for(i=nextpos,j=1;j<=V[0];i++,j++){//将原来T串替换为V串
//                 pStr[i]=V[j];
//             }
//             for(i=nextpos+V[0];i<=pStr[0]-dif;i++){//串元素依次前移
//                 pStr[i]=pStr[i+dif];
//             }
//             pStr[0]-=dif;
//         }
//         count++;
//         pos=nextpos+V[0];//继续查找下一个T串
//     }
//     return count;

//第二个思路：在函数内新建一个SString。利用index（kmp算法）函数在S串中查找T串，找到一个，就将返回位置前面的所有字符读入new串，然后读入V串，接着查找下一个。
    if(!*S || !T || !V) return ERROR;
    if(T[0]==0) return 0;
    SString New;
    New[0] = 0;//初始化new串长度为0
    int count = 0;//存放替换的T串个数
    int TmpPos=1;//临时存放在S串中找到的T串的位置
    int p_New, p_S,p_V;//p_New用于向new串写数据，pc_S用于S主串的查找匹配，pw_S用于从S主串读数据（拷至new串），pT是T模式串的指针，pV是V串的指针（用于读V串数据拷贝至new串）
    p_New = p_S = p_V = 1;
    while( p_S<=(*S)[0]&& (TmpPos=Index_S(*S, T, p_S)) ){
        while(p_S<TmpPos){
            New[p_New] = (*S)[p_S];
            p_New++;
            p_S++;
            New[0]++;
        }
        p_V = 1;
        while(p_V<=V[0]&&((p_New+V[0])<=MAXSTRLEN+1)){
            New[p_New] = V[p_V];
            p_New++;
            p_V++;
            New[0]++;
        }
        if(p_V==V[0]+1)
            count++;
        p_S += T[0];
    }
    while(p_S<=(*S)[0]){
        New[p_New] = (*S)[p_S];
        p_New++;
        p_S++;
        New[0]++;
    }
    for (int i = 0; i <= New[0];i++){
        (*S)[i] = New[i];
    }
    return count;
}

Status StrInsert_S(SString *S,int pos,SString V){//在第POS个位置之前插入串V
    if(!S || !V || pos<1 || pos > (*S)[0]+1 ) return ERROR;
    unsigned char *pStr = (unsigned char*)(S);
    int length_temp = pStr[0]+V[0];//因为*pstr是char型变量，存不下比Maxlength更大的数，所以此处必须用length_temp临时存储一下长度
    if(length_temp>MAXSTRLEN) {
        printf("StrInsert_S:Error!,The string is up to MaxLength!\n");
        return ERROR;
    }
    for(int i=pStr[0];i>=pos;i--){//从最后一个字符开始，依次往后挪V[0]个位置
        pStr[i+V[0]]=pStr[i];
    }
    for(int i = pos,j=1;j<=V[0];i++,j++){
        pStr[i]=V[j];
    }
    pStr[0]+=V[0];
    return OK;
}

Status StrDelete_S(SString *S,int pos,int len){//在串S中删除第pos个字符起长度为len的字串
    if(!S || pos <1 || pos>(*S)[0]-len+1 || len<0) {
        printf("StrDelete_S:Error,Argument Error!\n");
        return ERROR;
    }
    int i;
    unsigned char *pStr = (unsigned char*)(S);
    for(i=pos;i<=(*S)[0]-len;i++){
        pStr[i]=pStr[i+len];
    }
    pStr[0]-=len;
    return OK;
}

Status PrintStr_S(SString S){
    if(!S) return ERROR;
    fwrite(&S[1],1,S[0],stdout);//fwrite:将&S[1]起，以1个字节为单位，共S[0]个单位，拷贝到stdout标准输出文件。这里不用printf，主要是因为%s格式控制符需要找0/的字符串结束标志。
    return OK;
}





Status StrAssign_H(HString *T,const char *chars){
    if( T->ch ) free(T->ch);//每次给堆分配串赋值前，都重新分配一下空间。
    int i=0;
    const char *c=chars;
    while(*c){//这里是为了获取chars的长度
        i++;
        c++;
    }
    if(0==i) {
        T->ch=NULL;
        T->length=0;
    }else{
        T->ch=(char *)malloc(i*sizeof(char));
        if( !(T->ch) ) return OVERFLOW;
        T->length=i;
        i=0;c=chars;//将指针c重新指回chars的位置
        while(*c){
            T->ch[i]=*c;
            i++;
            c++;
        }
    }
    return OK;
}

Status StrCopy_H(HString *T,HString S){
    if(T->ch) free(T->ch);
    int i=0;
    char *c = S.ch;
    if(S.length==0){
        T->ch=NULL;
        T->length=0;
    }else{
        T->ch=(char*)malloc(S.length*sizeof(char));
        if(!(T->ch)) return OVERFLOW;
        T->length=S.length;
        while(*c){
            T->ch[i]=*c;
            i++;
            c++;
        }
    }
    return OK;
}

Status StrEmpty_H(HString S){
    if(!(S.ch)) return INFEASIBLE;
    if(S.length==0) return TRUE;
    else return FALSE;
}

Status StrCompare_H(HString S,HString T){
//    if ( !(S.ch) ||!(T.ch) ) return OVERFLOW;
//    int i=0,j=0;
//    while(i<S.length&&j<T.length){
//        if(S.ch[i]<T.ch[j]) return -1;
//        else if(S.ch[i]>T.ch[j]) return 1;
//        else{
//            i++;
//            j++;
//        }
//    }
//    if(i<S.length) return 1;
//    else if(j<T.length) return -1;
//    else return 0;
    int i;
    for(i=0;i<S.length&&i<T.length;i++){
        if(S.ch[i]!=T.ch[i]) return S.ch[i]-T.ch[i];
    }
    return S.length-T.length;
}

int StrLength_H(HString S){
    return S.length;
}

Status ClearString_H(HString *S){
    if(S->ch){
        free(S->ch);
        S->ch=NULL;
    }
    S->length=0;
    return OK;
}

Status Concat_H(HString *T,HString S1,HString S2){
    if(T->ch) free(T->ch);
    T->ch=(char *)malloc( (S1.length+S2.length)*sizeof(char) );
    if( !(T->ch) ) exit(OVERFLOW);
    int i=0,j=0;
    while(i<S1.length){
        T->ch[i]=S1.ch[i];
        i++;
    }
    while(j<S2.length){
        T->ch[i]=S2.ch[j];
        i++;j++;
    }
    T->length=S1.length+S2.length;
    return OK;
}

Status SubString_H(HString *Sub,HString S,int pos,int len){//查找串S中从第pos个位置开始，长度为len的字串，并赋值给Sub串
    if(pos<1 || pos>S.length || len<0 || len>S.length-pos+1 ){
        printf("SubString_H:The Argument is illegal.\n");
        return ERROR;
    }
    if(Sub->ch) free(Sub->ch);
    if(len==0){
        Sub->ch = NULL;
        Sub->length = 0;
    }else{
        Sub->ch = (char *)malloc(len * sizeof(char));
        for (int i = 0; i < len;i++){
            Sub->ch[i] = S.ch[pos + i-1];
        }
        Sub->length = len;
    }
    return OK;
}

int Index_H(HString S,HString T,int pos){//在主串S中，查找第一个与T串相等的子串，并返回其第一个字符的位置
    if( pos<1 || pos>S.length ){
        printf("Index_H:The Argument is illegal.\n");
        return ERROR;
    }
        
//第一步先求next数组
    int next[T.length];
    next[0] = -1;
    int i = 0, j = -1;
    while(i<T.length-1){
        if(j==-1||T.ch[i]==T.ch[j]){
            i++;
            j++;
            if(T.ch[i]==T.ch[j])
                next[i] = next[j];
            else next[i] = j;
        }else
            j = next[j];
    }
    i = pos-1;j = 0;
    while(i<S.length&&j<T.length){
        if(j==-1||S.ch[i]==T.ch[j]){
            i++;
            j++;
        }else
            j = next[j];
    }
    if(j>=T.length)
        return i - T.length + 1 ;
    else
        return 0;
}

int Replace_H(HString *S,HString T,HString V){//用V串替换主串S中所有与T串相等的不重叠的字串，返回替换的个数
    int count = 0;                //存储主串S中T字串的个数
    int dif = T.length - V.length;//用dif存储T串和V串的长度差
    QElemType TmpPos =1;                   //用TmpPos临时存储在主串S中每一次找到的T串的位置
    LinkQueue POS;
    POS.head = NULL;
    InitQueue_L(&POS);
    while( (TmpPos=Index_H(*S, T, TmpPos)) ){//用一个队列保存每一次找到的T串的位置
        EnQueue_L(&POS, TmpPos);
        TmpPos += T.length;
        if(TmpPos>S->length)
            break;
    }
    count = POS.length;
    char *NewStr = (char *)malloc((S->length - count * dif) * sizeof(char));
    int pS = 1;//指向主串S的指针
    int pV = 1;//替换串V的指针
    int pNew = 1;//新串的指针
    while( (!QueueEmpty_L(POS)) ){//当POS队列不空时，也就是说还没有替换完毕时
        DeQueue_L(&POS, &TmpPos);
        while(pS<TmpPos){//先将替换位置前的字符拷贝至新串，拷贝完毕后，pS指向需要替换的位置
            NewStr[pNew - 1] = S->ch[pS-1];
            pNew++;
            pS++;
        }
        pV = 1;
        while(pV<=V.length){//将替换内容写入新串
            NewStr[pNew - 1] = V.ch[pV-1];
            pNew++;
            pV++;
        }
        pS += T.length;//写完后，要将指向主串S的指针向后跳T.length个位置
    }
    while(pS<=S->length){//全部替换完成后，还要将剩下的字符写入新串
        NewStr[pNew - 1] = S->ch[pS-1];
        pNew++;
        pS++;        
    }
    S->length -= count * dif;
    free(S->ch);
    S->ch = NewStr;
    return count;
}

Status StrInsert_H(HString *S, int pos, HString V) { //在第POS个位置之前插入串V
    if(!(S->ch)||!V.ch) return ERROR;
    if(pos<1||pos>S->length+1) return ERROR;
    char *NewCh = (char*)malloc((S->length+V.length)*sizeof(char));
    int p_S,p_V,p_New;//i用作
    p_S=p_V=p_New=0;
    while(p_S<pos-1){
        NewCh[p_New]=S->ch[p_S];
        p_New++;
        p_S++;
    }
    while(p_V<V.length){
        NewCh[p_New]=V.ch[p_V];
        p_New++;
        p_V++;
    }
    while(p_S<S->length){
        NewCh[p_New]=S->ch[p_S];
        p_S++;
        p_New++;
    }
    free(S->ch);
    S->ch=NewCh;
    S->length+=V.length;
    return OK;
}

Status StrDelete_H(HString *S,int pos,int len){//在串S中删除第pos个字符起长度为len的字串
    if(!(S->ch)) return ERROR;
    if(pos<1||pos+len>S->length+1||len<0) return ERROR;
    char * NewCh= (char*)malloc((S->length-len)*sizeof(char));
    int p_New=0;//新串的指针
    int p_S=0;//指向S串的指针
    while(p_S<pos-1){
        NewCh[p_New]=S->ch[p_S];
        p_New++;
        p_S++;
    }
    p_S+=len;
    while(p_S<S->length){
        NewCh[p_New]=S->ch[p_S];
        p_New++;
        p_S++;
    }
    free(S->ch);
    S->ch=NewCh;
    S->length-=len;
    return OK;
}


Status PrintStr_H(HString S){
    if(!(S.ch)) return ERROR;
    fwrite(S.ch,1,S.length,stdout);
    return OK;
}
