#include<stdio.h>
#include<pthread.h>

void *thread_by_thread(void *arg){
	printf("\nThis thread is created by slave thread %s","A");
} 

void *create_thread(void *arg){
	printf("\nInside thread %s",(char *)arg);
	pthread_t pidnw;
	int rc=pthread_create(&pidnw,NULL,thread_by_thread,NULL);
	if(rc==0) printf("\nSuccessfully created another thread in thread %s",(char *)arg);
	else printf("\nUnable to create another thread in thread %s",(char *)arg);
	pthread_exit((void *)100);
}

void *kill_thread(void *arg){
	pthread_t tid=*(pthread_t *)arg;
	void *exit_status;
	int rc=pthread_join(tid,&exit_status);
	if(rc==0) printf("\nSuccessfulle killed thread 'A' in thread 'B' and exit status of 'A' thread is = %ld",(long)exit_status);
	else printf("\nCannot kill thread 'A' in thread 'B'");	
}

void *detach_thread(void *arg){
	printf("\nInside the detached thread...");
	return NULL;
}

int main(){
	pthread_t tid1,tid2,tid3;
	pthread_create(&tid1,NULL,create_thread,"A");
	pthread_create(&tid2,NULL,kill_thread,&tid1);
	pthread_join(tid2,NULL);
	pthread_create(&tid3,NULL,detach_thread,NULL);
	pthread_detach(tid3);
	int rc=pthread_join(tid3,NULL);
	if(rc==0) printf("\nSuccessfully killed the detached thread");
	else printf("\nNot able to kill the detached thread\n");
	return 0;
}
