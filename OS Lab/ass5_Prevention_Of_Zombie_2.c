#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	pid_t pid;
	pid=fork();
	if(pid==0){
		pid_t gcpid;
		gcpid=fork();
		if(gcpid==0){
			printf("\nI am not going to become a zombie yay....");
			fflush(stdout);
			sleep(10);
		}
	}else{
		int k;
		wait(&k);
		while(1);
	}
	return 0;
}
