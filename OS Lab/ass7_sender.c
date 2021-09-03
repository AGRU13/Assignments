#include<stdio.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	int shm_fd=shm_open("shm_example",O_CREAT|O_RDWR,0666);
	ftruncate(shm_fd,4096);
	char *ptr=(char *)mmap(0,4096,PROT_WRITE,MAP_SHARED,shm_fd,0);
	printf("sender mapped address %p\n",ptr);
	printf("writing to the shared memory from the sender\n");
	sprintf(ptr,"Hello World");
	munmap(ptr,4096);
	close(shm_fd);
	return 0;
}
