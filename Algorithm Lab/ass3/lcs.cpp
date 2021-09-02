#include<bits/stdc++.h>
#include<sched.h>
#include<stdbool.h>

using namespace std;
const int INF = 2000000000;

void dp(string &s1,string &s2,int n,int m){
    vector<vector<int>> len(n+1,vector<int>(m+1));
    int i,j;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(i==0 or j==0) len[i][j]=0;
            else if(s1[i-1]==s2[j-1]) len[i][j]=len[i-1][j-1]+1;
            else len[i][j]=max(len[i-1][j],len[i][j-1]);
        }
    }
    // cout<<len[n][m];
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

    int n,i,m;
    int times=10;
    long long tt=0;
    cin>>n>>m;
    string s1,s2;
    cin>>s1>>s2;
    while(times--){
        auto start = std::chrono::high_resolution_clock::now();
        dp(s1,s2,n,m);
        auto stop = std::chrono::high_resolution_clock::now();
	    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        tt+=(long long)duration.count();
    }
	cout<<n<<" "<<tt/10<<"\n";
}
