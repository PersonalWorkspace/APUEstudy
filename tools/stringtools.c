#include "stringtools.h"

int wordnum(char *str,int size,char end)
{
//统计str字符串中单词的数量，size为传入字符串的数组的大小，end可以为\nor\0，用以决定统计一行或者整个字符串的单词数
	int i,count=0;
	int startflag=0;
	if(str==NULL)
        {
                fprintf(stderr,"wordnum:str para is null\n");
                return -1;
        }
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
			{
				startflag=1;
			}	
		}
	}
        if(startflag==1)
        {
                startflag=0;
		count++;
	}
	return count;
}
int stringtoarray(char *str,int size,char **array,int rowmax,int colmax,char end)
{
	 int i,count=0;
        int startflag=0;
	char *currentword;
	int curwordlen=0;
	if(str==NULL)
        {
                fprintf(stderr,"stringtoarray:str para is null\n");
                return -1;
        }
        if(array==NULL)
        {
                fprintf(stderr,"stringtoarray:array para is null\n");
                return -1;
        }
        for(i=0,currentword=str;i<size&&str[i]!=end&&str[i]!='\0';i++)
        {
                if(str[i]==' '||str[i]=='\t'||str[i]=='\n')
                {
                        if(startflag==1)
                        {
                                startflag=0;
				if(curwordlen<colmax&&count<rowmax)
				{
					strncpy(array[count],currentword,curwordlen);
					array[count][curwordlen]='\0';
				}
                                count++;
                        }
                }
                else
                {
                        if(startflag==0)
			{
                                startflag=1;
				currentword=&str[i];
				curwordlen=0;
			}
			curwordlen++;
                }
        }
        if(startflag==1)
        {
                startflag=0;
		if(curwordlen<colmax&&count<rowmax)
		{
			strncpy(array[count],currentword,curwordlen);
			array[count][curwordlen]='\0';
		}
                count++;
        }
        return count;
}
int printfstrarr(char **array,int rownum)
{
	int i;
	if(array==NULL)
        {
                fprintf(stderr,"printfstrarr:array para is null\n");
                return -1;
        }
	for(i=0;i<rownum;i++)
	{
		printf("%d:%s\n",i,array[i]);
	}
	return 0;
}
