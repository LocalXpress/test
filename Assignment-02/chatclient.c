/* * chatclient.c - a program that reads messages with a given identifier * off of a message queue. */ 

#include <stdio.h>        /* Standard I/O functions. */ 
#include <stdlib.h>       /* malloc(), free() etc. */ 
#include <unistd.h>        /* sleep(), etc. */ 
#include <sys/types.h>    /* Various type definitions. */ 
#include <sys/ipc.h>      /* General SysV IPC structures */ 
#include <sys/msg.h>       /* Message queue functions and structs.*/

#define MAX_MSG_SIZE 200  /* Size (in bytes) of largest message we'll send.   */
#define NUM_MESSAGES 20  /* Number of messages the sender program will send. */
#define MTYPE1 1
#define MTYPE2 2
#define MTYPE3 3

struct mymsgbuf{
  long int mtype;
  char mtext[128];
};

int main(int argc, char* argv[]) { 
  int queue_id;                        /* ID of the created queue. */ 
  struct mymsgbuf* msg;               
  struct mymsgbuf* msg_recv;           /* Structure used for received messages. */
  int rc;                             /* Error code returned by system calls. */ 
  int max;
  
  queue_id = msgget((key_t)1234, 0666 | IPC_CREAT); 
  if (queue_id == -1) { 
    perror("main: msgget"); 
    exit(1);
  }
  printf("Message queue opened, queue id '%d'.\n", queue_id);
  puts("Waiting for server");
  msg = (struct mymsgbuf*)malloc((sizeof(struct mymsgbuf)));
  msg_recv = (struct mymsgbuf*)malloc((sizeof(struct mymsgbuf)));

 /* Form a loop of receiving messages and printing them out. */ 
  while (1) { 
    rc = msgrcv(queue_id, msg_recv, MAX_MSG_SIZE+1, MTYPE1, IPC_NOWAIT);
    if (rc == -1) { continue; } 
    printf("\n <server>: %s ", msg_recv->mtext); 
    printf("\n <client>:");
    scanf("%s", msg->mtext);
    msg->mtype = MTYPE2; 
    rc = msgsnd(queue_id, msg, strlen(msg->mtext)+1, IPC_NOWAIT); 
    if (rc == -1) { perror("main: msgsnd"); exit(1); } 
    if( msg->mtext[0] == '#')
      break;
  } 
  return 0;
}
