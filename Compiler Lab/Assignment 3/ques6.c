//character = '~' is used as epsilon

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TNUM 128

typedef struct production{
    char* str;
    int len;
}production;

int isNT(char c) {
    return c >= 'A' && c <= 'Z';
}

int nonterminal[26],terminal[TNUM],first[26][TNUM],follow[26][TNUM];

void add_first_to_first(char A,char B){
    for(int i=0;i<TNUM;i++){
        if(i=='~') continue;
        first[A-'A'][i]=first[A-'A'][i]||first[B-'A'][i];
    }
}

void add_first_to_follow(char A,char B){
    for(int i=0;i<TNUM;++i){
        if(i=='~') continue;
        follow[A-'A'][i]=follow[A-'A'][i]||first[B-'A'][i];
    }
}

void add_follow_to_follow(char A,char B){
    for(int i=0;i<TNUM;++i){
        if(i=='~') continue;
        follow[A-'A'][i]=follow[A-'A'][i]||follow[B-'A'][i];
    }
}

void find_first(production *prod,int num){
    int t=0;
    while(t<num){
        for(int i=0;i<num;++i){
            for(int j=3;j<prod[i].len;++j){
                char ch=prod[i].str[j];
                if(isNT(ch)){
                    add_first_to_first(prod[i].str[0],ch);
                    if(first[ch-'A']['~']) continue;
                }else{
                    first[prod[i].str[0]-'A'][ch]=1;
                }
                break;
            }
        }
        t++;
    }
}

void find_follow(production *prod,int num){
    int t=0;
    while(t<num){
        for(int k=0;k<26;k++){
            if(!nonterminal[k]) continue;
            char nt=k+'A';
            for(int i=0;i<num;i++){
                for(int j=3;j<prod[i].len;++j){
                    fflush(0);
                    if(nt==prod[i].str[j]){
                        int x;
                        for(x=j+1;x<prod[i].len;x++){
                            fflush(0);
                            char ch=prod[i].str[x];
                            if(isNT(ch)){
                                add_first_to_follow(nt,ch);
                                if(first[ch-'A']['~']) continue;
                            }else{
                                follow[nt-'A'][ch]=1;
                            }
                            fflush(0);
                            break;
                        }
                        if(x==prod[i].len) add_follow_to_follow(nt,prod[i].str[0]); 
                    }
                }
            }
        }
        t++;
    }
}

int main(){
	int num_of_prod,maxprod,idx=0,j;
    printf("Enter the number of production rules: ");
    scanf("%d",&num_of_prod);
    maxprod=num_of_prod;

    production* prod=malloc(maxprod*sizeof(production));
    
    char buff[256],temp[256];
    getchar();

    for(int i=0;i<num_of_prod;i++){
        printf("\nEnter the %d production: ",i+1);
        fgets(buff,256,stdin);
        j=0;
        nonterminal[buff[0]-'A']=1;
        for(int k=0;k<strlen(buff)-1;k++){
            if(buff[k]=='|'){
                prod[idx].str=malloc((j+1)*sizeof(char));
                for(int len=0;len<j;len++) prod[idx].str[len]=temp[len];

                idx++;
                if(idx>=maxprod){
                    maxprod+=maxprod;
                    prod=realloc(prod,maxprod*sizeof(production));
                    if(!prod){
                        printf("memory allocation error, exiting!!\n");
                        exit(1);
                    }
                }
                prod[idx-1].str[j]='\0';
                prod[idx-1].len=j;
                temp[0]=prod[idx-1].str[0];
                temp[1]='-';
                temp[2]='>';
                j=3;
            }else{
                temp[j]=buff[k];
                j++;
                if(!isNT(buff[k]) && buff[k]!='-' && buff[k]!='>'){
                    terminal[buff[k]]=1;
                }
            }
        }
        
        prod[idx].str=malloc((j+1)*sizeof(char));
        for(int len=0;len<j;len++) prod[idx].str[len]=temp[len];
        prod[idx].str[j]='\0';
        prod[idx].len=j;

        idx++;
        if(idx>=maxprod){
            maxprod+=maxprod;
            prod=realloc(prod,maxprod*sizeof(production));
            if(!prod){
                printf("memory allocation error, exiting!!\n");
                exit(1);
            }
        }
    }
    prod[idx].len=0;

    find_first(prod,idx);

    follow[prod[0].str[0]-'A']['$']=1;
    find_follow(prod,idx);

    for(int i=0;i<26;i++){
        if(nonterminal[i]){
            printf("\nFOLLOW of %c: {",i+'A');
            for(int j=0;j<TNUM;j++){
                if(follow[i][j]) printf(" %c,",j);
            }
            printf(" }");
        }
    }
	return 0;
}