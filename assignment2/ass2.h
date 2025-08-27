#include <stdio.h>
#include <stdlib.h>

typedef struct student_struct {
    unsigned int roll;
    char name[64];
    int score[5];
    int is_deleted;
}Student;

extern FILE *fp;
extern Student *head;