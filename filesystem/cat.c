#include "altools.h"
#include <fcntl.h>
#define OPTION_L BIT(0)
#define OPTION_I BIT(1)
#define OPTION_H BIT(2)
#define OPTION_A BIT(2)
#define BUFFSIZE 4096
int checkoption(char option,int source);
int display(int fdin,int fdout);
int setoption(int argnum,char **argarr);
void printf_help();

int main(int argv,char *argc[])
{
	int fdin=STDIN_FILENO;
	int fdout=STDOUT_FILENO;
	int options,i;
	int flag=1;
	char *pathname;
	if((options=setoption(argv,argc))<0)
        {
                printf_help();
                return 0;
        }
        for(i=1;i<argv;i++)
        {
                if(argc[i][0]!='-')
                {
			flag=0;
                        pathname=argc[i];
                        printf("the file %s :\n",pathname);
                        //listdir(options,pathname);
			if((fdin=open(pathname,O_RDONLY))<0)
			{
				fprintf(stderr,"%s\n",strerror(errno));
				return 1;		
			}
			display(fdin,fdout);
			if(close(fdin)!=0)
			{
				fprintf(stderr,"%s\n",strerror(errno));
				return 1;
			}
                }
        }
	if(flag)
	{
		 display(fdin,fdout);
	}
        return 0;
}
int display(int fdin,int fdout)
{
	char buf[BUFFSIZE];
	int n;
	while((n=read(fdin,buf,BUFFSIZE))>0)
        {
                if(write(fdout,buf,n)!=n)
                {
                        //err_sys("write error");
			fprintf(stderr,"%s\n",strerror(errno));
			return 1;
                }
                //printf("the total byte %d\n",fdin); 
        }
        if(n<0)
        {
                //err_sys("read error");
		fprintf(stderr,"%s\n",strerror(errno));
		return 1;
        }
        return 0;
}
int checkoption(char option,int source)
{
         switch(option)
         {
                 case 'l':
                         source=source|OPTION_L;
                         break;
                 case 'i':
                         source=source|OPTION_I;
                         break;
                 case 'a':
                         source=source|OPTION_A;
                         break;
                 case 'h':
                         source=source|OPTION_H;
                         break;
                 default:
                         source=-1;
         }
         return source;
}
int setoption(int argnum,char **argarr)
{
        int options=0;
        int i;
        for(i=1;i<argnum;i++)
        {   
                if(argarr[i][0]=='-')
                {   
                        int j;
                        int length=strlen(argarr[i]);
                        for(j=1;j<length;j++)
                                options=checkoption(argarr[i][j],options);
                        if(options<0)
                        {   
                                printf_help();
                                return -1; 
                        }   
                }   
        }   
        return options;
}
void printf_help()
{
        printf("usage:myls pathname [-option]\n");
}
