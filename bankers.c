#include <stdio.h>

struct pro {
    int all[10], max[10], need[10];
    int flag;
};

int i, j, pno, r, nr, id, k = 0, safe = 0, exec, count = 0, wait = 0, max_err = 0;
struct pro p[10];
int aval[10], seq[10];

void safeState() {
    while (count != pno) {
        safe = 0;
        for (i = 0; i < pno; i++) {
            if (p[i].flag) {
                exec = r;
                for (j = 0; j < r; j++) {
                    if (p[i].need[j] > aval[j]) {
                        exec = 0;
                        break;
                    }
                }
                if (exec == r) {
                    for (j = 0; j < r; j++) {
                        aval[j] += p[i].all[j];
                    }
                    p[i].flag = 0;
                    seq[k++] = i;
                    safe = 1;
                    count++;
                }
            }
        }
        if (!safe) {
            printf("System is in Unsafe State\n");
            break;
        }
    }
    if (safe) {
        printf("\n\nSystem is in safe state \n");
        printf("Safe State Sequence \n");
        for (i = 0; i < k; i++)
            printf("P[%d] ", seq[i]);
        printf("\n\n");
    }
}

void reqRes() {
    printf("\nRequest for new Resources\n");
    for (i = 0; i < r; i++) {
        scanf("%d", &nr);
        if (nr <= p[id].need[i]) {
            if (nr <= aval[i]) {
                aval[i] -= nr;
                p[id].all[i] += nr;
                p[id].need[i] -= nr;
            } else
                wait = -1;
        } else
            max_err = 1;
    }
    if (!max_err && !wait)
        safeState();
    else if (max_err)
        printf("\nProcess has exceeded its maximum age \n");
    else
        printf("\n Process needs to wait\n");
}

int main() {
    int ch = 1;
    printf("Enter no of processes: ");
    scanf("%d", &pno);
    printf("Enter no of resources: ");
    scanf("%d", &r);
    printf("Enter Available Resources of each type: ");
    for (i = 0; i < r; i++) {
        scanf("%d", &aval[i]);
    }
    printf("\n\n---Resource details---\n");
    for (i = 0; i < pno; i++) {
        printf("Resource for process %d\n", i);
        printf("Allocation Matrix\n");
        for (j = 0; j < r; j++)
            scanf("%d", &p[i].all[j]);
        printf("Maximum Resource request\n");
        for (j = 0; j < r; j++)
            scanf("%d", &p[i].max[j]);
        p[i].flag = 1;
    }
    for (i = 0; i < pno; i++) {
        for (j = 0; j < r; j++) {
            p[i].need[j] = p[i].max[j] - p[i].all[j];
        }
    }
    printf("\nProcess Details\n");
    printf("Pid\t\tAllocation\t\tMax\t\tNeed\n");
    for (i = 0; i < pno; i++) {
        printf("%d\t\t", i);
        for (j = 0; j < r; j++) {
            printf("%d ", p[i].all[j]);
        }
        printf("\t\t");
        for (j = 0; j < r; j++) {
            printf("%d ", p[i].need[j]);
        }
        printf("\n");
    }
    safeState();
    do {
        printf("Request new resource? [0/1]: ");
        scanf("%d", &ch);
        if (ch)
            reqRes();
    } while (ch != 0);
    printf("\n");
    return 0;
}


