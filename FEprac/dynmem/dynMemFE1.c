#include <stdio.h>
#include <stdlib.h>


typedef struct smart_string
{
    char * word;
    int length;
} smart_string;


smart_string * create_smart_string(char *str)
{
    smart_string* newString = malloc(sizeof(smart_string));
    int stringLength = strlen(str);

    newString->word = malloc(sizeof(char) * stringLength + 1);

    strcpy(newString, str);
    newString->length = stringLength;
    
    return newString;
}   

smart_string *erase_smart_string(smart_string *s)
{
    if(s == NULL) return;

    free(s->word);
    free(s);

    return NULL;
}

int main()
{




    return 0;
}