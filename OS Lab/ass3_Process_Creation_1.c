#include <stdio.h>
#include <unistd.h>

int main(){
	int var=100;
	pid_t pid;
	pid=fork();
	if(pid==0){
		printf("\nReturn value of fork in child process:(%d) is = %d",getpid(),pid);
		printf("\nvalue stored in child variable = %d and its address is = %p",var,&var);	
	}else{
		printf("\nReturn value of fork in parent process:(%d) is = %d",getpid(),pid);
		printf("\nvalue stored in parent variable = %d and its address is = %p",var,&var);		}
	return 0;
}
