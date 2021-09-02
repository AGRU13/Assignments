#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,pos=-1,key=-1,left,right;
	cin>>n;
	int* arr=(int*)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++) cin>>arr[i];
	auto start = std::chrono::high_resolution_clock::now();
	for(int j=0;j<10;j++){
		left=0,right=n-1;
		while(left<=right){
			if(arr[left]==key){
				pos=left;
				break;
			}
			if(arr[right]==key){
				pos=right;
				break;
			}
			left++;
			right--;
		}	
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	cout<<n<<" "<<(long long)duration.count()/10<<"\n";
	return 0;
}
