#include<stdio.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdatomic.h>

typedef struct Data{
	atomic_int status;
	char message[256];
}Data;

int main(){
	int shm_id=shm_open("talk_program",O_CREAT|O_RDWR,0666);
	ftruncate(shm_id,sizeof(Data));
	Data *data=(Data *)mmap(0,sizeof(Data),PROT_READ|PROT_WRITE,MAP_SHARED,shm_id,0);
	atomic_store(&data->status,0);
	while(1){
		printf("program-A: ");
		gets(data->message);
		atomic_store(&data->status,1);
		while(atomic_load(&data->status)!=2) {}
		printf("\nprogram-B: %s\n",data->message);
		atomic_store(&data->status,0);
	}
	munmap(data,sizeof(Data));
	close(shm_id);
	return 0;
}
