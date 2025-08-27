#include "ass2.h"

typedef struct student_Node
{
    Student *record;
    student_Node *next;
}Node;

Node *head = NULL;
unsigned int mod_len = 0;

Student *create_Student() {
    Student *new_student = (Student *)malloc(sizeof(Student));
    printf("Enter roll number: ");
    scanf("%u", &new_student->roll);
    printf("Enter name: ");
    scanf(" %[^\n]s", new_student->name);
    printf("Enter 5 scores:\n");
    for(int i = 0; i < 5; i++) {
        printf("Score %d: ", i+1);
        scanf("%d", &new_student->score[i]);
    }
    new_student->is_deleted = 0;
    return new_student;
}

void create_Node(Node **node , Student *data) {
    *node = (Node *)malloc(sizeof(Node));
    (*node)->record = data;
    (*node)->next = NULL;
}

void file_read() {
    if(!fp) {
        printf("File error");
        return;
    }
    Student *record;
    Node *current = head;
    while(fread(record , sizeof(Student) , 1 , fp)) {
        create_Node(&current , record);
        current = current->next;
    }
}


void add() {
    Student *new_record = create_Student();
    Node *record; 
    create_Node(&record , new_record);
    Node *current = head;
    while(current != NULL) {
        current = current->next;
    }
    current->next = record;
    current = record;
    mod_len++;
}

void 