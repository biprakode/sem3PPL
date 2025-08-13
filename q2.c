#include <stdio.h>
#include <stdlib.h>

int main() {
    int size;
    printf("Enter no. of elements:- ");
    scanf("%d" , &size);

    int *arr = (int *)malloc(sizeof(int) * size);

    for(int i = 0 ; i<size ; i++) {
        printf("Enter %dth:- ");
        scanf("%d" , arr+i);
    }

    for(int i = 0 ; i<size ; i++) {
        printf("Enter %dth:- %d" , *(arr + i));
    }
}