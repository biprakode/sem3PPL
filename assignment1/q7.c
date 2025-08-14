#include <stdio.h>
#include <stdlib.h>

typedef struct student_struct {
    int roll;
    char *name;
    int *scores;
    int score_size;
}student;

void add_student(student ***data, int *size);
void delete_student(student **students, int size, int roll);
void print_students(student **students, int size);

int main() {
    student **students = NULL;
    int size = 0;
    int choice;

    while (1) {
        printf("\n== Student Menu ==\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Delete Student\n");
        printf("4. Exit\n");
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
            free(students[i]->scores);
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
        if (!data) {
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
        printf("Enter number of scores: ");
        scanf("%d", &entry->score_size);
        entry->scores = (int *)malloc(entry->score_size * sizeof(int));

        for (int i = 0; i < entry->score_size; i++) {
            printf("Score %d: ", i + 1);
            scanf("%d", &entry->scores[i]);
            getchar();
        }

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
            free(students[i]->scores);
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
            printf("Roll: %d, Name: %s, Scores:", students[i]->roll, students[i]->name);
            for (int j = 0; j < students[i]->score_size; j++) {
                printf(" %d", students[i]->scores[j]);
            }
            printf("\n");
        }
    }
}