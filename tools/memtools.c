#include "memtools.h"


char **charArrAlloc(int row,int col)
{
	char **strarr;
	int i;
	if((strarr=(char **)malloc(row*sizeof(char *)))==NULL)
	{
		fprintf(stderr,"Malloc failed:%s\n",strerror(errno));
		return NULL;
	}
	for(i=0;i<row;i++)
	{
		if((strarr[i]=(char *)malloc(col*sizeof(char *)))==NULL)
		{
			fprintf(stderr,"Malloc failed:%s\n",strerror(errno));
			freeArr((void **)strarr,i);
			return NULL;
		}
	}
	return strarr;
}
void freeArr(void **ptr,int row)
{
	int i;
	if(ptr==NULL)
        {
                fprintf(stderr,"freeArr:ptr para is null\n");
                return ;
        }
	for(i=0;i<row;i++)
	{
		free(ptr[i]);
	}
	free(ptr);
}
