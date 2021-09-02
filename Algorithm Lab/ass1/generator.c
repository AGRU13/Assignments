#include<stdio.h>
#include<stdlib.h>

int main(int argc,char** args){
	int n=atoi(args[1]);
	printf("%d\n",n);
	for(int i=1;i<=n;i++) printf("%d ",i);
	return 0;
}
