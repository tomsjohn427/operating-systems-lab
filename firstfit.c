#include <stdio.h>

struct process {
    int ps;
    int flag;
};

struct sizes {
    int size;
    int alloc;
};

int main() {
    struct process p[50];
    struct sizes s[5];
    int i = 0, np = 0, n = 0, j = 0;

    printf("\nFirst Fit Memory Allocation\n");
    printf("\nEnter the number of blocks: ");
    scanf("%d", &n);

    printf("\nEnter the size for %d blocks:\n", n);
    for (i = 0; i < n; i++) {
        printf("Enter the size for block %d: ", i);
        scanf("%d", &s[i].size);
        s[i].alloc = 0; // Initialize allocation status to 0
    }

    printf("\nEnter the number of processes: ");
    scanf("%d", &np);

    printf("\nEnter the size of %d processes:\n", np);
    for (i = 0; i < np; i++) {
        printf("Enter the size of process %d: ", i);
        scanf("%d", &p[i].ps);
        p[i].flag = 0; // Initialize flag to 0
    }

    printf("\nAllocation of blocks using First Fit:\n");
    printf("\nProcess\tProcess Size\tBlock\n");

    for (i = 0; i < np; i++) {
        for (j = 0; j < n; j++) {
            if (p[i].flag != 1 && p[i].ps <= s[j].size && s[j].alloc == 0) {
                p[i].flag = 1;
                s[j].alloc = 1;
                printf("%d\t%d\t\t%d\n", i, p[i].ps, s[j].size);
                break; // Break the inner loop after allocation
            }
        }
        if (p[i].flag != 1)
            printf("Sorry! Process %d must wait as there is no sufficient memory\n", i);
    }

    return 0;
}


