#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "proctools.h"
#include "memtools.h"
#define BUFFERSIZE 255
#define MAX_ARGVS 100
#define MAX_ARGV 255
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
	char **argvs;
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
			int argvnum;
			argvnum=procArgvNum(buf,BUFFERSIZE);
			if((argvs=charArrAlloc(argvnum+1,MAX_ARGV))==NULL)
          		{
                  		return 1;
         		}
			//printf("argvnum:%d\n",argvnum);
			procArgvArr(buf,BUFFERSIZE,argvs,argvnum);
			//stringtoarray(buf,BUFFERSIZE,argvs,argvnum,MAX_ARGV,'\n');
			//argvs[argvnum][0]='\0';
			//printfstrarr(argvs,argvnum);
			execvp(argvs[0],argvs);
			//execlp(command,buf,(char *)0);
			snprintf(errorlog,4096,"%s",strerror(errno));
			fprintf(stderr,"%s\n",errorlog);
			freeArr((void**)argvs,argvnum);
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
