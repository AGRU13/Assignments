#include<bits/stdc++.h>

using namespace std;
#define ll long long 

mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rng(ll lim) {
	uniform_int_distribution<ll> uid(0,lim-1);
	return uid(rang);
}
int main(int argc,char *argv[]){
    int n=atoi(argv[1]),i;
    cout<<n<<"\n";
    for(i=0;i<n;i++) cout<<(rng(100)+1)<<" ";
    return 0;
}