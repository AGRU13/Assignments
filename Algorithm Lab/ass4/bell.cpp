#include<bits/stdc++.h>
#include<sched.h>
#include<stdbool.h>

using namespace std;
const int INF = 1000000000;

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

    int n,m,i,j;
    cin>>n>>m;
    vector<pair<int,int>> adj[n+1]; 
    for(int i=0;i<m;i++){
        int a,b,w;
        cin>>a>>b>>w;
        adj[a].emplace_back(b,w);
    }
    int src,negative_cycle=0;
    cin>>src;
    int times=10;
    long long tt=0;
    while(times--){
        vector<int> dis(n+1,INF);
        dis[src]=0;

        auto start = std::chrono::high_resolution_clock::now();
        for(int i=1;i<=n-1;i++){
            for(int j=1;j<=n;j++){
                if(d[j]==INF) continue;
                for(auto [v,w]:adj[j]){
                    d[v]=min(d[v],d[j]+w);
                }
            }
        }   

        for(int j=0;j<m;j++){
            if(d[j]==INF) continue;
            for(auto [v,w]:adj[j]){
                if(d[v]>d[j]+w) negative_cycle=1;
            }
        }
        auto stop = std::chrono::high_resolution_clock::now();
	    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        tt+=(long long)duration.count();
    }
	cout<<n<<" "<<tt/10<<"\n";
}