/* * chatserver.c - a program that reads messages with one of 3 identifiers * to a message queue. */ 

#include <stdio.h>     /* Standard I/O functions. */
#include <stdlib.h>    /* malloc(), free() etc. */ 
#include <sys/types.h> /* Various type definitions. */ 
#include <sys/ipc.h>   /* General SysV IPC structures */ 
#include <sys/msg.h>   /* Message queue functions and structs. */

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
  int queue_id;                                 /* ID of the created queue. */ 
  struct mymsgbuf* msg;                         /* Structure used for sent messages. */ 
  struct mymsgbuf* msg_recv; 
  int i;                                     /* Loop counter */ 
  int rc;                                   /* Error code retuend by system calls. */
 
/* Create a public message queue. */ 
  queue_id = msgget((key_t)1234, IPC_CREAT | 0666); 
  if (queue_id == -1) { perror("main: msgget"); exit(1); } 
  printf("Message queue created, queue id '%d'.\n", queue_id);
  puts("Waiting for client");
  msg = (struct mymsgbuf*)malloc((sizeof(struct mymsgbuf))); 
  msg_recv = (struct mymsgbuf*)malloc((sizeof(struct mymsgbuf))); 

/* Form a loop of creating messages and sending them. */ 
  for (;;) {
    printf("\n<server>:");
    scanf("%s", msg->mtext); 
    msg->mtype = MTYPE1; 
    rc = msgsnd(queue_id, msg, strlen(msg->mtext)+1, IPC_NOWAIT); 
    if (rc == -1) { perror("Main: msgsnd"); exit(1); } 
    while(1){
      rc = msgrcv(queue_id, msg_recv, MAX_MSG_SIZE+1, MTYPE2, IPC_NOWAIT); 
      if (rc == -1) { continue; } 
      else break;
    }
    printf("\n<client>: %s", msg_recv->mtext);
    if(msg_recv->mtext[0] == '#')
      break;
  }

/* Free allocated memory. */ 
  free(msg);
  msgctl(queue_id,IPC_RMID, NULL); 
  return 0; 
}
