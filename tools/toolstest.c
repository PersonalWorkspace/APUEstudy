#include "stringtools.h"
#include "memtools.h"


int main(void)
{
	char buf[255];
	int count;
	char **chbuffer;
	if((chbuffer=charArrAlloc(25,255))==NULL)
	{
		return 1;
	}
	while(fgets(buf,255,stdin)!=NULL)
	{
		count=stringtoarray(buf,255,chbuffer,25,255,'\n');
		printfstrarr(chbuffer,count);
	}
	freeArr(chbuffer,25);
	return 0;
}
