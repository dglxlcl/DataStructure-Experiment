#include <stdio.h>
#include <stdlib.h>
#include "MyArray.h"
#include <stdarg.h>

Status InitArray(Array *A,int dim,...){//初始化一个数组A，其维度是dim，可变变量为各个维度的长度。
    if(dim<1||dim>MAX_ARRAY_DIM)
        return ERROR;
    A->dim = dim;
    A->bounds = (int *)malloc(dim * sizeof(int));
    if(!A->bounds)
        exit(OVERFLOW);
    int elemtotal = 1;
    va_list ap;//stdarg.h里定义的宏va_list，实际上是一个指针，用来接收变长参数信息
    va_start(ap, dim);//stdarg.h里的宏，dim是函数的最后一个固定参数，执行后，ap指向第一个可变参数。
    for (int i = 0; i < dim;i++){
        A->bounds[i] = va_arg(ap, int);//va_vag(ap,int)作用是先获取当前ap所值的值（int类型），然后再指向下一个。
        if(A->bounds[i]<0){
            printf("InitArray:Argument input error!\n");
        }
        elemtotal *= A->bounds[i];//为了计算总共的空间大小
    }
    A->base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
    if(!A->base)
        exit(OVERFLOW);
    A->constans=(int *)malloc(dim*sizeof(int));
    A->constans[dim - 1] = 1;
    for (int i = dim - 2; i >= 0;i--){
        A->constans[i] = A->bounds[i + 1] * A->constans[i + 1];
    }
    return OK;
}

Status DestroyArray(Array *A){//销毁一个数组
    if(!A->base)    return ERROR;
    free(A->base);  A->base = NULL;
    if(!A->bounds)  return ERROR;
    free(A->bounds); A->bounds = NULL;
    if(!A->constans) return ERROR;
    free(A->constans); A->constans = NULL;
    return OK;
}

Status Locate(Array A, va_list ap, int *offset){//只用再Assign函数和Value函数里面，根据参数列表，得到元素在A中的相对地址off
    *offset = 0;
    int ind;//用于临时存放各个维度坐标参数
    for(int i=0;i<A.dim;i++){
        ind=va_arg(ap, int);
        if(ind<0||ind>=A.bounds[i]){
            printf("Locate:Argument input error!\n");
            return OVERFLOW;
        }
        *offset+=A.constans[i]*ind;
    }
    return OK;
}

Status Value(Array A,ElemType *e,...){
    va_list ap;
    va_start(ap, e);
    int offset;
    int result;
    if( (result=Locate(A, ap, &offset))<=0 ){
        printf("Value:failed to locate elemtype!\n");
        return OVERFLOW;
    }
    *e=*(A.base+offset);
    return OK;
}

Status Assign(Array *A,ElemType e,...){
    va_list ap;
    va_start(ap, e);
    int offset;
    int result;
    if( (result=Locate(*A, ap, &offset))<=0 ){
        printf("Assign:failed to locate elemtype!\n");
        return OVERFLOW;
    }
    *(A->base+offset)=e;
    return OK;
}




Status CreateSMatrix(SMatrix *M){
    if(M->data){
        printf("GreateSMatrix:The Matrix is initialized already!\n");
        return ERROR;
    }
    M->data = (Triple *)malloc((MAX_MATRIX_SIZE + 1) * sizeof(Triple));
    if(!M->data){
        exit(OVERFLOW);
    }
    printf("SMatrix:Initial...\n");
    int count=0;
    char flag;
    int tmp_i, tmp_j, tmp_e;
    printf("input the total number of row:");
    scanf("%d", &M->mu);
    M->rpos = (int *)malloc((M->mu + 1) * sizeof(int));//下标0未用
    M->rpos[0] = 0;
    M->rpos[1] = 1;
    int rnum[M->mu + 1];//存储每一行非零元的个数
    for (int i = 0; i <= M->mu;i++){//初始化rnum数组
        rnum[i] = 0;
    }
    printf("input the total number of col:");
    scanf("%d", &M->nu);
    printf("Please input the Triple of TSMartrix row by row [example:row,col,number,...],And input '#' for end.\n");
    while (count<MAX_MATRIX_SIZE){
        if( scanf("%d %d %d", &tmp_i,&tmp_j,&tmp_e) ){//data[0]不用
            if(tmp_i<1||tmp_i>M->mu||tmp_j<1||tmp_j>M->nu){
                printf("GreateSMatrix:input error!\n");
                return ERROR;
            }else{
                M->data[count + 1].i = tmp_i;
                M->data[count + 1].j = tmp_j;
                M->data[count + 1].e = tmp_e;
                rnum[M->data[count+1].i]++;
                count++;
            }
        }
        scanf("%c", &flag);
        if(flag=='#')
            break;
    }
    for (int i = 2; i <= M->mu;i++){
        M->rpos[i] = M->rpos[i - 1] + rnum[i - 1];
    }
        M->tu = count;
    return OK;
}

Status DestroySMatrix(SMatrix *M){
    if(!M->data) {
        printf("DestroySMatrix:The Matrix is not initialized.\n");
        return ERROR;
    }
    free(M->data);
    free(M->rpos);
    M->mu = 0;
    M->nu = 0;
    M->tu = 0;
    return OK;
}

Status PrintSMatrix(SMatrix M){//在屏幕上输出矩阵M
    if(!M.data||0==M.mu||0==M.nu){
        printf("PrintSMatrix:The Matrix is not initialized.\n");
        return ERROR;
    }
    int i, j;//打印用的指针，i代表行，j代表列
    int p=1;//SMatrix中非零元的指针。
    for(i = 1;i<=M.mu;i++){
        for(j=1;j<=M.nu;j++){
            if(p<=M.tu&&M.data[p].i==i&&M.data[p].j==j){
                printf("%-9d",M.data[p].e);
                p++;
            }else{
                printf("%-9d",0);
            }
        }
        printf("\n");
    }
    return OK;
}

Status SaveSMatrix(SMatrix M,char *filename){//将SMatrix保存至文件名为filename的文件中
    FILE* fp = fopen(filename,"w");
    if(!fp) {
        printf("SaveSMatrix:failed to open file '%s'\n",filename);
        return ERROR;
    }
    int i,j;
    int p = 1;
    fprintf(fp,"SMatrix.mu=%d,SMatrix.nu=%d\n",M.mu,M.nu);
    for(i=1;i<=M.mu;i++){
        fprintf(fp,"RPOS:%-9d", M.rpos[i]);
        for(j=1;j<=M.nu;j++){
            if(p<=M.tu&&M.data[p].i==i&&M.data[p].j==j){
                fprintf(fp,"%-9d",M.data[p].e);
                p++;
            }else{
                fprintf(fp,"%-9d",0);
            }            
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return OK;
}

Status LoadSMatrix(SMatrix *M,char *filename){//从文件名为filename的文件中读取一个SMatrix
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        printf("LoadSMatrix:failed to open file '%s'\n",filename);
        return ERROR;
    }
    int mu,nu;
    fscanf(fp,"SMatrix.mu=%d,SMatrix.nu=%d",&mu,&nu);
    fscanf(fp, "%*1[\n]");
    M->mu=mu;
    M->nu=nu;
    M->tu=0;
    M->data=(Triple *)malloc((MAX_MATRIX_SIZE+1)*sizeof(Triple));
    M->rpos = (int *)malloc((mu + 1) * sizeof(int));
    M->rpos[0] = 0;
    if(!M->data||!M->rpos){
        printf("LoadSMatrix:Failed to distrbute memmory!\n");
        return ERROR;
    }
    int i,j;
    int p = 1;
    int BRflag;
    ElemType tmpElem;
    for(i=1;i<=M->mu;i++){
        if((fscanf(fp, "RPOS:%d",&M->rpos[i]))){//如果读到rpos数组的数值才继续读下面的数
            for(j=1;j<=M->nu;j++){
                BRflag=0;
                if( (fscanf(fp,"%d",&tmpElem)) ){//如果文档格式符合规范是肯定能读到数值数据的,这里处理非法字符错误
                    if(tmpElem){
                        M->data[p].i=i;
                        M->data[p].j=j;
                        M->data[p].e=tmpElem;
                        M->tu++;
                        p++;
                    }
                }else{
                    printf("LoadSMatrix:Failed to read Matrix!Data corruption!\n");
                    return ERROR;
                }
                fscanf(fp, "%*[ ]");//清除每个元素后面的空格
                fscanf(fp, "%1[\n]",&BRflag);//每读完一个元素，就尝试读一次回车,这里处理列不匹配的情况
                if(j!=M->nu&&BRflag==10){//列宽小于M->mu的情况
                    printf("LoadSMatrix:The Matrix in the file '%s' is not compatible!\n",filename);
                    return ERROR;
                }
                if(feof(fp)) break;
            }
        }else{
            printf("LoadSMatrix:The Matrix in the file '%s' is not compatible!\n",filename);
            return ERROR;           
        }

        if(BRflag!=10){//如果读完一行后，没有读到回车标志
            printf("LoadSMatrix:The Matrix in the file '%s' is not compatible!\n",filename);
            return ERROR;
        }
        if(feof(fp)) break;
    }
    if (i<M->mu){
        printf("LoadSMatrix:The Matrix in the file '%s' is not compatible!\n",filename);
        return ERROR;
    }
    fclose(fp);
    return OK;
}

Status CopySMatrix(SMatrix M,SMatrix *T){//由稀疏矩阵SparseMatrix M得到SparseMatrix T
    if(T->data== NULL){
        T->data = (Triple *)malloc((MAX_MATRIX_SIZE + 1) * sizeof(Triple));
        if(!T->data){
            printf("CopySMatrix:Failed to distrbute memmory!\n");
            return ERROR;
        }
    }
    int p = 1;
    T->mu = M.mu;
    T->nu = M.nu;
    for(int i = 0;i<=M.mu;i++){
        T->rpos[i] = M.rpos[i];
    }
    while(p<=M.tu){
        T->data[p].i = M.data[p].i;
        T->data[p].j = M.data[p].j;
        T->data[p].e = M.data[p].e;
        p++;
    }
    T->tu = M.tu;
    return OK;
}

Status AddSMtrix(SMatrix M,SMatrix N,SMatrix *Q){//SparseMatrix M和N的行列数相等，将矩阵M和N相加得到SparseMatrix Q，Q必须是未初始化的,否则行列数必须和M，N匹配。
    if(M.mu!=N.mu||M.nu!=N.nu){
        printf("AddSMtrix：SparseMatrix M is not compitible with N");
        return ERROR;
    }
    if(Q->data!=NULL&&(Q->mu!=M.mu||Q->nu!=M.nu)){//如果Q已经初始化过了，并且行列数与矩阵M,N不相匹配
        printf("AddSMtrix:SpaseMatrix Q is not compitible with M and N\n");
        return ERROR;
    }else{//Q未经初始化的情况。
        Q->data = (Triple *)malloc((MAX_MATRIX_SIZE + 1) * sizeof(Triple));
        Q->rpos = (int *)malloc((M.mu + 1) * sizeof(int));
        if(Q->data==NULL||Q->rpos==NULL){
            printf("AddSMtrix:Failed to distrbute memmory!\n");
            return ERROR;            
        }
    }
    Q->mu = M.mu;
    Q->nu = M.nu;
    Q->tu = 0;
    int p_M,p_N,p_Q;
    p_M = p_N = p_Q = 1;
    while(p_M<=M.tu&&p_N<=N.tu){
        if(M.data[p_M].i<N.data[p_N].i){//M当前指针所在‘行’ 小于 N当前指针所在‘行’
            Q->data[p_Q] = M.data[p_M];
            Q->tu++;
            p_M++;
            p_Q++;
        }else if (M.data[p_M].i==N.data[p_N].i) {//M当前指针所在‘行’ 等于 N当前指针所在‘行’
            if(M.data[p_M].j<N.data[p_N].j){//M当前指针所在‘列’ 小于 N当前指针所在‘列’
                Q->data[p_Q] = M.data[p_M];
                Q->tu++;
                p_M++;
                p_Q++;
            }else if (M.data[p_M].j==N.data[p_N].j) {//M当前指针所在‘列’ 等于 N当前指针指针所在‘列’
                if((M.data[p_M].e+N.data[p_N].e)!=0){
                    Q->data[p_Q].i = M.data[p_M].i;
                    Q->data[p_Q].j = M.data[p_M].j;
                    Q->data[p_Q].e = M.data[p_M].e+N.data[p_N].e;
                    Q->tu++;
                    p_M++;
                    p_N++;
                    p_Q++;
                }else{
                    p_M++;
                    p_N++;
                }

            }else{//M当前指针所在‘列’ 大于 N当前指针指针所在‘列’
                Q->data[p_Q] = N.data[p_N];
                Q->tu++;
                p_N++;
                p_Q++;
            }
        }else {//M当前指针所在‘行’ 大于 N当前指针所在‘行’
            Q->data[p_Q] = N.data[p_N];
            Q->tu++;
            p_N++;
            p_Q++;
        }
    }
    while(p_M<=M.tu){
        Q->data[p_Q] = M.data[p_M];
        Q->tu++;
        p_M++;
        p_Q++;        
    }
    while(p_N<=N.tu){
        Q->data[p_Q] = N.data[p_N];
        Q->tu++;
        p_N++;
        p_Q++;        
    }

    int rnum[Q->mu + 1];//后面这一段代码都是为了得到Q的rpos数组的值
    for(int i=0;i<=Q->mu;i++){
        rnum[i] = 0;
    }
    p_Q = 1;
    while(p_Q<=Q->mu){
        rnum[Q->data[p_Q].i]++;
        p_Q++;
    }
    Q->rpos[1] = 1;
    for(int i=2;i<=Q->mu;i++){
        Q->rpos[i] = Q->rpos[i - 1] + rnum[i - 1];
    }

    return OK;
}

Status SubtSMtrix(SMatrix M,SMatrix N,SMatrix *Q){//SparseMatrix M和N的行列数相等，将矩阵M和N相减得到SparseMatrix Q，Q必须是未初始化的,否则行列数必须和M，N匹配。
    if(M.mu!=N.mu||M.nu!=N.nu){
        printf("AddSMtrix：SparseMatrix M is not compitible with N");
        return ERROR;
    }
    if(Q->data!=NULL&&(Q->mu!=M.mu||Q->nu!=M.nu)){//如果Q已经初始化过了，并且行列数与矩阵M,N不相匹配
        printf("AddSMtrix:SpaseMatrix Q is not compitible with M and N\n");
        return ERROR;
    }else{//Q未经初始化的情况。
        Q->data = (Triple *)malloc((MAX_MATRIX_SIZE + 1) * sizeof(Triple));
        Q->rpos = (int *)malloc((M.mu + 1) * sizeof(int));
        if(Q->data==NULL||Q->rpos==NULL){
            printf("AddSMtrix:Failed to distrbute memmory!\n");
            return ERROR;            
        }
    }
    Q->mu = M.mu;
    Q->nu = M.nu;
    Q->tu = 0;
    int p_M,p_N,p_Q;
    p_M = p_N = p_Q = 1;
    while(p_M<=M.tu&&p_N<=N.tu){
        if(M.data[p_M].i<N.data[p_N].i){//M当前指针所在‘行’ 小于 N当前指针所在‘行’
            Q->data[p_Q] = M.data[p_M];
            Q->tu++;
            p_M++;
            p_Q++;
        }else if (M.data[p_M].i==N.data[p_N].i) {//M当前指针所在‘行’ 等于 N当前指针所在‘行’
            if(M.data[p_M].j<N.data[p_N].j){//M当前指针所在‘列’ 小于 N当前指针所在‘列’
                Q->data[p_Q] = M.data[p_M];
                Q->tu++;
                p_M++;
                p_Q++;
            }else if (M.data[p_M].j==N.data[p_N].j) {//M当前指针所在‘列’ 等于 N当前指针指针所在‘列’
                if((M.data[p_M].e-N.data[p_N].e)!=0){
                    Q->data[p_Q].i = M.data[p_M].i;
                    Q->data[p_Q].j = M.data[p_M].j;
                    Q->data[p_Q].e = M.data[p_M].e-N.data[p_N].e;
                    Q->tu++;
                    p_M++;
                    p_N++;
                    p_Q++;
                }else{
                    p_M++;
                    p_N++;
                }

            }else{//M当前指针所在‘列’ 大于 N当前指针指针所在‘列’
                Q->data[p_Q] = N.data[p_N];
                Q->tu++;
                p_N++;
                p_Q++;
            }
        }else {//M当前指针所在‘行’ 大于 N当前指针所在‘行’
            Q->data[p_Q] = N.data[p_N];
            Q->tu++;
            p_N++;
            p_Q++;
        }
    }
    while(p_M<=M.tu){
        Q->data[p_Q] = M.data[p_M];
        Q->tu++;
        p_M++;
        p_Q++;        
    }
    while(p_N<=N.tu){
        Q->data[p_Q] = N.data[p_N];
        Q->tu++;
        p_N++;
        p_Q++;        
    }

    int rnum[Q->mu + 1];//后面这一段代码都是为了得到Q的rpos数组的值
    for(int i=0;i<=Q->mu;i++){
        rnum[i] = 0;
    }
    p_Q = 1;
    while(p_Q<=Q->mu){
        rnum[Q->data[p_Q].i]++;
        p_Q++;
    }
    Q->rpos[1] = 1;
    for(int i=2;i<=Q->mu;i++){
        Q->rpos[i] = Q->rpos[i - 1] + rnum[i - 1];
    }

    return OK;
}

Status MultSMatrix(SMatrix M,SMatrix N,SMatrix *Q){//对符合规格要求的两个矩阵M，N，进行相乘，结果存入矩阵Q;
//合法性检查：1、M和N必须存在，且M.nu必须等于N.mu；2.Q若存在，则Q.mu必须等于M.mu，Q.nu必须等于N.nu；3、Q若未初始化则初始化
    if(M.data==NULL||N.data==NULL){
        printf("MultSMatrix:The original Smatrix have not been initialized.\n");
        return ERROR;
    }
    if(M.nu!=N.mu){
        printf("MultSMatrix:The original SMatrix M cant Muliplay the other.\n");
        return ERROR;
    }
    if(Q->data!=NULL&&(Q->mu!=M.mu||Q->nu!=N.nu)){
        printf("MultSMatrix:The target SMatrix is not compitible with the output SMatrix\n");
        return ERROR;
    }
    if(Q->data==NULL){
        Q->data=(Triple*)malloc((MAX_MATRIX_SIZE+1)*sizeof(Triple));
        Q->rpos=(int *)malloc((M.mu+1)*sizeof(int));
        Q->mu=M.mu;
        Q->nu=N.nu;
        Q->tu = 0;
        if(Q->data==NULL||Q->rpos==NULL){
            printf("MultSMatrix:Memmory distributed error!\n");
            exit(OVERFLOW);
        }        
    }

//如果M和N有一个是零矩阵，则什么也不做
    if(M.tu*N.tu==0)
        return OK;

//创建临时累加值数组csum[]，依次存放计算过程中Q每列的临时累加值
    int csum[N.nu + 1];//初始化csum[],下标0不用

//逐行遍历M，每当开始计算某一行，将csum[]清零，根据非零元的列确定应该和N的哪一行的元素相乘，将和放入临时累加值数组。计算完一行，就判断csum[]的值，若是非零元就存入Q
    int p_M=1;
    int p_N;//M和N的指针
    int tp_M,tp_N;//M和N每一行指针的上界
    int Mrow, Nrow;//临时存放计算中M和N的行数
    int Qcol;//临时存放计算中Q的列数
    for (Mrow = 1; Mrow <= M.mu;Mrow++){
        for (int i = 1; i <= N.nu;i++){//每一行开始前，先清零csum[]数组
            csum[i] = 0;
        }

        if(Mrow<M.mu) {//求得矩阵M每一行指针的上界
            tp_M = M.rpos[Mrow+1];
        }else
            tp_M = M.tu + 1;

        Q->rpos[Mrow] = Q->tu + 1;//在每一行计算开始前，先得到这一行Q->rpos的值
        for (p_M = M.rpos[Mrow]; p_M < tp_M;p_M++){//开始遍历矩阵M的某一行的全部元素
            Nrow = M.data[p_M].j;//得到M矩阵某一行具体某列的元素需要和N的哪一行每个元素相乘（乘积根据列值存入csum）
            if(Nrow<N.mu){
                tp_N = N.rpos[Nrow+1];
            }else
                tp_N = N.tu + 1;

            for (p_N = N.rpos[Nrow]; p_N < tp_N;p_N++){//针对矩阵M的某一行的具体某列的元素，开始遍历N中对应的行的元素，乘积放入csum
                Qcol = N.data[p_N].j;
                csum[Qcol] += M.data[p_M].e * N.data[p_N].e;
            }
        }//此处循环结束后，M矩阵某一行所有元素已经计算完毕，相应Q的这一行的值也都存入了csum

        for (int j = 1; j <= Q->nu;j++){//开始扫描csum中的值，如果不等于0，就存入Q
            if(csum[j]!=0){
                if(Q->tu+1>MAX_MATRIX_SIZE){
                    printf("MultSMatrix:The length of target Matrix is overflow!.\n");
                }
                Q->data[Q->tu + 1].i = Mrow;
                Q->data[Q->tu + 1].j = j;
                Q->data[Q->tu + 1].e = csum[j];
                Q->tu++;
            }
        }
    }
    return OK;
}

Status TransposeSMatrix(SMatrix M,SMatrix *T){//对SMartrix M进行转置处理，得到SMatrix T
    if(M.data==NULL){
        printf("TransposeSMatrix:The original Matrix have not been initialized.\n");
        return ERROR;
    }
    if(T->data!=NULL&&(T->mu!=M.nu||T->nu!=M.mu)){//如果SMatrix T 已经存在，而且规格与M转置后的规格不一致
        printf("TransposeSMatrix:The target Matrix is not compitible with the Original Matrix");
        return ERROR;
    }
    if(T->data==NULL){
        T->data=(Triple*)malloc((MAX_MATRIX_SIZE+1)*sizeof(Triple));
        T->rpos=(int *)malloc((M.nu+1)*sizeof(int));
        T->mu=M.nu;
        T->nu=M.mu;
        if(T->data==NULL||T->rpos==NULL){
            printf("TransposeSMatrix:Memmory distributed error!\n");
            exit(OVERFLOW);
        }
    }

    //生成M的每列非零元个数的数组cnum[]，弃用下标0
    int cnum[M.nu+1];
    for(int i = 0 ;i<=M.nu;i++){//初始化cnum[]
        cnum[i]=0;
    }
    int p_M=1;
    while(p_M<=M.tu){
        cnum[M.data[p_M].j]++;//遍历矩阵M的非零元，累加计算对应列的非零元个数,从而得到cnum[]
        p_M++;
    }

    //根据M的cnum[]生成每列第一个非零元的位置cpos[](实际上对应转置后的矩阵T的每行第一个非零元的位置)
    int cpos[M.nu+1];//不用下标0
    cpos[1]=1;
    T->rpos[1] = 1;
    for(int i=2;i<=M.nu;i++){
        cpos[i]=cpos[i-1]+cnum[i-1];//递推得到cpos[]
        T->rpos[i] = T->rpos[i - 1] + cnum[i - 1];//同时得到T->rpos
    }
    T->tu=0;
    //行序优先遍历矩阵M，将元素转置后，根据cpos[]的值放入T中的对应位置
    p_M=1;
    int p_T;
    while(p_M<=M.tu){
        p_T=cpos[M.data[p_M].j];
        T->data[p_T].i=M.data[p_M].j;
        T->data[p_T].j=M.data[p_M].i;
        T->data[p_T].e=M.data[p_M].e;
        T->tu++; //其实这一句可以简化，在前面直接写成T->tu=M.tu;
        cpos[M.data[p_M].j]++;
        p_M++;
    }
    return OK;
}