#include<bits/stdc++.h>
#include<sched.h>
#include<stdbool.h>

using namespace std;
const int INF = 2000000000;

void order(int i,int j,vector<vector<int>> &s){
	if (i==j) {
        cout<<i<<" ";
		return;
	}	 
    cout<<"( ";
	order(i,s[i][j],s);
	order(s[i][j]+1,j,s);
    cout<<") ";
}

void dp(vector<int>&arr,int n){
    vector<vector<int>> m(n,vector<int>(n)),s(n,vector<int>(n));
    int i,j,k,l,q;
    for(i=0;i<n;i++) m[i][i]=0;
    for(l=2;l<n;l++){
        for(i=1;i<n-l+1;i++){
            j=i+l-1;
            m[i][j]=INF;
            for(k=i;k<=j-1;k++){
                q=m[i][k]+m[k+1][j]+arr[i-1]*arr[k]*arr[j];
                if(q<m[i][j]){
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
    // order(1,n-1,s);
    // cout<<m[1][n-1]<<"\n";
}

int main(){
    cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0,&set);
	struct sched_param prior_param;
	int prior;
	memset(&prior_param,0,sizeof(struct sched_param));
	sched_setaffinity(0,sizeof(cpu_set_t), &set);
	prior=sched_get_priority_max(SCHED_FIFO);
	prior_param.sched_priority=prior;
	sched_setscheduler(0,SCHED_FIFO,&prior_param);

    int n,i;
    
    int times=10;
    long long tt=0;
       	cin>>n;
        vector<int> arr(n);
        for(i=0;i<n;i++) cin>>arr[i];

    while(times--){
        auto start = std::chrono::high_resolution_clock::now();
        dp(arr,n);
        auto stop = std::chrono::high_resolution_clock::now();
	    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        tt+=(long long)duration.count();
    }
	cout<<n<<" "<<tt/10<<"\n";
}