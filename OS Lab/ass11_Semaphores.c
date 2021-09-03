#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>

typedef struct _rwlock_t{
    sem_t lock;
    sem_t writelock;
    int readers;
} rwlock_t;

rwlock_t rw;
int cnt=1;

void rwlock_init(){
    rw.readers=0;
    sem_init(&rw.lock,0,1);
    sem_init(&rw.writelock,0,1);
}

void rwlock_acquire_readlock(){
    sem_wait(&rw.lock);
    rw.readers++;
    if(rw.readers==1)
        sem_wait(&rw.writelock);
    sem_post(&rw.lock);
}

void rwlock_release_readlock(){
    sem_wait(&rw.lock);
    rw.readers--;
    if(rw.readers==0)
        sem_post(&rw.writelock);
    sem_post(&rw.lock);
}

void rwlock_acquire_writelock(){
    sem_wait(&rw.writelock);
}

void rwlock_release_writelock(){
    sem_post(&rw.writelock);
}

void *writer(int *wno){
	sleep(rand()%10);
    rwlock_acquire_writelock();
    cnt*=2;
    printf("Writer %d, changed the variable cnt to %d\n",*wno,cnt);
    rwlock_release_writelock();
}

void *reader(int *rno){
	sleep(rand()%10);
    rwlock_acquire_readlock();
    printf("Reader %d, read cnt variable as = %d\n",*rno,cnt);
    rwlock_release_readlock();
}

int main(){
	srand(time(NULL));
    pthread_t read[10],write[5];
    rwlock_t rw;
    rwlock_init();
    int a[10]={1,2,3,4,5,6,7,8,9,10};

    for(int i=0;i<10;i++) pthread_create(&read[i],NULL,(void *)reader,&a[i]);
    for(int i=0;i<5;i++) pthread_create(&write[i],NULL,(void *)writer,&a[i]);
    
    for(int i=0;i<10;i++) pthread_join(read[i],NULL);
    for(int i=0;i<5;i++) pthread_join(write[i],NULL);

    return 0;
}
