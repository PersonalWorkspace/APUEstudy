#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFSIZE 4096
int main(int argv,char *argc[])
{
	int in,out,n;
	char buf[BUFFSIZE];
	in=STDIN_FILENO;
	out=STDOUT_FILENO;
	if(argv>2)
	{
		printf("usage:mycat [filename]\n");
		return 0;
	}
	if(argv==2)
	{
		if((in=open(argc[1],O_RDONLY,0))==-1)
		{
			printf("cannot open file %s\n",argc[1]);
			return 1;
		}
	}
	while((n=read(in,buf,BUFFSIZE))>0)
	{
		if(write(out,buf,n)!=n)
		{
			printf("write error\n");
			return 1;
		}
	}
	if(n<0)
	{
		printf("read error\n");
		return 1;
	}
	return 0;
}
