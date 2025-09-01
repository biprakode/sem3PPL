#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char FILENAME[] = "student_record";

typedef struct student_struct {
    unsigned long int rollno;
    char name[64];
    int score[5];
    int is_deleted;
} Student;

void print_student(Student *s);
void input_student(Student *s);
int unique_roll(FILE *fp, unsigned long int rollno);
float calculateTotalScore(Student *s);
void add_record(FILE *fp);
void displayAllRecords(FILE *fp);
void search_roll(FILE *fp, unsigned long int rollno);
void edit_Record(FILE *fp, unsigned long int rollno);
void logical_Delete(FILE *fp, unsigned long int rollno);
FILE *physical_Delete(FILE *fp, const char path[]);
void print_menu();

void print_student(Student *s) {
    if (!s || s->is_deleted == 1) return;
    int total = 0;
    for (int i = 0; i < 5; i++) {
        total += s->score[i];
    }
    printf("%7lu | %-20s | %d\n", s->rollno, s->name, total);
}

void input_student(Student *s) {
    if (!s) return;
    memset(s, 0, sizeof(Student));
    printf("Enter roll number: ");
    scanf("%lu", &s->rollno);
    printf("Enter name: ");
    scanf(" %63[^\n]", s->name);
    printf("Enter 5 scores: ");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &s->score[i]);
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    s->is_deleted = 0;
}

float calculateTotalScore(Student *s) {
    if (!s || s->is_deleted == 1) return 0.0f;
    int total = 0;
    for (int i = 0; i < 5; i++) {
        total += s->score[i];
    }
    return (float)total;
}

void add_record(FILE *fp) {
    if (!fp) {
        printf("File error in add_record\n");
        return;
    }
    Student *s = (Student *)malloc(sizeof(Student));
    if (!s) {
        printf("Memory allocation failed\n");
        return;
    }
    input_student(s);
    if (unique_roll(fp, s->rollno) == 0) {
        int choice;
        printf("Overwrite Record? (1/0):- ");
        scanf("%d", &choice);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (choice != 1) {
            free(s);
            return;
        }
        Student temp;
        rewind(fp);
        while (fread(&temp, sizeof(Student), 1, fp) == 1) {
            if (temp.is_deleted != 1 && temp.rollno == s->rollno) {
                fseek(fp, -sizeof(Student), SEEK_CUR);
                fwrite(s, sizeof(Student), 1, fp);
                fflush(fp);
                printf("Record updated successfully.\n");
                free(s);
                return;
            }
        }
    }
    fseek(fp, 0, SEEK_END);
    fwrite(s, sizeof(Student), 1, fp);
    fflush(fp);
    printf("Record added successfully.\n");
    free(s);
}

void displayAllRecords(FILE *fp) {
    Student s;
    rewind(fp);
    printf("\nRoll No | Name                 | Total Score\n");
    printf("------------------------------------------\n");
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.is_deleted != 1) {
            print_student(&s);
        }
    }
}

int unique_roll(FILE *fp, unsigned long int rollno) {
    Student s;
    rewind(fp);
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.is_deleted != 1 && s.rollno == rollno) {
            return 0;
        }
    }
    return 1;
}

void search_roll(FILE *fp, unsigned long int rollno) {
    Student s;
    rewind(fp);
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.is_deleted != 1 && s.rollno == rollno) {
            found = 1;
            print_student(&s);
            break;
        }
    }
    if (!found) {
        printf("Record with roll number %lu not found.\n", rollno);
    }
}

void edit_Record(FILE *fp, unsigned long int rollno) {
    Student s;
    rewind(fp);
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.is_deleted != 1 && s.rollno == rollno) {
            found = 1;
            print_student(&s);
            printf("Record found => Enter new details\n");
            input_student(&s);
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            fflush(fp);
            printf("Record updated successfully.\n");
            return;
        }
    }
    printf("Record with roll number %lu not found.\n", rollno);
}

void logical_Delete(FILE *fp, unsigned long int rollno) {
    Student s;
    rewind(fp);
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.is_deleted != 1 && s.rollno == rollno) {
            found = 1;
            s.is_deleted = 1;
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            fflush(fp);
            printf("Record logically deleted\n");
            return;
        }
    }
    printf("Record with roll number %lu not found.\n", rollno);
}

FILE *physical_Delete(FILE *fp, const char path[]) {
    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        perror("Error creating temporary file");
        return fp;
    }
    Student s;
    rewind(fp);
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.is_deleted == 0) {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove(path);
    rename("temp.dat", path);
    fp = fopen(FILENAME, "r+");
    if (fp == NULL) {
        perror("Error reopening file after physical delete");
    }
    printf("Physically deleted all logically deleted records.\n");
    return fp;
}

void print_menu() {
    printf("\n--- Student Record Management System ---\n");
    printf("1. Add a new record\n");
    printf("2. Display all records\n");
    printf("3. Search for a record\n");
    printf("4. Edit a record\n");
    printf("5. Logically delete a record\n");
    printf("6. Physically delete all logically deleted records\n");
    printf("0. Exit\n");
}

int main() {
    FILE *fp;
    int choice;
    unsigned long int rollno;
    fp = fopen(FILENAME, "r+");
    if (fp == NULL) {
        fp = fopen(FILENAME, "w+");
        if (fp == NULL) {
            perror("Error opening file");
            return 1;
        }
    }

    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        switch (choice) {
            case 1:
                add_record(fp);
                break;
            case 2:
                displayAllRecords(fp);
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%lu", &rollno);
                while ((c = getchar()) != '\n' && c != EOF);
                search_roll(fp, rollno);
                break;
            case 4:
                printf("Enter roll number to edit: ");
                scanf("%lu", &rollno);
                while ((c = getchar()) != '\n' && c != EOF);
                edit_Record(fp, rollno);
                break;
            case 5:
                printf("Enter roll number to logically delete: ");
                scanf("%lu", &rollno);
                while ((c = getchar()) != '\n' && c != EOF);
                logical_Delete(fp, rollno);
                break;
            case 6:
                fp = physical_Delete(fp, FILENAME);
                if (fp == NULL) {
                    perror("Error reopening file after physical delete");
                    return 1;
                }
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    fclose(fp);
    return 0;
}