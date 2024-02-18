#include <stdio.h>
#include <stdlib.h>


typedef struct tv_show 
{
    char *show_name;
    int number_of_seasons;
} tv_show;



struct tv_show * delete_show_list (struct tv_show *show_list, int length) 
{
    for (int i = 0; i < length; i++)
    {
        free(show_list[i].show_name);
    }
    
    free(show_list);

    return NULL;
}

int main()
{




    return 0;
}