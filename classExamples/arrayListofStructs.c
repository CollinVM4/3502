#include<stdlib.h>
#include<stdio.h>

typedef struct List List;
typedef struct Student Student;

struct Student 
{
    int grade;
    char * name;
};

struct List 
{
    int size, cap;
    Student ** arr;
};

Student * createStudent(char * name, int grade)
{
    // create student * struct
    Student * res = (Student *) malloc(sizeof(Student));

    res->name = (char *) malloc(sizeof(char) * (1 + strlen(name)));
    // strcpy(res->name, name); // dangling pointer, right now just has garbage memory
    res->grade = grade;

    return res;
}


void append(List * list, char * name, int grade)
{   // check if array is full
    if (list->cap == list->size)
    {
        list->cap *= 2;
        list->arr = (Student **) realloc(list->arr, sizeof(Student *) * list->cap);
    }
    list->arr[list->size] = createStudent(name, grade);
    list->size++;
}