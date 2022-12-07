#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int i;
	pid_t pid;
	for(i=0;i<5;i++){
		pid=fork();
		if(pid==0){
			execlp("ls","ls","-l","/tmp",NULL);
			exit(0);
		}
		else{
			wait(NULL);
		}
	}
	return 0;
}
