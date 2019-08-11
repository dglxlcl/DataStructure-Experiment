#ifndef MY_STRING_H_INCLUDED
#define MY_STRING_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSTRLEN 255

typedef int Status;

typedef unsigned char SString[MAXSTRLEN+1];//必须使用unsigned char型变量，不然0号元素取值范围为-128~127，取不到255

typedef struct {
    char *ch;
    int length;
}HString;


Status StrAssign_S(SString *T,const char *chars);

Status StrCopy_S(SString *T,SString S);

Status StrEmpty_S(SString S);

Status StrCompare_S(SString S,SString T);

int StrLength_S(SString S);

Status ClearString_S(SString *S);

Status Concat_S(SString *T,SString S1,SString S2);

Status SubString(SString *Sub,SString S,int pos,int len);

int Index_S(SString S,SString T,int pos);

int Replace_S(SString *S,SString T,SString V);

Status StrInsert_S(SString *S,int pos,SString V);

Status StrDelete_S(SString *S,int pos,int len);

Status PrintStr_S(SString S);




Status StrAssign_H(HString *T,const char *chars);

Status StrCopy_H(HString *T,HString S);

Status StrEmpty_H(HString S);

Status StrCompare_H(HString S,HString T);

int StrLength_H(HString S);

Status ClearString_H(HString *S);

Status Concat_H(HString *T,HString S1,HString S2);

Status SubString_H(HString *Sub, HString S, int pos, int len); //查找串S中从第pos个位置开始，长度为len的字串，并赋值给Sub串

int Index_H(HString S, HString T, int pos);//在主串S中，查找第一个与T串相等的子串，并返回其第一个字符的位置

int Replace_H(HString *S, HString T, HString V); //用V串替换主串S中所有与T串相等的不重叠的字串，返回替换的个数

Status StrInsert_H(HString *S, int pos, HString V); //在第POS个位置之前插入串V

Status StrDelete_H(HString *S,int pos,int len);//在串S中删除第pos个字符起长度为len的字串

Status PrintStr_H(HString S);


#endif // MY_STRING_H_INCLUDED
