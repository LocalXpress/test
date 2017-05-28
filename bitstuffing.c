#include<stdio.h>
#include<string.h>
int main()
{
  int i,j,n,count=0;
  char str[100];
  printf("\n enter the string : ");
  gets(str);
  for(i=0;i<strlen(str);i++)
  {
    count=0;
    for(j=i;j<=(i+5);j++)
    {
      if(str[j]=='1')
      {
       count++;
      }
    }
    if(count==6)
    {
     
     for(n=strlen(str)+1;n>=j;n--)
     {
       str[n]=str[n-1];
     }
     str[i+5]='0';
     i=i+5;
    }
   }
   
   printf("\n the string is : ");
   
    printf("%s",str);
   
  return 0;
}
