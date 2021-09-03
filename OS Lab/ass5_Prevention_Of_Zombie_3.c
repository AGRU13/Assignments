#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main(){
	signal(SIGCHLD,SIG_IGN);
	pid_t pid;
	pid=fork();
	if(pid==0){
		printf("\nI am child and I am not going to become a zombie...");
		fflush(stdout);
		sleep(10);
	}else{
		printf("\nI am parent..");
		fflush(stdout);
		while(100);
	}
	return 0;
}
