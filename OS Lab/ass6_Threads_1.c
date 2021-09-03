#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/wait.h>

void *myfunc(){
	return NULL;	
}

int main(){
	double processtime=0,threadtime=0;
	struct timeval start,end;
	int times=1000,k;
	pthread_t tid;
	while(times--){
		gettimeofday(&start,NULL);
		pid_t pid;
		pid=fork();
		if(pid>0) return 0;
		else {
			gettimeofday(&end,NULL);
			wait(&k);
			processtime+=end.tv_usec-start.tv_usec;
		}
		gettimeofday(&start,NULL);
		pthread_create(&tid,NULL,myfunc,NULL);
		gettimeofday(&end,NULL);
		pthread_join(tid,NULL);
		threadtime+=end.tv_usec-start.tv_usec;
	}
	processtime/=1000;
	threadtime/=1000;
	printf("\nAverage time for process creation is = %lf microsecs and that for thread is = %lf microsecs \n",processtime,threadtime);
	return 0;
}
