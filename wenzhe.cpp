#include <stdio.h>
int sum[5];
int cnt[5];
int ss[5][100000];
typedef struct {
    int type;
    int tim1;
    int tim2;
    int start;
    int index;
}customer;
customer s[1000];
void swap(customer *a, customer *b) {
    customer c = *a;
    *a = *b;
    *b = c;
}
int get_wind_VIP(int start, int x) {
    for (int i = start;; i++ ) {
        int flag = 1;
        for (int j = i; j <= i + x && flag; j++) {
            if (ss[4][j] == 1) flag = 0;
        }
        if (flag == 1) return i;
    }
}
int get_wind(int start, int x, int *op) {
    for (int i = start;; i++ ) {
        for (int k = 1; k <= 4; k++) {
            int flag = 1;
            for (int j = i; j <= i + x && flag; j++) {
                if (ss[k][j] == 1) flag = 0;
            }
            if (flag == 1) {
                *op = k;
                return i;
            }
        }
    }
}
int main () {
    printf("请输入客户数量\n");
    int n;
    scanf("%d", &n);
    printf("请依次输入每个客户，到达时间，服务时间,服务类型（0:普通客户 1:VIP客户）\n");
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &s[i].tim1, &s[i].tim2, &s[i].type);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (s[i].tim1 > s[j].tim1) {
                swap(&s[i], &s[j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (s[i].type == 1) {
            int start = get_wind_VIP(s[i].tim1, s[i].tim2);
            s[i].start = start;
            for (int j = start; j <= start + s[i].tim2; j++) {
                ss[4][j] = 1;
            }
            sum[4] += s[i].tim2;
            cnt[4]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (s[i].type == 0) {
            int idx;
            int start = get_wind(s[i].tim1, s[i].tim2, &idx);
            s[i].start = start;
            for (int j = start; j <= start + s[idx].tim2; j++) {
                ss[idx][j] = 1;
            }
            sum[idx] += s[i].tim2;
            cnt[idx]++;
        }
    }
    for (int i = 1; i < 4; i++) {
        printf("窗口%d接待%d位客户，总时常为%d, 平均处理时间为%.2f\n", i, cnt[i], sum[i],
               (cnt[i] == 0 ? 0 : 1.0 * sum[i] / cnt[i]));
    }
    printf("窗口%d(VIP)接待%d位客户，总时常为%d, 平均处理时间为%.2f\n", 4, cnt[4], sum[4],
           (cnt[4] == 0 ? 0 : 1.0 * sum[4] / cnt[4]));
    return 0;
}
