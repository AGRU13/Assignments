#include<stdio.h>

long long fact(int n){
	int i;
	long long ans=1;
	for(i=1;i<=n;i++) ans*=i;
	return ans;
}
