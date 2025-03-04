#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 513

struct my_msg_st
{
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

int main ()
{
    int running = 1;
    struct my_msg_st some_data;
    int msgid;
    char buffer[BUFSIZ];
    msgid = msgget ((key_t)1234, 0666|IPC_CREAT);
    if (msgid == -1 )
    {
        perror ("MSGGET");
        exit (1);
    }
    while (running)
    {
        printf ("Enter some text\t");
        fgets (buffer, BUFSIZ, stdin);
        some_data.my_msg_type = 1;
        strcpy (some_data.some_text, buffer);
        if (msgsnd (msgid, (void *)&some_data, MAX_TEXT, 0)==-1)
        {
            perror ("MSGSEND");
            exit(1);
        }
        if (strncpy (some_data.some_text, "end", 3)==0)
        {
            running=0;
            break;
        }
    }
    exit (0);
}