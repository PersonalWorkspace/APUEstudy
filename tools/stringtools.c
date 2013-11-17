#include <string.h>

int wordnum(char *str,int size,char end)
{
	int i,count=0;
	int startflag=0;
	for(i=0;i<size&&str[i]!=end&&str[i]!='\0';i++)
	{
		if(str[i]==' '||str[i]=='\t'||str[i]=='\n')
		{
			if(startflag==1)
			{
				startflag=0;
				count++;
			}	
		}
		else
		{
			if(startflag==0)
				startflag=1;
		}
	}
	if(str[i]==end)
	{
		if(startflag==1)
		{
			startflag=0;
			count++;
		}
	}
	return count;
}
