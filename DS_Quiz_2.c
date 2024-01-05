#include <stdio.h>
#include <stdlib.h>

int main(){
    int t = 0;
    scanf("%d",&t);
    while (t--){   
        int stack[100000];
        int flag = 0;
        char hohoho[100000];
        scanf("%s",&hohoho);
        int top = 0,now = 0;
        while (hohoho[now]=='['||hohoho[now]==']'||hohoho[now]=='('||hohoho[now]==')'){
            //printf("w%c",hohoho[now]);
            if (hohoho[now]=='('){
                hohoho[top] = 1;
                top++;
            }
            else if (hohoho[now] == '['){
                hohoho[top] = 2;
                top++;
            }
            else if (hohoho[now] == ')'){
                if (top-1>=0){
                    if (hohoho[top-1]==1){
                        top--;
                    }
                    else{
                        flag = 1;
                        //printf("c1");
                        break;
                    }
                }
                else{
                    flag = 1;
                    //printf("c3");
                    break;
                }
            }
            else if (hohoho[now] == ']'){
                if (top-1>=0){
                    if (hohoho[top-1]==2){
                        top--;
                    }
                    else{
                        flag = 1;
                        //printf("c2");
                        break;
                    }
                }
                else{
                    flag = 1;
                    //printf("c4");
                    break;
                }
            }
            now++;
        }
        if (top == 0 && flag == 0){
                printf("Yes\n");
            }
            else{
                printf("No\n");
            }
            now++;
    }
}