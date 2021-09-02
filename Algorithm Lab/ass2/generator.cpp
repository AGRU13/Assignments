#include<bits/stdc++.h>
using namespace std;

mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
long long rng(long long lim) {
	uniform_int_distribution<long long> uid(0,lim-1);
	return uid(rang);
}

int main(int argc,char** args){
  int n=atoi(args[1]);
  int i;
  cout<<n<<"\n";
  for(int i=0;i<n;i++) cout<<rng(1e9)<<" "; 
  return 0;
}
