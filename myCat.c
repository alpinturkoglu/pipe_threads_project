#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

//myCat function reads the file.
int main(int argc, char *argv[])
{
	printf("Program works with: ./myCat filename or ./myCat filename = myMore\n\n");
	//Variables for file operations
	FILE *file;
	file=fopen(argv[1],"r");
	char singleLine[2500];
	//Variables for creating a pipe
	int fd[2];
	
	if(argc==2)
	{
		
		if(strcmp(argv[0],"./myCat")==0 && file!=NULL)
		{
			
			while(!feof(file))
			{
				fgets(singleLine,2500,file);
				puts(singleLine);
			}
		
		}
		else
		{
			printf("The arguments are named invalid\n");
		}
	}
	else if(argc==4)
	{
		if(strcmp(argv[0],"./myCat")==0 && strcmp(argv[2],"=")==0 && strcmp(argv[3],"myMore")==0) //The pipe process needs to have an operator = and 2 arguments more. 
		{
			if(pipe(fd))
			{
				perror("pipe");
				return -1;
			}
		switch(fork())
		{
			case -1:
				perror("fork error");
				return -1;
			case 0: //child process
			printf("CHILD process of the pipe\n");
			
			char p1[10],p2[10];
			sprintf(p1,"%d",fd[0]);
			sprintf(p2,"%d",fd[1]);
			
			printf("%d  %d\n",fd[0],fd[1]);
			char *arr[5]={"./myMore",p1,p2, NULL};
			//Runs myMore program
			int e=execv("./myMore",arr);
			printf("error: %d\n",e);
			
			default: //parent process
			printf("Parent Process\n");
			close(fd[0]);
			//Writing to the pipe
			while(!feof(file))
			{
				fgets(singleLine,2500,file);
				write(fd[1],singleLine,sizeof(singleLine));
			}
			
			close(fd[1]);
			wait(NULL);
		}
		}
		else
		{
			printf("The arguments are named invalid\n");
		}
	}
	else 
	{
		printf("The count of arguments are wrong\n");
	}

	
	//Close the file
	fclose(file);
	return 0;
}
