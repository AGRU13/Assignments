#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	pid_t pid;
	pid=fork();
	if(pid==0){
		printf("\nHello I am child ");
	}else{
		int k;
		wait(&k);
		while(100);
		printf("\nBye...");	
	}
}
