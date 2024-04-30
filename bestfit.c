#include <stdio.h>
#define MAX 20

int main() {
    int bsize[MAX], fsize[MAX], nb, nf;
    int temp, low = 10000;
    static int bflag[MAX], fflag[MAX];
    int i, j;
   
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);
   
    for(i = 1; i <= nb; i++) {
        printf("Enter the size of memory block %d: ", i);
        scanf("%d", &bsize[i]);
    }
   
    printf("\nEnter the number of files: ");
    scanf("%d", &nf);
   
    for(i = 1; i <= nf; i++) {
        printf("\nEnter the size of file %d: ", i);
        scanf("%d", &fsize[i]);
    }
   
    for(i = 1; i <= nf; i++) {
        for(j = 1; j <= nb; j++) {
            if(bflag[j] != 1) {
                temp = bsize[j] - fsize[i];
                if(temp >= 0) {
                    if(low > temp) {
                        fflag[i] = j;
                        low = temp;
                    }
                }
            }
        }
        bflag[fflag[i]] = 1;
        low = 10000;
    }
   
    printf("\nFile no\tFile size\tBlock no\tBlock size\n");
    for(i = 1; i <= nf; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\n", i, fsize[i], fflag[i], bsize[fflag[i]]);
       
    return 0;
}

	


