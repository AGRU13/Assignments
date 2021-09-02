#include<bits/stdc++.h>
#include<sched.h>
#include<stdbool.h>

using namespace std;
const int NINF = -2000000000;

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

    int n,i,m,src,dest;
    cin>>n>>m;
    vector<pair<int,int>> adj[n+1];
    for(i=0;i<m;i++){
        int a,int b,int w;
        cin>>a>>b>>w;
        adj[a].EB(b,w);
    }
    cin>>src>>dest;

    int times=10;
    long long tt=0;
    while(times--){
        auto start = std::chrono::high_resolution_clock::now();

        vector<int> order;
        function<int> topsort=[&](){
            vector<int> in(n+1);
            int i;
            for(i=1;i<=n;i++) {
                for(auto u:adj[i]) in[u]++;
            }
            queue<int> q;
            for(i=1;i<=n;i++)
                if(!in[i]) q.push(i);

            while(!q.empty()){
                int temp=q.front();
                q.pop();
                order.EB(temp);
                for(auto u:adj[temp]){
                    in[u]--;
                    if(!in[u]) q.push(u);
                }
            }
            return sz(order)==n;
        };
	
	topsort();

        vector<int> dis(n+1,NINF);
        dis[src]=0;
        for(i=0;i<n;i++){
            int u=order[i];
            if(dis[u]!=NINF){
                for(auto [v,w]:adj[u]){
                    dis[v]=max(dis[v],dis[u]+w);
                }
            }
        }

        // cout<<dis[dest];
        auto stop = std::chrono::high_resolution_clock::now();
	    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        tt+=(long long)duration.count();
    }
	cout<<n<<" "<<tt/10<<"\n";
}