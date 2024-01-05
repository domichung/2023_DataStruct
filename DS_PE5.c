#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
} MinHeap;

MinHeap* createMinHeap(int size) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->arr = (int*)malloc(sizeof(int) * size);
    minHeap->size = size;
    return minHeap;
}

void heapify(MinHeap* minHeap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < minHeap->size && minHeap->arr[left] < minHeap->arr[smallest])
        smallest = left;

    if (right < minHeap->size && minHeap->arr[right] < minHeap->arr[smallest])
        smallest = right;

    if (smallest != i) {
        int temp = minHeap->arr[i];
        minHeap->arr[i] = minHeap->arr[smallest];
        minHeap->arr[smallest] = temp;
        heapify(minHeap, smallest);
    }
}

int extractMin(MinHeap* minHeap) {
    int min = minHeap->arr[0];
    minHeap->arr[0] = minHeap->arr[--minHeap->size];
    heapify(minHeap, 0);
    return min;
}

int main() {
    FILE *inputFile = fopen("DS_PE5_input.txt", "r");
    FILE *outputFile = fopen("DS_PE5_output.txt", "w");

    int time;

    while (fscanf(inputFile, "%d", &time) != EOF) {
        MinHeap* minHeap = createMinHeap(time);

        fgetc(inputFile);

        for (int i = 0; i < time; i++) {
            fscanf(inputFile, "%d", &minHeap->arr[i]);
        }

        for (int i = time / 2 - 1; i >= 0; i--) {
            heapify(minHeap, i);
        }

        int total = 0;

        while (minHeap->size > 1) {
            int min1 = extractMin(minHeap);
            int min2 = extractMin(minHeap);
            int sum = min1 + min2;
            minHeap->arr[minHeap->size++] = sum;
            total += sum;
        }

        fprintf(outputFile, "%d\n", total);

    }
}