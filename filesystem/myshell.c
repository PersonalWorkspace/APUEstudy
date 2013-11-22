#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#define MAXLINE 255
static void sig_init(int);
int main(int argv,char *argc[])
{
	char buf[MAXLINE];
	pid_t pid;
	int status;
	if(signal(SIGINT,sig_init)==SIG_ERR)
	{
		perror(argc[0]);
	}
	printf("%% ");
	while(fgets(buf,MAXLINE,stdin)!=NULL)
	{
		if(buf[strlen(buf)-1]=='\n')
			buf[strlen(buf)-1]=0;
		if(strcmp(buf,"exit")==0)
		{
			return 0;
		}
		if((pid=fork())<0)
		{
			perror(argc[0]);
			return 1;
		}
		else if(pid==0)//为什么这里是子进程的操作？
		{
			execlp(buf,buf,(char *)0);
			printf("cannot execute:%s\n",buf);
			exit(127);
		}
		if((pid=waitpid(pid,&status,0))<0)
		{
			printf("waitpid error\n");
			return 1;
		}
		printf("%% ");
	}
	return 0;

}
void sig_init(int signo)
{
	printf("interrupt:%d\n%%",signo);
}
