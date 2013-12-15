#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define BIT(n) (1<<(n))
#define OPTION_L BIT(0)
#define OPTION_I BIT(1)
#define OPTION_H BIT(2)
#define OPTION_A OPTION_L|OPTION_I|OPTION_H
#define MAX_LENGTH 1024



char *get_privileges(mode_t mode,char *privileges);
int listdir(int options,char *pathname);
void setprivileges(int mode,int index,char *pri);
char *get_gnamebyid(int gid);
char *get_unamebyid(int uid);
char *filetype(mode_t mode);
int file_pathcat(char *buf,char *pathname,char *filename,int length);
int checkoption(char option,int source);
int setoption(int argnum,char **argarr);
void printf_help();
int main(int argv,char *argc[])
{
	char *pathname="./";
	int options=0;
	int i;
	if((options=setoption(argv,argc))<0)
	{
		printf_help();
                return 0;
	}
	for(i=1;i<argv;i++)
	{	
		if(argc[i][0]!='-')
		{
			pathname=argc[i];
			printf("the dir %s :\n",pathname);
			listdir(options,pathname);
		}
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
char *get_privileges(mode_t mode,char *privileges)
{
	int i;
	for(i=0;i<9;i++)
	{
		setprivileges(mode,i,privileges);
	}
	privileges[9]='\0';
	return privileges;
}
void setprivileges(int mode,int index,char *pri)
{
	switch(index)
	{
		case 0:
			pri[0]=mode&S_IRUSR?'r':'-';
			break;
		case 1:
			pri[1]=mode&S_IWUSR?'w':'-';
			break;
		case 2:
			pri[2]=mode&S_IXUSR?'x':'-';
			break;
		case 3:
			pri[3]=mode&S_IRGRP?'r':'-';
			break;
		case 4:
			pri[4]=mode&S_IWGRP?'w':'-';
			break;
		case 5:
			pri[5]=mode&S_IXGRP?'x':'-';
			break;
		case 6:
			pri[6]=mode&S_IROTH?'r':'-';
			break;
		case 7:
			pri[7]=mode&S_IWOTH?'w':'-';
			break;
		case 8:
			pri[8]=mode&S_IXOTH?'x':'-';
			break;
		default:
			break;
	}
}
int file_pathcat(char *buf,char *pathname,char *filename,int length)
{
	int pathlength=strlen(pathname);
	//printf("pathname:%s length:%d filename:%s",pathname,pathlength,filename);
	if((pathlength+strlen(filename)+1)>=length)
	{
		return 0;
	}
	strcpy(buf,pathname);
	if(buf[pathlength-1]!='/')
	{
		buf[pathlength]='/';
		buf[pathlength+1]='\0';
	}
	strcat(buf,filename);
	return 1;
}
char *get_unamebyid(int uid)
{
	struct passwd *pw;
	pw=getpwuid(uid);
	if(!pw)
	{
		return NULL;
	}
	return pw->pw_name;
}
char *get_gnamebyid(int gid)
{
	struct group *grp;
	grp=getgrgid(gid);
	if(!grp)
	{
		return NULL;
	}	
	return grp->gr_name;
}
char *filetype(mode_t mode)
{
	switch(mode&S_IFMT)
	{
		case S_IFDIR:
			return "directory";
		case S_IFCHR:
			return "C_oriented device file";
		case S_IFBLK:
			return "B_oriented device file";
		case S_IFREG:
			return "regular file";
		case S_IFLNK:
			return "symbolic link";
		case S_IFSOCK:
			return "socket file";
		case S_IFIFO:
			return "pipe file";
		default:
			return NULL;
	}
}
void printf_help()
{
	printf("usage:myls pathname [-option]\n");
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
int listdir(int options,char *pathname)
{
	DIR *dp;
	struct dirent *dirp;
        struct stat statbuf;
	char apathbuf[MAX_LENGTH];
	if((dp=opendir(pathname))==NULL)
	{
		fprintf(stderr,"cann't open %s\n",pathname);
		return 1;
	}
	while((dirp=readdir(dp))!=NULL)
	{
		if(!strcmp(dirp->d_name,"..")||!strcmp(dirp->d_name,"."))
			continue;
		if(!(options&OPTION_H))
		{
			if(dirp->d_name[0]=='.')
			continue;
		}
		if(file_pathcat(apathbuf,pathname,dirp->d_name,MAX_LENGTH))
        	{
			if(stat(apathbuf,&statbuf)!=0)
			{
				fprintf(stderr,"get failure:%s\n",strerror(errno));
				return 1;
			}
		}
		else
		{
		}	
		if(options&OPTION_L||options&OPTION_I)
		{
			if(options&OPTION_I)
				printf("%d\t",(int)statbuf.st_ino);
			if(options&OPTION_L)
			{
				char *uname,*gname,*mtime;
				int timelength;
				char privileges[10];
				get_privileges(statbuf.st_mode,privileges);
				printf("%s\t",filetype(statbuf.st_mode));
				printf("%s\t",privileges);
				if((uname=get_unamebyid(statbuf.st_uid))!=NULL)
				{
					printf("%s\t",uname);
				}
				if((gname=get_gnamebyid(statbuf.st_gid))!=NULL)
				{
					printf("%s\t",gname);
				}	
				mtime=ctime(&statbuf.st_mtime);
				timelength=strlen(mtime);
				mtime[timelength-1]='\0';
				printf("%s\t",mtime);
			}
		}
		printf("%s",dirp->d_name);
		if((statbuf.st_mode&S_IFMT)==S_IFDIR)
		{
			printf("/");
		}
		printf("\n");
	}
	closedir(dp);
	return 0;
}
