#include<bits/stdc++.h>
#include<sched.h>
#include<stdbool.h>

using namespace std;

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r) 
{ 
    int i,j,k; 
    int n1=m-l+1; 
    int n2=r-m; 
  
    /* create temp arrays */
    int* L=(int*)malloc(sizeof(int)*n1);
    int* R=(int*)malloc(sizeof(int)*n2); 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i=0;i<n1;i++) 
        L[i]=arr[l+i]; 
    for (j=0;j<n2;j++) 
        R[j]=arr[m+1+j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i=0; 
    j=0; 
    k=l; 
    while(i<n1 && j<n2) 
    { 
        if(L[i]<=R[j]) 
        { 
            arr[k]=L[i]; 
            i++; 
        } 
        else
        { 
            arr[k]=R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there are any */
    while(i<n1)
    { 
        arr[k]=L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there are any */
    while(j<n2) 
    { 
        arr[k]=R[j]; 
        j++; 
        k++; 
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

  int i,j,size,curr_size,left_start,mid,right_end;
  cin>>size;
  int* arr=(int*)malloc(sizeof(int)*size);
  for(i=0;i<size;i++) cin>>arr[i];

  auto start = std::chrono::high_resolution_clock::now();
  /* Iterative mergesort function to sort A[0...n-1] */
		// Merge subarrays in bottom up manner. First merge subarrays of 
		// size 1 to create sorted subarrays of size 2, then merge subarrays 
		// of size 2 to create sorted subarrays of size 4, and so on. 
		for (curr_size=1; curr_size<=size-1; curr_size=2*curr_size) 
		{ 
			// Pick starting point of different subarrays of current size 
			for (left_start=0; left_start<size-1; left_start+=2*curr_size) 
			{ 
				// Find ending point of left subarray. mid+1 is starting point of right 
			  mid = min(left_start+curr_size-1,size-1); 
				right_end = min(left_start+2*curr_size-1,size-1); 

				// Merge Subarrays A[left_start...mid] & A[mid+1...right_end] 
				merge(arr,left_start,mid,right_end); 
			} 
		}
		 
  auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	cout<<size<<" "<<(long long)duration.count()/10<<"\n";
  return 0;
}
