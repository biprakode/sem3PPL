#include <stdio.h>
#include <stdlib.h>

typedef struct student_struct {
    int roll;
    char *name;
    int score;  
} student;

void add_student(student ***data, int *size);
void delete_student(student **students, int size, int roll);
void print_students(student **students, int size);
int user_sort(student *entry1 , student* entry2);
void qsort(student **students , int size , int (*user_sort)(student * , student *) , int lo , int hi);

int main() {
    student **students = NULL;
    int size = 0;
    int choice;

    while (1) {
        printf("\n== Student Menu ==\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Delete Student\n");
        printf("4: Sort Student (select return from user_sort):- \n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            add_student(&students, &size);
        } 
        else if (choice == 2) {
            printf("\n");
            print_students(students, size);
        } 
        else if (choice == 3) {
            int roll;
            printf("Enter roll to delete: ");
            scanf("%d", &roll);
            delete_student(students, size, roll);
        } 
        else if (choice == 4) {
            qsort(students , size , user_sort , 0 , size-1);
            printf("Sorted\n");
            print_students(students, size);
        }
        else if (choice == 5) {
            break;
        } 
        else {
            printf("Invalid choice.\n");
        }
    }

    // free all remaining students
    for (int i = 0; i < size; i++) {
        if (students[i]) {
            free(students[i]->name);
            free(students[i]);
        }
    }
    free(students);

    return 0;
}

void add_student(student*** data , int *size) {
    int stop = 0;
    while (!stop) {
        *data = (student **)realloc(*data, (*size + 1) * sizeof(student *));
        if (!*data) {  // fixed check
            perror("realloc failed");
            return;
        }

        student *entry = (student *)malloc(sizeof(student));

        printf("Enter roll: ");
        scanf("%d", &entry->roll);
        getchar(); // clear newline

        entry->name = (char *)malloc(sizeof(char) * 100);
        printf("Enter name: ");
        scanf(" %[^\n]" , entry->name);

        printf("Enter score: ");
        scanf("%d", &entry->score);

        (*data)[*size] = entry;
        (*size)++;

        printf("Stop? (1 = yes, 0 = no): ");
        scanf("%d", &stop);
    }
}

void delete_student(student **students, int size, int roll) {
    for (int i = 0; i < size; i++) {
        if (students[i] && students[i]->roll == roll) {
            free(students[i]->name);
            free(students[i]);
            students[i] = NULL;
            printf("Deleted roll %d\n", roll);
            return;
        }
    }
    printf("Roll %d not found.\n", roll);
}

void print_students(student **students, int size) {
    for (int i = 0; i < size; i++) {
        if (students[i] != NULL) {
            printf("Roll: %d, Name: %s, Score: %d\n", 
                   students[i]->roll, students[i]->name, students[i]->score);
        }
    }
}


int user_sort(student *entry1 , student* entry2) {
    return entry1->roll - entry2->roll; // desc roll
    return entry1->score - entry2->score; // desc score
    return entry2->roll - entry1->roll; // asc roll
    return entry2->score - entry1->score; // asc score
}



void qsort(student **students , int size , int (*user_sort)(student * , student *) , int lo , int hi) {
    if(lo >= hi) return;

    int s=lo;
    int e=hi;
    student *piv = students[(lo + hi)/2];
    while(s<=e) {
        while ((user_sort(students[s] , piv) > 0)) s++;
        while ((user_sort(students[s] , piv)) < 0) e--; 

        if(s<=e) {
            student *temp = students[s];
            students[s] = students[e];
            students[e] = temp;
            s++;
            e--;
        }
    }

    if (lo < e) qsort(students, size, user_sort, lo, e);
    if (s < hi) qsort(students, size, user_sort, s, hi);
}