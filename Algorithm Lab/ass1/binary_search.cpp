#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,l,r,mid,pos=-1,key=-1;
	cin>>n;
	int* arr=(int*)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++) cin>>arr[i];
	auto start = std::chrono::high_resolution_clock::now();
	for(int i=0;i<10;i++){
		l=0,r=n-1;
		while(l<=r){
			mid=(l+r)/2;
			if(arr[mid]>key) r=mid-1;
			else if(arr[mid]<key) l=mid+1;
			else{
				pos=mid;
				break;
			}
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	cout<<n<<" "<<(long long)duration.count()/10<<"\n";
	return 0;
}
