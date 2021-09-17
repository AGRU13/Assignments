#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 20

typedef struct production{
    char* str;
    int len;
}production;

int isNT(char c) {
    return c >= 'A' && c <= 'Z';
}

int nonterminal[26];

int main(){
	int num_of_prod;
    printf("Enter the number of production rules: ");
    scanf("%d",&num_of_prod);

    production prod[26];
    for(int i=0;i<26;i++){
        prod[i].str=NULL;
        prod[i].len=0;
    }

    char buff[256];
    getchar();
    for(int i=0;i<num_of_prod;i++){
        printf("\nEnter production %d :",i+1);
        scanf("%s",buff);
        if(nonterminal[buff[0]-'A']){
            int length=prod[buff[0]-'A'].len+strlen(buff)+1-3;
            prod[buff[0]-'A'].str=realloc(prod[buff[0]-'A'].str,length*sizeof(char));    
            int idx=prod[buff[0]-'A'].len-1,j=3;
            prod[buff[0]-'A'].str[idx]='|';
            idx++;
            while(buff[j]){
                prod[buff[0]-'A'].str[idx]=buff[j];
                idx++;
                j++;
            }
            prod[buff[0]-'A'].str[idx]='\0';
            prod[buff[0]-'A'].len=length;
        }else{
            int length=strlen(buff)+1;
            prod[buff[0]-'A'].str=malloc(length*(sizeof(char)));
            prod[buff[0]-'A'].len=length;
            strcpy(prod[buff[0]-'A'].str,buff);
            nonterminal[buff[0]-'A']=1;
        }
    }

    printf("\nProduction rules after grouping:");
    for(int i=0;i<26;i++){
        if(!prod[i].len) continue;
        printf("\n%s",prod[i].str);
    }
	return 0;
}