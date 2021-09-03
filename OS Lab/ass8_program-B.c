#include<stdio.h>
#include<sys/mman.h>
#include<stdatomic.h>
#include<unistd.h>
#include<fcntl.h>

typedef struct Data{
	atomic_int status;
	char message[256];
}Data;

int main(){
	int shm_id=shm_open("talk_program",O_CREAT|O_RDWR,0666);
	Data *data=(Data *)mmap(0,sizeof(Data),PROT_READ|PROT_WRITE,MAP_SHARED,shm_id,0);
	while(1){
		while(atomic_load(&data->status)!=1){}
		printf("\nprogram-A: %s\n",data->message);
		printf("\nprogram-B: ");
		gets(data->message);
		atomic_store(&data->status,2);
	}
	munmap(data,sizeof(Data));
	close(shm_id);
	shm_unlink("talk_program");
	return 0;
}
