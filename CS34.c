#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<sys/wait.h>
int main(int argc, char *argv[])
{
	char str[20],*argv1[100];
	int status,flag=0;
	pid_t pid;
	char buffer[100];
        char str2[100];
	char prompt[6]="CS34> ";
        strcpy(str2,getcwd(buffer,100));
	char error_message[30] = "An error has occurred\n";
	if(argv[1]!=NULL) 
	{
		flag++;
		int file_descriptor = open(argv[1],O_RDONLY);
		if(file_descriptor==-1)
			write(STDERR_FILENO, error_message, strlen(error_message));
		dup2(file_descriptor,0);
		if(close(file_descriptor)==-1)
			write(STDERR_FILENO, error_message, strlen(error_message));
	}
	do
	{
		if(flag==0)
			write(STDOUT_FILENO, prompt, strlen(prompt));
		if(gets(str)=='\0')
			exit(0);
		if(flag==1)
			{
			write(STDOUT_FILENO, str, strlen(str));
			printf("\n");
			}
		char *p = str;
				char *words[2];
				int nwords = 0;	
				while(1)
				{
					while(isspace(*p))
						p++;
					if(*p == '\0') {
						break;}
					words[nwords++] = p;
					while(!isspace(*p) && *p != '\0')
						p++;
					if(*p == '\0'){
						break;}
					*p++ = '\0';	
				}			
		if(strcmp(words[0],"exit")==0)
		{
			exit(0);
		}
		else if((nwords==1) && strcmp(words[0],"pwd")==0)
		{
			if((pid = fork())<0) {
				printf("ERROR: forking child process failed");
				exit(1);
			}
			else if(pid==0) {
				argv1[0]=strcat(str2,"/mydir/pwd");
				argv1[1]=NULL;
				execvp(argv1[0],argv1);
				printf("ERROR: exec failed");
				exit(1);
			}
			else {
				waitpid(pid,&status,0);
			}
		
		}
		else
		{
				if((strcmp(words[0],"cd")==0) && (nwords==1))
				{
					char str[100];
					strcpy(str,getenv("HOME"));
					chdir(str);
				}
				else if((strcmp(words[0],"cd")==0) && (nwords>1))
				{
					if(!chdir(words[1]));
					else
						write(STDERR_FILENO, error_message, strlen(error_message)); 	
				}
				else if(nwords!=1 && (strcmp(words[1],">")==0))
				{
										
					if(nwords==3)
					{
					int file_des = open(words[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);				
					if((pid = fork())<0) {
						printf("ERROR: forking child process failed");
						exit(1);
					}
					else if(pid==0) {
						int i;
						for(i=0;i<nwords;i++)
						{
							argv1[i]=words[i];
						}
						argv1[i]='\0';
						dup2(file_des,1);
						argv1[1]=NULL;
						execvp(argv1[0],argv1);
						printf("ERROR: exec failed");
						exit(1);
					}
					else {
						waitpid(pid,&status,0);
					}
					}
					else
						write(STDERR_FILENO, error_message, strlen(error_message)); 	
				}
				else
				{
					if((pid = fork())<0) {
						printf("ERROR: forking child process failed");
						exit(1);
					}
					else if(pid==0) {
						int i;
						for(i=0;i<nwords;i++)
						{
							argv1[i]=words[i];
						}
						argv1[i]='\0';
						execvp(argv1[0],argv1);
						write(STDERR_FILENO, error_message, strlen(error_message));
						exit(1);
					}
					else {
						waitpid(pid,&status,0);
					}		
				}
		}
	}while(1);
return 0;
}
