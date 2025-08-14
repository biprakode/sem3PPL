#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
} person;

void qsort_people(person *arr, int lo, int hi);

int main() {
    int n;
    printf("Enter no. of entries:- ");
    scanf("%d", &n);

    person *people = (person *)malloc(sizeof(person) * n);

    for (int i = 0; i < n; i++) {
        printf("Enter name:- ");
        scanf(" %[^\n]", people[i].name);
        printf("Enter age:- ");
        scanf("%d", &people[i].age);
    }

    qsort_people(people, 0, n - 1);

    printf("Sorted:-\n");
    for (int i = 0; i < n; i++) {
        printf("%s : %d\n", people[i].name, people[i].age);
    }

    free(people);
}

void qsort_people(person *arr, int lo, int hi) {
    if (lo >= hi) return;

    int s = lo, e = hi;
    int piv = arr[(lo + hi) / 2].age; 

    while (s <= e) {
        while (arr[s].age < piv) s++;
        while (arr[e].age > piv) e--;

        if (s <= e) {
            person temp = arr[s];
            arr[s] = arr[e];
            arr[e] = temp;
            s++;
            e--;
        }
    }

    qsort_people(arr, lo, e);
    qsort_people(arr, s, hi);
}
