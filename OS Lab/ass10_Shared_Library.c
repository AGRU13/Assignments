#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

int main(){
	void *handle;
	long long (*factorial)(int);
	int (*ifprime)(int),num;
	char *error;

	handle=dlopen("./libA.so",RTLD_LAZY);
	if(!handle){
		fputs(dlerror(),stderr);
		exit(1);
	}
	dlerror();
	factorial=dlsym(handle,"fact");
	if((error=dlerror())!=NULL){
		fputs(error,stderr);
		exit(1);
	}
	printf("Enter a number to find its factorial: ");
	scanf("%d",&num);
	printf("factorial of %d = %ld\n",num,(*factorial)(num));
	dlclose(handle);

	handle=dlopen("./libB.so",RTLD_LAZY);
	if(!handle){
		fputs(dlerror(),stderr);
		exit(1);
	}
	dlerror();
	ifprime=dlsym(handle,"isprime");
	if((error=dlerror())!=NULL){
		fputs(error,stderr);
		exit(1);
	}

	printf("Enter a number to check if it is a prime or not: ");
	scanf("%d",&num);
	if((*ifprime)(num)==1) printf("%d is a prime number.\n",num);
	else printf("%d is not a prime number.\n",num);
	dlclose(handle);
	return 0;
}
