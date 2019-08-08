#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


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

// int main(){
//     int a = 3;
//     int array[a];
//     for (int i = 0; i < a;i++){
//         array[i] = i;
//     }
//     for (int i = 0; i < a;i++){
//         printf("%d", array[i]);
//     }
//     return 0;
// }

void getnext(char *S, int *next);

void adv_getnext(char *S, int *next);

int main(){
    char *ch = {"abaabaaabaaaab"};
    int len = strlen(ch);
    int next[len];
    adv_getnext(ch, next);
    for (int i = 0; i < len;i++){
        next[i]++;
    }
    return 0;
}


void getnext (char *S,int *next){
    int length = strlen(S);
    next[0] = -1;
    int i = 0;
    int j = -1;
    while(i<length){
        if(j==-1||S[i]==S[j]){
            i++;
            j++;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}

void adv_getnext(char *S,int *next){
    int length = strlen(S);
    next[0] = -1;
    int i = 0;
    int j = -1;
    while(i<length){
        if(j==-1||S[i]==S[j]){
            i++;
            j++;
            if(S[i]==S[j]){
                next[i] = next[j];
            }else next[i] = j;
        }else{
            j = next[j];
        }
    }    
}