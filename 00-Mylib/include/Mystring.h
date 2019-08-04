#ifndef MY_STRING_H_INCLUDED
#define MY_STRING_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSTRLEN 255

typedef int Static;

typedef unsigned char SString[MAXSTRLEN+1];//必须使用unsigned char型变量，不然0号元素取值范围为-128~127，取不到255

typedef struct {
    char *ch;
    int length;
}HString;


Static StrAssign_S(SString *T,const char *chars);

Static StrCopy_S(SString *T,SString S);

Static StrEmpty_S(SString S);

Static StrCompare_S(SString S,SString T);

int StrLength_S(SString S);

Static ClearString_S(SString *S);

Static Concat_S(SString *T,SString S1,SString S2);

Static SubString(SString *Sub,SString S,int pos,int len);

int Index_S(SString S,SString T,int pos);

int Replace_S(SString *S,SString T,SString V);

Static StrInsert_S(SString *S,int pos,SString V);

Static StrDelete_S(SString *S,int pos,int len);

Static PrintStr_S(SString S);




Static StrAssign_H(HString *T,const char *chars);

Static StrCopy_H(HString *T,HString S);

Static StrEmpty_H(HString S);

Static StrCompare_H(HString S,HString T);

int StrLength_H(HString S);

Static ClearString_H(HString *S);

Static Concat_H(HString *T,HString S1,HString S2);

Static SubString_H(HString *Sub, HString S, int pos, int len); //查找串S中从第pos个位置开始，长度为len的字串，并赋值给Sub串

int Index_H(HString S, HString T, int pos);//在主串S中，查找第一个与T串相等的子串，并返回其第一个字符的位置

int Replace_H(HString *S, HString T, HString V); //用V串替换主串S中所有与T串相等的不重叠的字串，返回替换的个数

Static PrintStr_H(HString S);


#endif // MY_STRING_H_INCLUDED
