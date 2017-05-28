/* * queue_sender.c - a program that sends messages with one of 3 identifiers * to a message queue. */ 
#include <stdio.h> /* standard I/O functions. */
#include <stdlib.h> /* malloc(), free() etc. */ 
#include <sys/types.h> /* various type definitions. */ 
#include <sys/ipc.h> /* general SysV IPC structures */ 
#include <sys/msg.h> /* message queue functions and structs. */

#define MAX_MSG_SIZE 200  /* size (in bytes) of largest message we'll send.   */
#define NUM_MESSAGES 50  /* number of messages the sender program will send. */
struct mymsgbuf{
  long int mtype;
  char mtext[128];
};
int main(int argc, char* argv[]) { 
  int queue_id;                                 /* ID of the created queue. */ 
  struct mymsgbuf* msg;                         /* structure used for sent messages. */ 
/*struct msgbuf* recv_msg;*/ 
  int i;                                     /* loop counter */ 
  int rc;                                   /* error code retuend by system calls. */ 
/* create a public message queue, with access only to the owning user. */ 
  queue_id = msgget((key_t)1234, 0666 | IPC_CREAT); 
  if (queue_id == -1) { perror("main: msgget"); exit(1); } 
  printf("Message queue created, queue id '%d'.\n", queue_id); 
  msg = (struct mymsgbuf*)malloc((sizeof(struct mymsgbuf))); 
/* form a loop of creating messages and sending them. */ 
  for (i=1; i <= NUM_MESSAGES; i++) { 
    msg->mtype = (i % 3) + 1;               /* create message type between '1' and '3' */ 
    sprintf(msg->mtext, "Hello - %d", i); 
    rc = msgsnd(queue_id, msg, strlen(msg->mtext)+1, 0); 
    if (rc == -1) { perror("main: msgsnd"); exit(1); } 
  } 
/* free allocated memory. */ 
  free(msg); 
  printf("Generated %d messages, exiting.\n", NUM_MESSAGES); 
  return 0;
}

