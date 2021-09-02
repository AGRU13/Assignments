#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,idx,fibm1=1,fibm2=0,fibm,pos=-1,key=-1,offset=-1;
	cin>>n;
	fibm=fibm1+fibm2;
	while(fibm<n){
		fibm2=fibm1;
		fibm1=fibm;
		fibm=fibm1+fibm2;
	}
	int* arr=(int*)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++) cin>>arr[i];
	auto start = std::chrono::high_resolution_clock::now();
	for(int i=0;i<10;i++){
		while(fibm>1){
			idx=min(offset+fibm2,n-1);
			if(arr[idx]<key){
				fibm=fibm1;
				fibm1=fibm2;
				fibm2=fibm-fibm1;
				offset=idx;
			}else if(arr[idx]>key){
				fibm=fibm2;
				fibm1=fibm1-fibm2;
				fibm2=fibm-fibm1;
			}else {
				pos=idx;
				break;
			}
		}
		if(fibm1 and arr[offset+1]==key) pos=offset+1;
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	cout<<n<<" "<<(long long)duration.count()/10<<"\n";
	return 0;
}
