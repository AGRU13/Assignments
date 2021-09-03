#include<stdio.h>
#include<unistd.h>

int main(){
	pid_t pid;
	FILE *fptr;
	fptr=fopen("t.txt","w");
	pid=fork();
	if(pid==0){
		fprintf(fptr,"\nHello I am child and my pid is = %d",getpid());
	}else{
		fprintf(fptr,"\nHello I am parent of %d and my pid is = %d",pid,getpid());
	}
	return 0;
}
