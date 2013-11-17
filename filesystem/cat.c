#include "apue.h"


#define BUFFSIZE 4096



int main(void)
{
	int n;
	char buf[BUFFSIZE];
	while((n=read(STDIN_FILENO,buf,BUFFSIZE))>0)
	{
		if(write(STDOUT_FILENO,buf,n)!=n)
		{
			err_sys("write error");
		}
		printf("the total byte %d\n",STDIN_FILENO);
		
	}
	if(n<0)
	{
		err_sys("read error");
	}
	return 0;
}
