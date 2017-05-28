/* * queue_reader.c - a program that reads messages with a given identifier * off of a message queue. */ 
#include <stdio.h>        /* standard I/O functions. */ 
#include <stdlib.h>       /* malloc(), free() etc. */ 
#include <unistd.h>        /* sleep(), etc. */ 
#include <sys/types.h>    /* various type definitions. */ 
#include <sys/ipc.h>      /* general SysV IPC structures */ 
#include <sys/msg.h>      /* message queue functions and structs.*/

#define MAX_MSG_SIZE 200  /* size (in bytes) of largest message we'll send.   */
#define NUM_MESSAGES 50  /* number of messages the sender program will send. */
struct mymsgbuf{
  long int mtype;
  char mtext[128];
};
int main(int argc, char* argv[]) { 
  int queue_id;            /* ID of the created queue. */ 
  struct mymsgbuf* msg;   /* structure used for received messages. */
  int rc;                 /* error code returned by system calls. */ 
  long int msg_type;     /* type of messages we want to receive. */ 
  /* read message type from command line */ 
  if (argc != 2) { 
    fprintf(stderr, "Usage: %s <message type>\n", argv[0]); 
    fprintf(stderr, " <message type> must be between 1 and 3.\n"); 
    exit(1); 
  } 
  msg_type = atol(argv[1]); 
  if (msg_type < 1 || msg_type > 3) { 
    fprintf(stderr, "Usage: %s <message type>\n", argv[0]); 
    fprintf(stderr, " <message type> must be between 1 and 3.\n"); 
    exit(1); 
  }
 /* access the public message queue that the sender program created. */
  queue_id = msgget((key_t)1234, 0666 | IPC_CREAT); 
  if (queue_id == -1) { 
    perror("main: msgget"); 
    exit(1);
  } 
  printf("Message queue opened, queue id '%d'.\n", queue_id); 
  msg = (struct mymsgbuf*)malloc((sizeof(struct mymsgbuf)));
 /* form a loop of receiving messages and printing them out. */ 
  while (1) { 
    rc = msgrcv(queue_id, msg, MAX_MSG_SIZE+1, msg_type, IPC_NOWAIT); 
    if (rc == -1) { perror("main: msgrcv"); exit(1); } 
    printf("Read message: '%s' \n", msg->mtext); 
/* slow down a little... */ 
    sleep(1); 
  } 
/* NOT REACHED */
}
