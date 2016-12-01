#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>


int main(int argc,char *argv[])
{
	int read_pipe=atoi(argv[1]);
	int write_pipe=atoi(argv[2]); 
	char buf[2500],input;
	close(write_pipe);
	//pipe'da bişey yoksa read 0 dönüyor
	int read_error = 1;
	int line_size=1;
	while(input != 'q'){
		int i;
  		for(i=0;i<24;i++)
		{
			read_error = read(read_pipe,buf,sizeof(buf));
			printf("line: %d %s\n",line_size,buf);
			line_size++;
			if(read_error==0)
				exit(0);
		
		}
		scanf("%c",&input);
	}
	close(read_pipe);

	return 0;
}
