#include <stdio.h>
#include <stdlib.h>

int main(  ){
    int i = 0xffffffff;
    printf("i=%x\n", i);
    printf("&i =%p\n", &i);
    char ch;
    printf("&ch=%p\n", &ch);
    scanf("%[a]", &ch);
    printf("i=%x\n", i);
    printf("ch=%d",ch);
    system("pause"); 
    return 0;
}  

// int main(){
//     char str[10]={1,1,1,1,1,1,1,1,1,1};
//     scanf("%s", str);
//     printf("接收完毕\n");
//     printf("%s\n", str);
//     for (int i = 0; i < 10;i++){
//         printf("%02X ", (unsigned char)str[i]);
//     }

//     return 0;
// }