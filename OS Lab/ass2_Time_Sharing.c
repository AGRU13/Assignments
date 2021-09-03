#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<unistd.h>

int main(){
	FILE *fptr;
	fptr=fopen("output.csv","w");
	int r=fork();
	int n=1000;
	while(n--){
		struct timeval ts;
		gettimeofday(&ts,NULL);
		fprintf(fptr,"%d,%ld\n",getpid(),ts.tv_sec*1000000+ts.tv_usec);
	}	
	fclose(fptr);
	return 0;
}
