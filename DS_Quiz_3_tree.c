#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int value;
    int now;
    // 1 左 2 右
    
    struct tree* left;
    struct tree* right;
} tree;

tree* createtree(tree* hi,int time,int value){
    tree* temp = malloc(sizeof(tree));
    temp->now=1;
    (temp->value)=value;
    //printf("%d",temp->value);
    if (time>0){
        time = time - 1;
        temp->left = createtree(temp->left,time,2*(temp->value));
        temp->right = createtree(temp->right,time,2*(temp->value)+1);
    }
    else {
        return NULL;
    }
    return temp;
}

void printree(tree* a){
    if (a->left != NULL){
        printree(a->left);
    }
    printf("%d ",a->value);
    if (a->right != NULL){
        printree(a->right);
    } 
}

int fuckofball(tree* hi){
    if (hi->left != NULL){
        if ( hi->now == 1){
            int x = fuckofball(hi->left);
            hi->now = 2;
            return x;
        }
        else{
            int x = fuckofball(hi->right);
            hi->now = 1;
            return x;
        }
    }
    else {
        return hi->value;
    }
}


int main(){
    int x;
    scanf("%d",&x);
    while (x--){
        tree* head = NULL;
        int w = 0,ball = 0;
        scanf("%d %d",&w,&ball);
        head = createtree(head,w,1);
        //printree(head);
        int output = 0;
        while (ball--){
            output = fuckofball(head);
        }
        printf("%d\n",output);
    }
    
}