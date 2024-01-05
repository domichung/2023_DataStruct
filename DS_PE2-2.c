#include <stdio.h>

int josephus(int n, int m, int start) {
    int result = 0;
    for (int i = 2; i <= n; i++) {
        result = (result + m) % i;
    }
    return (result + start) % n + 1;
}

int main() {
    int n, m, start;
    while (scanf("%d%d",&n,&m)){
        if ( n == 0 && m == 0 ){
            break;
        }
        scanf("%d",&start);
        printf("%d\n", josephus(n, m, start - 1));
    }
    return 0;
}