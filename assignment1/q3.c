#include <stdio.h>
#include <stdlib.h>

int main() {
    int r , c;
    printf("Enter:- r,c:- ");
    scanf("%d%d" , &r , &c);

    int *ptoarr[r];
    for(int i=0; i<r; i++) {
        ptoarr[i] = (int *)malloc(sizeof(int) * c);
    }

    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("Enter:- [%d][%d]:- " , i , j);
            scanf("%d" , &ptoarr[i][j]);
        }
    }

    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("%d\t"  , ptoarr[i][j]);
        }
        printf("\n");
    }

    for(int i = 0 ; i<r ; i++) {
        free(ptoarr[i]);
    }

    int **pp = (int **)malloc(sizeof(int *) * r);
    for(int i=0; i<r; i++) {
        pp[i] = (int *)malloc(sizeof(int) * c);
    }

    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("Enter:- [%d][%d]:- " , i , j);
            scanf("%d" , &pp[i][j]);
        }
    }

    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("%d\t"  , pp[i][j]);
        }
        printf("\n");
    }

    for(int i = 0 ; i<r ; i++) {
        free(pp[i]);
    }
    free(pp);

    //2D array in 1D
    int *arr = (int *)malloc(sizeof(int) * r + sizeof(int) * c * r);
    for(int i=0; i<r ; i++) {
        *(arr + i) = *(arr + r + i*c);
    }

    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("Enter:- [%d][%d]:- " , i , j);
            scanf("%d" , (&arr[i*r + j]));
        }
    }

    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("%d\t"  , arr[i*r + j]);
        }
        printf("\n");
    }

    free(arr);
}

/*
==237017== HEAP SUMMARY:
==237017==     in use at exit: 0 bytes in 0 blocks
==237017==   total heap usage: 11 allocs, 11 frees, 75,920 bytes allocated
==237017== 
==237017== All heap blocks were freed -- no leaks are possible
==237017== 
==237017== For lists of detected and suppressed errors, rerun with: -s
==237017== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) 
*/