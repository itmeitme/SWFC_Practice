#include <stdio.h>
  
long long int sum[1001][1001];
  
int main(void)
{
    int x, y, N, M;
    scanf("%d", &N);
      
    for (x = 1; x <= N; x++) {
        long long int ysum = 0;
        for (y = 1; y <= N; y++) {
            int num;
            scanf("%d", &num);;
            if (x == 1) {
                if (y == 1) sum[x][y] = num;
                else sum[x][y] = sum[x][y - 1] + num;
            }
            else {
                ysum += num;
                sum[x][y] = sum[x - 1][y] + ysum;
            }
        }
    }
    scanf("%d", &M);
    for (int x = 0; x < M; x++) {
        int sri, sci, eri, eci;
        scanf("%d %d %d %d", &sri, &sci, &eri, &eci);
        printf("%lld\n", sum[eri][eci] - sum[sri - 1][eci] - sum[eri][sci - 1] + sum[sri - 1][sci - 1]);
    }
  
    return 0;
}
