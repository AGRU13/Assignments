#include<stdio.h>

//this functions return 0 if the number is not prime otherwise 1
int isprime(int n){
	if(n<=1) return 0;
	if(n<=3) return 1;
	if(n%2==0||n%3==0) return 0;
	int i=5;
	while(i*i<=n){
		if(n%i==0||n%(i+2)==0) return 0;
		i+=6;
	}
	return 1;
}
