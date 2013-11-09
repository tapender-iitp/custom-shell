#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main()
{
	char buffer[100];
	char str[100];
	strcpy(str,getcwd(buffer,100));
	printf("%s",str);
	printf("\n");
	return 0;	
}
