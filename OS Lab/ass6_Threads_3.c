#include<stdio.h>
#include<pthread.h>

static volatile int var;
FILE *fptr;

void *myfunc(void *arg){
	var+=10;
	fprintf(fptr,"\nValue of the variable inside slave thread %s is: %d",(char*)arg,var);	
	pthread_exit(0);
}

int main(){
	fptr=fopen("out.txt","w");
	var=100;
	fprintf(fptr,"\nInitial value of the variable is = %d",var);
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,myfunc,"A");
	pthread_create(&tid2,NULL,myfunc,"B");
	fprintf(fptr,"\nValue of the common variable inside main thread is %d",var);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}
