#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
	int shm_id=shm_open("shm_example",O_RDONLY,0666);
	char *ptr=(char *)mmap(0,4096,PROT_READ,MAP_SHARED,shm_id,0);
	printf("receiver mapped address %p\n",ptr);
	printf("Reading the shared memory in the receiver:\n ");
	printf("%s\n",ptr);
	munmap(ptr,4096);
	close(shm_id);
	shm_unlink("shm_example");
	return 0;
}
