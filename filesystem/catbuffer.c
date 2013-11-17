#include <stdio.h>


int main(int argc,char **argv)
{
	int c;
//	char buf[255];
//	vsnprintf(buf,255,"this for test%d\n",6);
	while((c=getc(stdin))!=EOF)
	{
		if(putc(c,stdout)==EOF)
			fprintf(stderr,"Write error");
	}
	if(ferror(stdin))
		fprintf(stderr,"Input error");
//	printf("%s",buf);
	return 0;
}
