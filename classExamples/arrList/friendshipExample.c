#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct UserList UserList;
typedef User User;

struct User 
{
    char ** arr;
    int size, cap;
    char * name;
};

struct UserList
{
    int size,cap;
    User * arr;
};

UserList * createUserList()
{
    UserList * ret;

    ret = (UserList  *) malloc(sizeof(UserList));
    ret->size = 0;
    ret->cap = 2;
    ret->arr = (User *) malloc(sizeof(User) * ret->cap);

    return ret;
}

void initializeUser(User * user, char * name)
{
    user->size = 0;
    user->cap = 2;
    user->arr = (char **) malloc(sizeof(char *) * user->cap);

    user->name = name;// TODO FIX
}

void append(UserList * list, char * name)
{
    if (list->size == list->cap)
    {
        list->cap *= 2;
        list->arr = (User *) realloc(list->arr, sizeof(User) * list->cap);

        initializeUser(&(list->arr[list->size]), name);
        list->size++;
    }
}

// Add friend to a user
void addFriend(User * user, char * friend)
{
    if (user->size == user->cap)
    {
        //Expand
        user->cap *= 2;
        user->arr = (char **) realloc(user->arr, user->cap * sizeof(char *));
    }

    user->arr[user->size] = friend; // TODO fix
    user->size++;
}

User * findUser(UserList * list, char * name)
{
    //linear search
    for (int i = 0; i < list->size; i++)
    {
        if (strcmp(name, list->arr[i].name) == 0)
        {
            return &list->arr[i];
        }
    }
    // new user
    append(list,name); // creat new user
    return &(list->arr[list->size-1]); // return the new user
    
}

void addFriendShip(UserList * list, char * a, char * b)
{
    // find the users
    User * user_a = findUser(list, a);
    User * user_b = findUser(list, b);

    // add the friendship
    addFriend(user_a, b);
    addFriend(user_b, a);
}

void printUser(User * user)
{
    printf("User %s has %d friends who are:\n", user->name, user->size);
}

void printList(UserList * list)
{
    for (int i = 0; i < list->size; i++)
    {
        printUser(&list->arr[i]);
    }
    
}

int main()
{
    UserList * theList = createUserList();

    char name1[100 + 1];
    char name2[100 + 1];

    while (1)
    {
        scanf("%s", name1);
        if (0 == strcmp("END", name1)) break;
        scanf("%s", name2);
        addFriendShip(theList, name1, name2);
    }
    
    printList(theList);
    
    return(0);
}