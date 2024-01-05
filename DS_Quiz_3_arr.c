#include <stdio.h>
int magic[1024][1024] = {0};
int main(){
    int x;
    scanf("%d",&x);
    while (x--){
        int time = 0;
        int ball = 0;
        scanf("%d %d",&time,&ball);
        int thold = time;
        long long int math = 0;
        long long int mathnum = 1;
        while (thold>0){
            math = math + mathnum;
            thold--;
            mathnum = mathnum*2;
        }
        
        for (int i = 0 ; i < 1024 ; i++){
            for( int j = 0 ; j < 1024 ; j++ ){
                magic[i][j] = ((i*1024)+j < math ? 1 : 0);
                if (magic[i][j]>0){
                    //printf("%d %d \n",i,j);
                }
            }
        }

        long long int final = 0;
        while (ball--){
            long long int num=0;
            while (1){
                if (magic[num/1024][num%1024]==1){
                    magic[num/1024][num%1024]=2;
                    long long int checknum = num*2+1;
                    //printf("a : %d ;",checknum);
                    if (checknum > 1048576){
                        //printf("o");
                        break;
                    }
                    else if (magic[checknum/1024][checknum%1024] == 0){
                        //printf("o");
                        break;
                    }
                    else {
                        num = checknum;
                    }
                }
                else {
                    //printf("m");
                    magic[num/1024][num%1024]=1;
                    long long int checknum = (num*2)+2;
                    if (checknum > 1048576){
                        break;
                    }
                    else if (magic[checknum/1024][checknum%1024] == 0){
                        break;
                    }
                    else {
                        num = checknum;
                    }
                }
            }
            final = num;
        }
        printf("%d\n",final+1);
    }
}

//不是吧 用陣列幹是最快的