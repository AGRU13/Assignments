#include<bits/stdc++.h>
#include<sched.h>
#include<stdbool.h>

using namespace std;

mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
long long rng(long long lim) {
	uniform_int_distribution<long long> uid(0,lim-1);
	return uid(rang);
}

/* This function takes random element as pivot, places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot */
long int partition(int arr[],int low,int high)  
{  
    	int pivot=arr[low+rng(1e9)%(high-low+1)];  
    	int i=(low-1); 		// Index of smaller element  
  	int j;
  			
    	for (j=low;j<=high-1;j++) 
    	{  
        	// If current element is smaller than the pivot  
       		if(arr[j]<pivot) 
       		{
       			i++; // increment index of smaller element  
      			swap(arr[i],arr[j]);  
       		}
    	}
    	swap(arr[i+1],arr[high]);  
    	return (i+1);  
}
		
/* Quicksort function to sort A[0...n-1] */
void Quicksort(int arr[],int low,int high)  
{  
    	if(low<high)  
    	{  
        	/* pi is partitioning index, arr[p] is now at right place */
        	int pi=partition(arr,low,high);  
  
        	// Separately sort elements before partition and after partition  
       		Quicksort(arr,low,pi-1);  
 		Quicksort(arr,pi+1,high);  
    	}  
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

	int i,j,size;
	cin>>size;
	 int* A=(int*)malloc(sizeof(int)*size);
	for(i=0;i<size;i++) cin>>A[i];

  	auto start = std::chrono::high_resolution_clock::now();
	Quicksort(A,0,size-1);
  	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	cout<<size<<" "<<(long long)duration.count()/10<<"\n";
  	return 0;
}
