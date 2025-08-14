#include <stdio.h>

int main() {
    int x = 10;
    int *p = &x;
    int **pp = &p;

    printf("int :- %d\n" , x);
    printf("int *:- %d\n" , *p);
    printf("int **:- %d\n" , **pp);
}