#include <stdio.h>

int search(char arr[], char x, int n) {
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

void printPostOrder(char in[], char pre[], int n, FILE *output) {
    if (n == 0)
        return;

    int root = search(in, pre[0], n);
    if (root == -1) {
        return;
    }

    printPostOrder(in, pre + 1, root, output);
    printPostOrder(in + root + 1, pre + root + 1, n - root - 1, output);
    fprintf(output, "%c", pre[0]);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        perror("Error opening files");
        return 1;
    }

    int value_tree = 0;
    fscanf(input, "%d", &value_tree);

    char preorder[60];
    char inorder[60];

    fscanf(input, "%s", preorder);
    fscanf(input, "%s", inorder);

    printPostOrder(inorder, preorder, value_tree, output);

    fclose(input);
    fclose(output);

    return 0;
}