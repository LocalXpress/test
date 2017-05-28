#include<stdio.h>
#include<string.h>
int main()
{
    int i,j,count=0,n1;
char str[100];
printf("enter the bit string");
gets(str);
for(i=0;i<strlen(str);i++)
{
count=0;  // the following code search the six ones  in given string
for(j=i;j<=(i+5);j++)
{
if(str[j]=='1'){
count++;
}
}
          //if there is six 1 then the following code execute bit stuffing after 5 ones

if(count==5 )
{
n1=j;
for(;n1<=strlen(str);n1--)
{
str[n1]=str[n1-1];
}
str[i+5]='0';
i=i+5;
}
}
puts(str);
return 0;
}




