#include<stdio.h>
#include<unistd.h>

int main(){
	pid_t pid,maxpid=0,minpid=getpid();
	int k=100;
	FILE *fptr;
	fptr=fopen("num.txt","w");
	while(k--){
		fprintf(fptr,"\nNumber of processes: %d",maxpid-minpid+1);
		pid=fork();
		maxpid=pid>maxpid?pid:maxpid;
	}
	return 0;
}
