/*
编写这段代码心得：
1.if()，括号里面的布尔表达式要用括号括起来，比如if( (a==b)&&(a==c) )。
2.用非定义的函数操作线性表里的数据时，要考虑线性表各个数据元素的值的相关性，比如用get()给线性表赋值后，要相应的改变线性表的length
3.函数指针的定义形式是：datatype
(*p)(parm1,parm2)，表示这是一个datatype类型的函数的指针，在函数体内引用函数指针的方式是：(*p)(parm1,parm2),在传递参数时直接使用函数名就可以了。
4.指针只能和指针比较，不然会出错。
5.scanf("%d)进行匹配时，会自动忽略并清空输入流缓冲区的空格和回车。%[]将只读取将括号里的字符集，%1[0-9]表示一次只读取0-9中的一个数字，读取完毕后会和%s类似，在指针变量后面自动补0。
6.C语言不支持函数重载，要改变ElemType的数据类型，只有打开库工程，改变ElemType的定义后，Rebuild
*/
#include "LinearList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//由于C语言没有构造函数，为简洁代码，该库没有写相应的构造函数。因此，定义一个顺序表后，一定要立刻将其指针成员初始化为0，以下所有操作默认调用者已经初始化顺序表

//构造一个空的顺序表，长度初始化为0，分配LISE_INIT_SIZE长度的空间给*elem，返回OK（1），若分配失败，返回ERROR（0）
Status InitList_Sq(Sqlist *L) {
  if (L->elem) {
    printf("InitList_Sq:SequenceList is already initialized!\n");
    return ERROR;
  }
  L->elem = (ElemType *)malloc(
      LIST_INIT_SIZE *
      sizeof(
          ElemType)); //申请初始大小为LIST_INIT_SIZE（100）的空间，空间首地址赋值给顺序表的elem数据项
  if (!L->elem) {
    printf("InitList_Sq:Fail to requst memmory!Procesee is terminated!\n");
    exit(OVERFLOW);
  }
  L->length = 0;                //顺序表长度赋值为0
  L->listsize = LIST_INIT_SIZE; //顺序表大小赋值为初始大小
  return OK;
}

//扩展顺序表的空间大小，增量是LISTINCREMENT
Status IncListSize_Sq(Sqlist *L) {
  if (!L->elem) {
    printf("IncListSize_Sq:SequenceList is not initialized!\n");
    return ERROR;
  }
  ElemType *newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
  if (!newbase) {
    printf("IncListSize_Sq:Fail to requst memmory!Procesee is terminated!\n");
    exit(OVERFLOW);
  }
  L->elem = newbase;
  L->listsize += LISTINCREMENT;
  return OK;
}

//销毁一个顺序表，释放这个顺序表的占用空间，同时将长度和容量都置0
Status DestroyList_Sq(Sqlist *L) {
  if (!L->elem) {
    printf("DestroyList_Sq:SequenceList is not initialized!\n");
    return ERROR;
  }
  free(L->elem);
  L->elem = NULL;
  L->length = 0;
  L->listsize = 0;
  return OK;
}

//将顺序表清空为空表，长度为0
Status ClearList_Sq(Sqlist *L) {
  if (!L->elem) {
    printf("ClearList_Sq:SequenceList is not initialized!\n");
    return ERROR;
  }
  L->length = 0;
  return OK;
}

//当L为空表时，返回TURE，否则返回FALSE。
Status ListEmpty_Sq(Sqlist L) {
  if (!L.elem) {
    printf("ListEmpty_Sq:Warning:SequenceList is not initialized!\n");
    return ERROR;
  }
  if (L.length == 0)
    return TRUE;
  else
    return FALSE;
}

//返回顺序表L的长度。
int ListLength_Sq(Sqlist L) {
  if (!L.elem) {
    printf("ListLength_Sq:Warning:SequenceList is not initialized!\n");
    return ERROR;
  }
  return L.length;
}

//获取顺序表L的第i个元素，将其赋值给e。当i的取值非法时，返回ERROR
Status GetElem_Sq(Sqlist L, int i, ElemType *e) {
  if (!L.elem) {
    printf("GetElem_Sq:Warning:SequenceList is not initialized!\n");
    return ERROR;
  }
  if ((i >= 1) && (i <= L.length)) { //判断i的取值是否在[1,length]之间
    *e = *(L.elem + i - 1);          //将第i个元素赋值给e
    return OK;
  } else {
    printf("GetElem_Sq:Warning:The index i of SequenceList is illegal!\n");
    return ERROR;
  }
}

//在顺序表L中，对e和所有元素的值，依次调用compare函数进行匹配，返回第一个匹配成功的元素的坐标。
int LocateElem_Sq(Sqlist L, ElemType e, Status (*compare)(ElemType, ElemType)) {
  if (!L.elem) {
    printf("LocateElem_Sq:Warning:SequenceList is not initialized!\n");
    return ERROR;
  }
  register int i;
  for (i = 1; i <= L.length; i++) {
    if ((*compare)(e, *(L.elem + i - 1)))
      return i; //当改变compare函数时，要在这里相应的修改传递给compare()函数的参数列表
  }
  return 0;
}

//在顺序表L的第i个元素前插入元素e。如果表长=SIZE,则增加分配顺序表空间，增量为LISTINCREMENT，若i取值非法则返回错误，否则返回OK。
Status ListInsert_Sq(Sqlist *L, int i, ElemType e) {
  if (!L->elem) {
    printf("ListInsert_Sq:Error!:SequenceList is not initialized!\n");
    exit(OVERFLOW);
  }
  if ((i < 1) || (i > L->length + 1)) {
    printf("ListInsert_Sq:Warning:The index i of SequenceList is illegal!\n");
    return ERROR; //当i<1或i>length+1时，为非法值
  }
  if (L->length >= L->listsize) {
    IncListSize_Sq(L); //当表长>=表大小时，增加表的大小，增量为LISTINCREMENT;
  }
  int j = L->length - 1; //初始化j指向最后一个元素
  while (j > i - 2) { //循环终止条件是：j指向了第i个元素之前（下标i-2）
    L->elem[j + 1] = L->elem[j];
    j--;
  }
  L->elem[i-1] = e;
  L->length++;
  return OK;
}

//删除顺序表L的第i个元素，将其赋值给e，如果操作成功返回OK，如果错误则返回ERROR。
Status ListDelete_Sq(Sqlist *L, int i, ElemType *e) {
  if ((i < 1) && (i > L->length))
    return ERROR; // i的合法值为[1,length]
  //    *e = *(L->elem+i-1);
  register ElemType *p = L->elem + i - 1; // p指向第i个元素
  *e = *p;
  while (p < (L->elem + L->length - 1)) { //当p位于[i,length]之间时
    *p = *(p + 1); //将后一个元素的值赋值给前一个元素
    p++;
  }
  L->length -= 1; //表长减1
  return OK;
}

//用键盘向表L中输入元素，若表中已经有内容，就在把输入内容添加在后面（自动更新表的大小）。format是格式控制字符，与scanf中的用法一样，但不支持字符串。
Status ListInput_Sq(const char *format, Sqlist *L) {
  int i = L->length; // p指向表最后元素的下一个位置。此处不用担心表L已满导致P指向非法地址，在后面会对表满做单独处理
  ElemType tmpElem;   
  if (sizeof(ElemType) == 1) { //当元素类型时字符类型时（长度为1）
    do {
      if (i >= L->listsize) {
        IncListSize_Sq(L);       //当表满了，就增加表的大小
      }
      if ((tmpElem=getchar())!='\n'){
        L->elem[i] = tmpElem;
        i++;//如果匹配成功，而且录入值不是回车时，添加元素
      }
    } while (tmpElem!= '\n'); //当输入回车时停止输入。
    L->length = i;
    printf("CharType data are received\n");
  } else { //当元素不是字符类型时(长度不为1)
    do {
      if (i >= L->listsize) {
        IncListSize_Sq(L);
      }
      if ((scanf("%1[\n]", &tmpElem)))
        break; //检查是否直接输入了回车，如果是，就直接结束输入
      if (scanf(format, &tmpElem)) {
        L->elem[i] = tmpElem; //如果匹配成功，就往在表L的末尾添加一个元素
        i++;
      }
      scanf("%*[ ]"); //无论是否读取成功，都尝试清除后面所有的空格。
      if(scanf("%1[^0-9]", &tmpElem)) break;//再尝试读一个字符，如果不是数字就结束输入
    } while (1); //如果输入字后面接的是空格，就继续匹配。（如果是字母或回车会终止录入）
    L->length = i;
    printf("NumType data are received\n");
    if ((tmpElem != '\n')) {
      scanf("%*[^\n]");
      scanf("%*c");
    } //当输入不是因为回车停止时，清空输入缓冲区
  }
  return OK;
}

//输出表L中的内容，format是格式控制符，与printf的格式控制符一样，但这里不支持字符串。
Status ListPrint_Sq(const char *format, Sqlist *L) {
  if (L->length == 0) {
  }

  int i;
  for (i = 1; i <= L->length; i++) {
    printf(format, *(L->elem + i - 1));
  }
  putchar('\n');
  return OK;
}

//一个compare()函数的特例，这里是判断两个元素是否相等。
Status equal(ElemType a, ElemType b) {
  if (a == b)
    return TRUE;
  else
    return FALSE;
}

//对顺序表L中的内容进行冒泡排序
Status ListBubbleSort_Sq(Sqlist *L) {
  register int i , j;
  int change = TRUE;
  ElemType temp;
  for (i = L->length-1; i>0&&change==TRUE; i--) {
    change = FALSE;
    for (j = 0; j < i; j++) {
      if (L->elem[j] > L->elem[j+1]) {
        temp = L->elem[j+1];
        L->elem[j+1] = L->elem[j];
        L->elem[j] = temp;
        change = TRUE;
      }
    }
  }
  return OK;
}

//取顺序表L1和顺序表L2的并集。
Status ListUnion_Sq(Sqlist *L1, Sqlist *L2) {
  while (L1->length + L2->length > L1->listsize) {
    IncListSize_Sq(L1);
  }
  register int i;
  ElemType e;
  for (i = 1; i <= L2->length; i++) {
    GetElem_Sq(*L2, i, &e);
    if (!LocateElem_Sq(*L1, e, equal)) {
      ListInsert_Sq(L1, L1->length+1, e);
    }
  }
  return OK;
}
