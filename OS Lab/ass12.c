#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//LRU algorithm is used to find a page for replacement
int findframe(int *timeofuse,int frames){
    int framenumber=-1,min=INT_MAX;
    for(int i=0;i<frames;i++){
        if(timeofuse[i]<min) min=timeofuse[i],framenumber=i;
    }
    return framenumber;
}

int main(){
    int n,frames,m,counter=0;
    printf("Enter the size of the reference string:");
    scanf("%d",&n);
    int refs[n];
    printf("\nEnter the elements of the reference string: ");
    for(int i=0;i<n;i++) scanf("%d",&refs[i]);
    printf("\nEnter the number of frames:");
    scanf("%d",&frames);
    int memory[frames],timeofuse[frames];
    for(int i=0;i<frames;i++) memory[i]=-1,timeofuse[i]=0;
    int found,pagefault=0;
    for(int i=0;i<n;i++){
        found=0;
        counter++;
        //check if the page already exist in memory
        for(int j=0;j<frames;j++){
            if(memory[j]==refs[i]) {
                timeofuse[j]=counter;
                found=1;
                break;
            }
        }    
        pagefault+=1-found;
        //look for a empty frame if pagefault occurs
        if(found==0){
            for(int j=0;j<frames;j++){
                if(memory[j]==-1) {
                    memory[j]=refs[i];
                    timeofuse[j]=counter;
                    found=1;
                    break;
                }
            }
        }
        // replace a page since no empty frame exist
        if(found==0){
            int framenumber=findframe(timeofuse,frames);
            memory[framenumber]=refs[i];
            timeofuse[framenumber]=counter;
        }
    }

    printf("\nNumber of page faults with frames=%d for the given reference string is : %d",frames,pagefault);
    return 0;
}

/*---------------------------------------------------------------------------------------------
Input-1:
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
3
Output:
Number of page faults with frames=3 for the given reference string is : 12

Input-2:
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
4
Output:
Number of page faults with frames=4 for the given reference string is : 8

---------------------------------------------------------------------------------------------
We can see, as the number of frames increases the number of page faults decreases so 
number of page faults are inversely proportional to memory allocated.*/

