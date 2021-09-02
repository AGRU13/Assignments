#include<bits/stdc++.h>

using namespace std;
#define ll long long 

mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rng(ll lim) {
	uniform_int_distribution<ll> uid(0,lim-1);
	return uid(rang);
}

ll neg(ll lim){
    uniform_int_distribution<ll> uid(-lim,lim-1);
	return uid(rang);
}

int main(int argc,char *argv[]){
    int n=atoi(argv[1]);
    int m=3*n;
    cout<<n<<" "<<m<<"\n";
    for(int i=1;i<=m;i++){
        int a=rng(n)+1,b=rng(n)+1;
        if(a==b){
            i--;
            continue;
        }
        int w=neg(1e5);
        cout<<min(a,b)<<" "<<max(a,b)<<" "<<w<<"\n";
    }
    cout<<(rng(n)+1);
    return 0;
}