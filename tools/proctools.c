#include "proctools.h"

int procArgvNum(char *argvlist,int size)
{
	int num;
	if(argvlist==NULL)
	{
		fprintf(stderr,"procArgvNum:argvlist para is null\n");
		return -1;
	}
	num=wordnum(argvlist,size,'\n')+1;
	return num;
}
int procArgvArr(char *argvlist,int size,char **argvarr,int argvnum)
{
	if(argvlist==NULL)
	{
		fprintf(stderr,"procArgvArr:argvlist para is null\n");
		return -1;
	}
	if(argvarr==NULL)
	{
		fprintf(stderr,"procArgvArr:argvarr para is null\n");
		return -1;
	}
	stringtoarray(argvlist,size,argvarr,argvnum-1,255,'\n');
	free(argvarr[argvnum-1]);
	argvarr[argvnum-1]=NULL;
}
