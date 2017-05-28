#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include <netdb.h>

int main(int argc, char **argv){
 
  int sockfd,n;
  char rline[4097];
  struct sockaddr_in servaddr;
  //struct hostent *he;
  
   if(argc !=2)
      printf("\n error in argument");
   
   if( (sockfd= socket(AF_INET, SOCK_STREAM,0)) < 0)
      printf("\n error in socket creation");
  
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(13000);
  
  
  if( (inet_pton(AF_INET,argv[1], &servaddr.sin_addr)) <= 0)
      printf("\n error in inet_pton creation");  
     
    
    
    if( connect(sockfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
      printf("\n error in connect");
      
    while( (n= read(sockfd,rline,4097)) >0) {
        rline[n]=0;
    
    if(fputs(rline,stdout) == EOF)
       printf("\n error in fputs");
      }
    exit(0);
}    
    
    
