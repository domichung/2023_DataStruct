#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    
    FILE *out = fopen("D1150211_PE2.csv", "w+");
    //初始化迷宮大小和起始位置
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int starti = atoi(argv[3]);
    int startj = atoi(argv[4]);

    //初始化bug和移動方向
    int bug[40][40] = {0};
    int movei[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int movej[8] = {1, 1, 1, 0, -1, -1, -1, 0};

    //初始化亂數生成器
    srand(time(NULL));

    //開始計算移動次數
    int total = 0;

    //初始也需要計數
    bug[starti][startj] = 1;
    total++;

    //開始走
    while (total < 50000) {
        //生成隨機方向
        int x = rand() % 8;

        //計算新位置
        int newi = starti + movei[x];
        int newj = startj + movej[x];

        //檢查是否在範圍內
        if (newi >= 0 && newi < n && newj >= 0 && newj < m && bug[newi][newj] == 0) {
            //更新bug的位置
            starti = newi;
            startj = newj;
            //增加新儲存格的bug計數
            bug[starti][startj]++;
            total++;
        }
        else {
            //都訪問過即結束
            break;
        }
    }

    //將結果寫入CSV文件
    fprintf(out, "total moves = %d\n", total);
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++) {
            fprintf(out, "%d", bug[i][j]);
            if (j < m-1){
                fprintf(out, ",");
            }
        }
        fprintf(out, "\n");
    }

    fclose(out);
    return 0;
}