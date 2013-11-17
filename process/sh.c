#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define BUFFERSIZE 255
int findcommandindex(char *buf,int size)
{
	int i;
	for(i=0;i<size&&buf[i]!='\0';i++)
	{
		if(buf[i]==' '||buf[i]=='\t')
			break;
	}
	return i;
}
int main(int argc,char **argv)
{
	//if(argc<=1)
	//{
	//	fprintf(stderr,"usage:%s command\n",argv[0]);
	//	return 0;
	//}	
	char buf[BUFFERSIZE];
	int pid;
	int status;
	int commandindex;
	char command[255];
	char errorlog[4096];
	printf("%%");
	while(fgets(buf,BUFFERSIZE,stdin)!=NULL)
	{
		if(buf[strlen(buf)-1]=='\n')
			buf[strlen(buf)-1]=0;
		if((pid=fork())<0)
		{
			snprintf(errorlog,4096,"%s",strerror(errno));
			fprintf(stderr,"%s\n",errorlog);
		}
		else if(pid==0)
		{
			commandindex=findcommandindex(buf,BUFFERSIZE);
			strncpy(command,buf,commandindex+1);
			command[commandindex]='\0';
			execlp(command,buf,(char *)0);
			snprintf(errorlog,4096,"%s",strerror(errno));
			fprintf(stderr,"%s\n",errorlog);
			return errno;
		}
		else
		{
			if((pid=waitpid(pid,&status,0))<0)
			{
				snprintf(errorlog,4096,"%s",strerror(errno));
				fprintf(stderr,"%s\n",errorlog);
			}
		}
		printf("%%");
	}
	return 0;
}
