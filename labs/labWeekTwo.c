#include<stdlib.h>
#include<stdio.h>

typedef struct author_t author_t;
typedef struct book_t book_t;


struct author_t
{
    char name[20];
    int birthyear;
    int publishings;
};

struct book_t
{
    char name[20];
    int year;
    int numAuthors;
    author_t * authors;
};






int main()
{







    return(0);
}