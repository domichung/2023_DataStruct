#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct TreeNode {
    int delay;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int delay) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->delay = delay;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int search(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

TreeNode* buildTree(int in[], int post[], int inStart, int inEnd, int* pIndex) {
    if (inStart > inEnd)
        return NULL;

    TreeNode* node = createNode(post[(*pIndex)--]);

    if (inStart == inEnd)
        return node;

    int iIndex = search(in, inStart, inEnd, node->delay);

    node->right = buildTree(in, post, iIndex + 1, inEnd, pIndex);
    node->left = buildTree(in, post, inStart, iIndex - 1, pIndex);

    return node;
}

void skew(TreeNode* node, int* longest, int* shortest, int currentDelay) {
    if (node == NULL) {
        return;
    }

    currentDelay += node->delay;

    if (node->left == NULL && node->right == NULL) {
        if (currentDelay > *longest) {
            *longest = currentDelay;
        }
        if (*shortest == -1 || currentDelay < *shortest) {
            *shortest = currentDelay;
        }
        return;
    }

    if (node->left) {
        skew(node->left, longest, shortest, currentDelay);
    }
    if (node->right) {
        skew(node->right, longest, shortest, currentDelay);
    }
}

void deleteTree(TreeNode* node) {
    if (node == NULL) return;

    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}

int main() {
    int* inOrder = NULL;
    int* postOrder = NULL;
    int inOrder_size = 0;
    int postOrder_size = 0;
    int num = 0;
    char c;

    while (scanf("%d%c", &num, &c)) {
        int *temp = realloc(inOrder, (inOrder_size + 1) * sizeof(int));
        if (temp == NULL) {
            free(inOrder);
            fprintf(stderr, "Failed to allocate memory\n");
            return 1;
        }
        inOrder = temp;
        inOrder[inOrder_size++] = num;
        if (c == '\n') break;
    }

    while (scanf("%d%c", &num, &c)) {
        int *temp = realloc(postOrder, (postOrder_size + 1) * sizeof(int));
        if (temp == NULL) {
            free(postOrder);
            fprintf(stderr, "Failed to allocate memory\n");
            return 1;
        }
        postOrder = temp;
        postOrder[postOrder_size++] = num;
        if (c == '\n') break;
    }

    int n = inOrder_size;
    int pIndex = n - 1;
    TreeNode* root = buildTree(inOrder, postOrder, 0, n - 1, &pIndex);
    int longest = -1, shortest = INT_MAX;
    skew(root, &longest, &shortest, 0);
    printf("Delayed time (longest path) = %d\n", longest);
    printf("Delayed time (shortest path) = %d\n", shortest);
    deleteTree(root);

    return 0;
}