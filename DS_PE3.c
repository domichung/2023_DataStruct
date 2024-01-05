#include <stdio.h>
#include <stdlib.h>

typedef struct list list;

struct list {
    long long int data;  // 修改数据类型为 long long int
    list *link;
};

void outputToFile(list* a, FILE* output_file) {
    while (a != NULL) {
        fprintf(output_file, "%lld->", a->data);  // 修改格式说明符
        a = a->link;
    }
    fprintf(output_file, "NULL\n");
}

void upsidedownoutToFile(list* a, FILE* output_file) {
    if (a == NULL) {
        return;
    }
    upsidedownoutToFile(a->link, output_file);
    fprintf(output_file, "%lld->", a->data);  // 修改格式说明符
}

void upsidedownoutlastnullToFile(list* a, FILE* output_file) {
    upsidedownoutToFile(a, output_file);
    fprintf(output_file, "NULL\n");
}

void clearList(list* a) {
    while (a != NULL) {
        list* temp = a;
        a = a->link;
        free(temp);
    }
}

int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");

    if (input == NULL || output_file == NULL) {
        perror("Error opening files");
        return 1;
    }

    char _mode;
    list *head = NULL;

    while (fscanf(input, " %c", &_mode) != EOF) {
        long long int _value;  // 修改数据类型为 long long int
        if (_mode == 'B') {
            fscanf(input, " %lld", &_value);  // 修改格式说明符

            list *temp = (list*)malloc(sizeof(list));
            temp->data = _value;
            temp->link = head;
            head = temp;
        }
        else if (_mode == 'E') {
            fscanf(input, " %lld", &_value);  // 修改格式说明符

            list *temp = (list*)malloc(sizeof(list));
            temp->data = _value;
            temp->link = NULL;

            if (head == NULL) {
                head = temp;
            }
            else {
                list *temp2 = head;
                while (temp2->link != NULL) {
                    temp2 = temp2->link;
                }
                temp2->link = temp;
            }
        }
        else if (_mode == 'R') {
            if (head != NULL) {
                list* temp = head;
                head = head->link;
                free(temp);
            }
            if (head != NULL) {
                list *temp2 = head;
                list *temp3 = head;
                while (temp2->link != NULL) {
                    temp3 = temp2;
                    temp2 = temp2->link;
                }
                temp3->link = NULL;
            }
        }
    }

    outputToFile(head, output_file);
    upsidedownoutlastnullToFile(head, output_file);

    // Clear the list before exiting
    clearList(head);

    fclose(input);
    fclose(output_file);

    return 0;
}