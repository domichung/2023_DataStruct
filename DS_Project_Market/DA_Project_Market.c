#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIE TREE

typedef struct SellerData {
    char sellerId[100];  
    int price;           
} SellerData;

typedef struct BstNode {
    char productName[100];     
    SellerData* sellers;          
    int sellerCount;              
    struct BstNode* left;         
    struct BstNode* right;       
} BstNode;

typedef struct ProgramState {
    int insertCount;
    int searchCount;
    int searchFuckup;
    int buyCount;
    int buyfuckup;
    int nodeCount;
    int treeHeight;
} ProgramState;

BstNode* CreateNode() {
    BstNode* root = malloc(sizeof(BstNode));
    root->sellers = NULL;
    root->sellerCount = 0;
    root->left = NULL;
    root->right = NULL;

    return root;
}

BstNode* SearchNode(BstNode* node, char* name) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(node->productName, name) == 0) {
        return node;
    } else if (strcmp(node->productName, name) > 0) {
        return SearchNode(node->left, name);
    } else {
        return SearchNode(node->right, name);
    }
}

BstNode* SearchNode_buy(BstNode* node, char* name) {
    if (node == NULL) {
        return NULL;
    }

    if (strcasecmp(node->productName, name) == 0) {
        return node;
    } else if (strcasecmp(node->productName, name) > 0) {
        return SearchNode(node->left, name);
    } else {
        return SearchNode(node->right, name);
    }
}

void MinHeapify(SellerData* arr, int size, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int smallest = index;

    if (left < size && arr[left].price < arr[smallest].price) {
        smallest = left;
    }

    if (right < size && arr[right].price < arr[smallest].price) {
        smallest = right;
    }

    if (smallest != index) {
        SellerData temp = arr[index];
        arr[index] = arr[smallest];
        arr[smallest] = temp;
        MinHeapify(arr, size, smallest);
    }
}

void putsellpeoplein(BstNode* node, char* sellerId, int price) {
    SellerData* seller = malloc(sizeof(SellerData));
    strcpy(seller->sellerId, sellerId);
    seller->price = price;

    node->sellerCount++;
    node->sellers = realloc(node->sellers, sizeof(SellerData) * node->sellerCount);
    node->sellers[node->sellerCount - 1] = *seller;

    for (int i = node->sellerCount / 2 - 1; i >= 0; i--) {
        MinHeapify(node->sellers, node->sellerCount, i);
    }
}

SellerData* PopSeller(BstNode* node) {
    if (node->sellerCount == 0) {
        return NULL;
    }

    SellerData* seller = malloc(sizeof(SellerData));
    *seller = node->sellers[0];

    node->sellerCount--;
    node->sellers[0] = node->sellers[node->sellerCount];
    MinHeapify(node->sellers, node->sellerCount, 0);

    return seller;
}

void InsertNode(BstNode* root, BstNode* node) {
    if (root == NULL) {
        root = node;
        return;
    }

    if (strcmp(root->productName, node->productName) > 0) {
        if (root->left == NULL) {
            root->left = node;
        } else {
            InsertNode(root->left, node);
        }
    } else {
        if (root->right == NULL) {
            root->right = node;
        } else {
            InsertNode(root->right, node);
        }
    }
}

BstNode* RemoveNode(BstNode* root, BstNode* node) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(root->productName, node->productName) > 0) {
        root->left = RemoveNode(root->left, node);
    } else if (strcmp(root->productName, node->productName) < 0) {
        root->right = RemoveNode(root->right, node);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            BstNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BstNode* temp = root->left;
            free(root);
            return temp;
        } else {
            BstNode* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }

            for(int i=0; i<temp->sellerCount; i++)
                root->sellers[i] = temp->sellers[i];

            strcpy(root->productName, temp->productName);
            root->sellerCount = temp->sellerCount;
            ///////////////++++++++++++++++++++++++
            root->right = RemoveNode(root->right, temp);
        }
    }

    return root;
}

void SortNode(BstNode* node, FILE* f) {
    if (node == NULL) {
        return;
    }

    SortNode(node->left, f);
    fprintf(f, "%s\n", node->productName);
    SortNode(node->right, f);
}

int howtalltree(BstNode* root) {
    if (root == NULL) {
        return 0;
    }

    int left = howtalltree(root->left);
    int right = howtalltree(root->right);

    return left > right ? left + 1 : right + 1;
}

int main() {
    FILE* inputFile = fopen("input3.txt", "r");
    FILE* searchFile = fopen("SearchTable.txt", "w+");
    FILE* buyFile = fopen("BuyTable.txt", "w+");
    FILE* sortFile = fopen("SortTable.txt", "w+");
    FILE* logFile = fopen("LogTable.txt", "w+");
    //FILE *compare = fopen("compare.txt","w+");

    ProgramState state = {0};
    BstNode* root = NULL;
    char inputLine[1000];

    while (fscanf(inputFile, "%s", inputLine) != EOF) {

        if (strncmp(inputLine, "insert",6) == 0) {
            state.insertCount++;
            char name[100];
            char sellerId[100];
            int price = 0;
            
            fscanf(inputFile, "%s %s %d", name , sellerId , &price);

            if (root == NULL) {
                root = CreateNode();
                strcpy(root->productName, name);
                state.nodeCount++;
            }

            BstNode* node = SearchNode_buy(root, name);

            if (node == NULL) {
                node = CreateNode();
                strcpy(node->productName, name);
                InsertNode(root, node);
                state.nodeCount++;
            }

            putsellpeoplein(node, sellerId, price);
            printf("#in %s by %s $$ = %d\n", node->productName, sellerId, price);
            printf("*************************************************%s count: %d, low: %d\n*************************************************", node->productName, node->sellerCount, node->sellers[0].price);
            for (int i = 0; i < node->sellerCount; i++) {
                printf("%d ", node->sellers[i].price);
            }
            printf("\n");
            //fprintf(compare,"in:%s %d\n", name ,state.nodeCount);
        }

        else if ( strncmp(inputLine, "search",6) == 0 ) {
            state.searchCount++;
            char name[100];
            fscanf(inputFile, "%s", name );
            BstNode* node = SearchNode(root, name);

            if (node == NULL) {
                printf("#Search = fuckup\n", name);
                fprintf(searchFile, "%s Not found\n", name);
                state.searchFuckup++;
            } else {
                printf("#Search %s, count: %d\n", node->productName, node->sellerCount);
                fprintf(searchFile, "%s\n", node->productName);
                for (int i = 0; i < node->sellerCount; i++) {
                    fprintf(searchFile, "%s %d\n", node->sellers[i].sellerId, node->sellers[i].price);
                }
            }

            fprintf(searchFile, "----------------------------\n");
        }

        else if ( strncmp(inputLine, "buy",3) == 0 ) {
            state.buyCount++;
            char name[100];
            fscanf(inputFile, "%s", name );
            BstNode* node = SearchNode_buy(root, name);

            if (node == NULL) {
                printf("#buy = fuckup\n", name);
                fprintf(buyFile, "%s Not found\n", name);
                state.buyfuckup++;
            } 
            else {
                SellerData* seller = PopSeller(node);

                printf("#Buy %s, count: %d, low: %d\n", node->productName, node->sellerCount, node->sellers[0].price);
                fprintf(buyFile, "%s %s %d\n", node->productName, seller->sellerId, seller->price);

                if (node->sellerCount == 0) {
                    root = RemoveNode(root, node);
                    ///////////////++++++++++++++++++++++++
                    state.nodeCount--;
                }
            }
            //fprintf(compare,"by:%s %d\n", name ,state.nodeCount);
        }

        else if ( strncmp(inputLine, "sort",4) == 0 ) {
            printf("#sort\n");
            SortNode(root, sortFile);
            fprintf(sortFile, "----------------------------\n");
        }

        else if ( strncmp(inputLine, "report" , 6) == 0 ) {
            printf("#report\n");
            state.treeHeight = howtalltree(root);
            fprintf(logFile, "insert %d\n", state.insertCount);
            fprintf(logFile, "search %d %d\n", state.searchCount, state.searchFuckup);
            fprintf(logFile, "buy %d %d\n", state.buyCount, state.buyfuckup);
            fprintf(logFile, "nodeCount %d\n", state.nodeCount);
            fprintf(logFile, "treeHeight %d\n", state.treeHeight);
        }

        else {
            printf("#error input %s",inputLine);
        }
    }
}
