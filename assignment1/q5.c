#include <stdio.h>
#include <stdlib.h>
void qsort(int *ages , char **names , int n , int lo , int hi);

int main() {
    int n;
    printf("Enter no. of entries:- ");
    scanf("%d" , &n);
    
    char **names = (char **)malloc(sizeof(char *) * n);
    int *ages = (int *)malloc(sizeof(int) * n);

    for(int i = 0 ; i<n ; i++) {
        names[i] = (char *)malloc(sizeof(char) * 50);
        printf("Enter name:- ");
        scanf(" %[^\n]" , names[i]);
        printf("Enter age:- ");
        scanf("%d" , &ages[i]);
    }

    qsort(ages , names , n , 0 , n-1);

    printf("Sorted:- \n")
    for(int i = 0 ; i<n ; i++) {
        printf("%s : %d\n" , names[i] , ages[i]);
    }

    for(int i = 0 ; i<n ; i++) free(names[i]);
    free(names);
    free(ages);
}

void qsort(int *ages , char **names , int n , int lo , int hi) {
    if (lo>=hi) {
        return;
    }

    int s = lo;
    int e = hi;
    int piv = ages[rand() % (n)];
    while(ages[s] < piv) s++;
    while(ages[e] > piv) e--;

    if(s <= e) {
        // swap s & e
        ages[s] = ages[s]^ages[e];
        ages[e] = ages[s]^ages[e];
        ages[s] = ages[s]^ages[e];
        char *temp = names[s];
        names[s] = names[e];
        names[e] = temp;
        s++;
        e--;
    }

    qsort(ages , names , n , lo , e);
    qsort(ages , names , n , s , hi);
}



