#include <stdio.h>

int oute(int num){
    if (num != 0){
        oute(num/8);
        printf("%d",num%8);
    }
}


int main(){
    int a,t = 0;
    scanf("%d",&a);
    while (t != a){
        int x = 0;
        scanf("%d",&x);
        printf("Case #%d:",t+1);
        if (x == 0) {
            printf("0");
        }
        oute(x);
        printf("\n");
        t++;
    }
}