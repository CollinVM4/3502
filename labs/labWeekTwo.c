#include<stdlib.h>
#include<stdio.h>


typedef struct author_t
{
    char name[20];
    int birthYear;
    int publishings;
} author_t;

typedef struct book_t
{
    char name[20];
    int year;
    int numAuthors;
    author_t * authors;
}book_t;


int main()
{
    book_t ** ptrBookArr; // Advanced

    /*part 1 BEGIN*/
    int i, j, numBooks;
    book_t * bookArr; // simple

    // read in the number of books
    scanf("%d", &numBooks);

    // allocate memory for the books
    bookArr = (book_t *) calloc(numBooks, sizeof(book_t));
    for (int i = 0; i < numBooks; i++)
    {
        scanf("%s", bookArr[i].name);
        scanf("%d", &bookArr[i].year);
        scanf("%d", &bookArr[i].numAuthors);

        bookArr[i].authors = 
        (author_t *) calloc(bookArr[i].numAuthors, sizeof(author_t));
        for (int j = 0; j < bookArr[i].numAuthors; j++)
        {
            scanf("%s", bookArr[i].authors[j].name);
            scanf("%d", &bookArr[i].authors[j].birthYear);
            scanf("%d", &bookArr[i].authors[j].publishings);
        }
    }
    /* part 1 END */

    for (int i = 0; i < numBooks; i++)
    {
        printf("%s\n", bookArr[i].name);
        for (int j = 0; j < bookArr[i].numAuthors; j++)
        {
            printf("%s\n", bookArr[i].authors[j].name);
        }
        printf("\n");
    }
    
    /* part 2 BEGIN */
    for (int i = 0; i < numBooks; i++)
    {
        free(bookArr[i].authors);
        bookArr[i].authors = NULL;
    }
    free(bookArr);
    bookArr = NULL;
    /* part 2 END */

    // return a success 
    return EXIT_SUCCESS;
}