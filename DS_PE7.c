#include <stdio.h>

typedef struct dance {
    int canichange;
    int num;
} dance;

typedef struct d1d2 {
    int d1;
    int d2;
} d1d2;

void bubbleSort(d1d2 arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].d1 > arr[j + 1].d1) {
                // swap arr[j] and arr[j+1]
                d1d2 temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int P, D;
        scanf("%d %d", &P, &D);
        dance num[P];

        for (int i = 0; i < P; i++) {
            num[i].num = 999999;
            num[i].canichange = 1;
        }

        num[0].num = 1;

        int x = 0;
        d1d2 _listtt[D];
        while (x < D) {
            int d1, d2;
            scanf("%d %d", &d1, &d2);
            if (d1 > d2) {
                d1 = d1 + d2;
                d2 = d1 - d2;
                d1 = d1 - d2;
            }
            _listtt[x].d1 = d1;
            _listtt[x].d2 = d2;
            x++;
        }

        // Sort _listtt based on d1 values
        bubbleSort(_listtt, D);

        int now = 0;
        while (now < D) {
            int d1 = _listtt[now].d1;
            int d2 = _listtt[now].d2;

            if (d1 == 0) {
                num[d2].canichange = 0;
                num[d2].num = 1;
            } else if (num[d1].num < num[d2].num) {
                if (num[d2].canichange == 1) {
                    num[d2].num = num[d1].num + 1;
                }
            } else if (num[d1].num > num[d2].num) {
                if (num[d1].canichange == 1) {
                    num[d1].num = num[d2].num + 1;
                }
            } else {
                // Handle the case when num[d1].num is equal to num[d2].num
            }
            now++;
        }
        for (int i = 1; i < P; i++) {
            printf("%d\n", num[i].num);
        }
      	printf("\n");
    }
    return 0;
}
