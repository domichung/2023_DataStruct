#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int value;
    struct tree* left;
    struct tree* right;
} tree;

void insertintree(tree** a, int value) {
    if (*a == NULL) {
        tree* temp = malloc(sizeof(tree));
        temp->left = NULL;
        temp->right = NULL;
        temp->value = value;
        *a = temp;
    } else if (value > (*a)->value) {
        insertintree(&(*a)->right, value);
    } else {
        insertintree(&(*a)->left, value);
    }
}

void printree(tree* tree) {
    if (tree == NULL) {
        return;
    }
    printree(tree->left);
    printf("%d ", tree->value);
    printree(tree->right);
}

void removetree(tree** a, int remove) {
    if (*a == NULL) {
        printf("no find\n");
        return;
    }

    tree* parent = NULL;
    tree* current = *a;

    while (current != NULL && current->value != remove) {
        parent = current;
        current = (remove < current->value) ? current->left : current->right;
    }

    if (current == NULL) {
        printf("no find\n");
        return;
    }

    if (current->left == NULL || current->right == NULL) {
        tree* temp = (current->left != NULL) ? current->left : current->right;

        if (parent == NULL) {
            free(*a);
            *a = temp;
        } 
        else {
            if (parent->left == current) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
            free(current);
        }
    }
    else {
        tree* successorParent = current;
        tree* successor = current->right;

        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        current->value = successor->value;

        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } 
        else {
            successorParent->right = successor->right;
        }

        free(successor);
    }
}

int dfsoftree(tree *a){
    if (a == NULL){
        return 0;
    }
    int left = dfsoftree(a->left);
    int right = dfsoftree(a->right);
    return (1 + (left >= right ? left : right ));
}

int main() {
    int a;
    tree* head = NULL;  
    while (scanf("%d", &a) != EOF) {
        if (a == 0)
            printf("%d\n",dfsoftree(head));
        else if (a > 0) {
            insertintree(&head, a);
        } else if (a < 0) {
            removetree(&head,-a);
        }
        printree(head);
        printf("\n");
    }

    return 0;  
}
