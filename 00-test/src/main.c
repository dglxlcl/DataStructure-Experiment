#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


// void foo(int dim,...){
//     va_list ap;
//     va_start(ap, dim);
//     for (int i = 0; i < dim;i++){
//         printf("fixed argument%d:%d\n",i+1,va_arg(ap, int));
//     }
//     va_end(ap);
// }

// int main(){
//     foo(8, 1,2,3,4,5,6,7,8);
//     return 0;
// }  

int main(){
    int *p = (int *)malloc( 4*sizeof(int));
    p[0]=1;
    p[1]=2;
    p[2]=4;
    p[3]=8;
    return 0;
}
