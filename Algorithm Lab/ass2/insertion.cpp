#include<bits/stdc++.h>
#include<sched.h>
#include<stdbool.h>

using namespace std;

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

  int i,j,n,temp;
  cin>>n;
  int* arr=(int*)malloc(sizeof(int)*n);
  for(i=0;i<n;i++) cin>>arr[i];
  
  auto start = std::chrono::high_resolution_clock::now();
  for(i=1;i<=n;i++){
    temp=arr[i];
    j=i;
    while(arr[j-1]>temp and j>=1){
      arr[j]=arr[j-1];
      j--;
    }
    arr[j]=temp;
  }
  auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	cout<<n<<" "<<(long long)duration.count()/10<<"\n";
  return 0;
}
