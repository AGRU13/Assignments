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

  int i,j,size;
  cin>>size;
  int* A=(int*)malloc(sizeof(int)*size);
  for(i=0;i<size;i++) 
  	cin>>A[i];
  auto start = std::chrono::high_resolution_clock::now();
  /* Iterative Heapsort function to sort A[0...size-1] */
		// Build the MaxHeap where value of each child is always smaller than value of their parent 		
		for(i=1;i<size;i++)  
    		{ 
        		// if child is bigger than parent 
        		if(A[i]>A[(i-1)/2])  
        		{
            			j=i;
            			// swap child and parent until parent is smaller 
            			while(A[j]>A[(j-1)/2])  
            			{
                			swap(A[j],A[(j-1)/2]);
                			j=(j-1)/2; 
            			} 
        		} 
    		}
		// Heapsort the MaxHeap
		for(i=size-1;i>0;i--) 
    		{ 
        		// swap value of first indexed with last indexed  
        		swap(A[0],A[i]);
      
        		// maintaining heap property after each swapping 
			long int index;        		
			j=0; 

        		do
        		{ 
            			index=(2*j+1);
            			// if left child is smaller than right child, point index variable to right child 
            			if(index<(i-1) and A[index]<A[index+1]) 
                			index++; 
          
            			// if parent is smaller than child then swap parent with child having higher value 
            			if (index<i and A[j]<A[index]) 
                			swap(A[j],A[index]); 
          
            			j=index; 
        		}while(index<i); 
    		}
  auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	cout<<size<<" "<<(long long)duration.count()/10<<"\n";
  return 0;
}
