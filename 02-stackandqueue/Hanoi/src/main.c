#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//递归算法
long long count;

//存在以个n阶汉诺塔，利用Y，将X移动到Z
void hanoi(int n,char X,char Y,char Z,FILE *fp);

int main()
{
    FILE *fp=fopen("Hanoi_recursion.txt","w");
    if(fp==NULL) exit(0);
    int n;
    clock_t t1,t2;
    printf("Please input the rank of Hanoi:");
    scanf("%d",&n);
    t1=clock();
    hanoi(n,'X','Y','Z',fp);
    t2=clock();
    fprintf(fp,"共耗时：%lf\n",(double)(t2-t1)/CLK_TCK);
    return 0;
}
void hanoi(int n,char X,char Y,char Z,FILE *fp){
    if (n==1){
        count+=1;
        printf("%lld:%c->%c\n", count, X, Z);
        fprintf(fp,"%lld:%c->%c\n",count,X,Z);
        return;
    }else{
        hanoi(n-1,X,Z,Y,fp);
        count++;
        printf("%lld:%c->%c\n", count, X, Z);
        fprintf(fp,"%lld:%c->%c\n",count,X,Z);
        hanoi(n-1,Y,X,Z,fp);
    }
}

//迭代算法
