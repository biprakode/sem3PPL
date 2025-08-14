#include <stdio.h>
#include <stdlib.h>
int* getdim();
void *ptoarr_init(int *data[] , int r , int c);
int **pp_init(int r , int c);
int *arr_init(int r , int c);
void ptoarr_fill_print(int *data[] , int r , int c);
void pp_fill_print(int **data , int r , int c);
void arr_fill_print(int *data , int r , int c);
void ptoarr_free(int *data[] , int r);
void pp_free(int **data , int r);
void arr_free(int *data , int r);
int *oned_init(int r);
void oned_fill_print(int *data , int r);
void oned_free(int *data);

int main() {
    int *dims = getdim();
    int r = dims[0];
    int c = dims[1];
    free(dims);

    int *oned = oned_init(r);
    int *ptoarr[r];
    ptoarr_init(ptoarr , r , c);
    int **pp = pp_init(r , c);
    int *arr = arr_init(r , c);

    oned_fill_print(oned , r);
    ptoarr_fill_print(ptoarr , r , c);
    pp_fill_print(pp , r , c);
    arr_fill_print(arr , r , c);

    oned_free(oned);
    ptoarr_free(ptoarr , r);
    pp_free(pp , r);
    arr_free(arr , r);
}

int* getdim() {
    int *dims = (int *)malloc(2 * sizeof(int));
    printf("Enter:- r,c:- ");
    scanf("%d%d" , &dims[0] , &dims[1]);
    return dims;
}

int *oned_init(int r) {
    return (int *)malloc(sizeof(int) * r);
}

void *ptoarr_init(int *data[] , int r , int c) {
    for(int i=0; i<r; i++) {
        data[i] = (int *)malloc(sizeof(int) * c);
    }
    return data;
}

int **pp_init(int r , int c) {
    int **pp = (int **)malloc(sizeof(int *) * r);
    for(int i=0; i<r; i++) {
        pp[i] = (int *)malloc(sizeof(int) * c);
    }
    return pp;
}


int *arr_init(int r , int c) {
    int *arr = (int *)malloc(sizeof(int) * r + sizeof(int) * c * r);
    for(int i=0; i<r ; i++) {
        *(arr + i) = *(arr + r + i*c);
    }
    return arr;
}

void oned_fill_print(int *data , int r) {
    for(int i=0; i<r; i++) {
        printf("Enter:- [%d]:- ", i);
        scanf("%d", &data[i]);
    }
    for(int i=0; i<r; i++) {
        printf("%d\t", data[i]);
    }
    printf("\n");
}

void ptoarr_fill_print(int *data[] , int r , int c) {
    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("Enter:- [%d][%d]:- " , i , j);
            scanf("%d" , &data[i][j]);
        }
    }

    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("%d\t"  , data[i][j]);
        }
        printf("\n");
    }
}

void pp_fill_print(int **data , int r , int c) {
    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("Enter:- [%d][%d]:- " , i , j);
            scanf("%d" , &data[i][j]);
        }
    }

    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("%d\t"  , data[i][j]);
        }
        printf("\n");
    }
}

void oned_free(int *data) {
    free(data);
}

void arr_fill_print(int *data , int r , int c) {
    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("Enter:- [%d][%d]:- " , i , j);
            scanf("%d" , (&data[i*r + j]));
        }
    }

    for(int i=0; i<r ; i++) {
        for(int j=0 ; j<c ; j++) {
            printf("%d\t"  , data[i*r + j]);
        }
        printf("\n");
    }
}

void ptoarr_free(int *data[] , int r) {
    for(int i = 0 ; i<r ; i++) {
        free(data[i]);
    }
}

void pp_free(int **data , int r) {
    for(int i = 0 ; i<r ; i++) {
        free(data[i]);
    }
    free(data);
}

void arr_free(int *data , int r) {
    free(data);
}