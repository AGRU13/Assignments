#include<stdio.h>
#include<pthread.h>

void *myfunc(void *arg){
	printf("\nSlave thread %s called.",(char*)arg);
	pthread_exit(0);
}

int main(){
	printf("\nInside main thread!!");
	pthread_t tid1,tid2,tid3;
	pthread_create(&tid1,NULL,myfunc,"A");
	pthread_create(&tid2,NULL,myfunc,"B");
	pthread_create(&tid3,NULL,myfunc,"C");
	printf("\nWaiting for threads to end");
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	printf("\nAll the slave threads are terminated/joined..\n");
	return 0;
}
