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
int first_beta[TNUM],table[26][TNUM];

void add_first_to_first(char A,char B){
    for(int i=0;i<TNUM;i++){
        if(i=='~') continue;
        first[A-'A'][i]=first[A-'A'][i]|first[B-'A'][i];
    }
}

void add_first_to_follow(char A,char B){
    for(int i=0;i<TNUM;++i){
        if(i=='~') continue;
        follow[A-'A'][i]=follow[A-'A'][i]|first[B-'A'][i];
    }
}

void add_follow_to_follow(char A,char B){
    for(int i=0;i<TNUM;++i){
        if(i=='~') continue;
        follow[A-'A'][i]=follow[A-'A'][i]|follow[B-'A'][i];
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

void find_first_beta(char *str,int len){
    for(int i=3;i<len;i++){
        if(isNT(str[i])){
            for(int j=0;j<TNUM;j++){
                if(j=='~') continue;
                first_beta[j]=first_beta[j]|first[str[i]-'A'][j];
            }
            if(first[str[i]-'A']['~']) continue;
        }else first_beta[str[i]]=1;
        break;
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

    terminal['$']=1;
    terminal['~']=0;

    int p=0;
    for(int i=0;i<idx;i++){
        if(i!=0 && (prod[i].str[0]!=prod[i-1].str[0])) p++;

        for(int j=0;j<TNUM;j++) first_beta[j]=0;
        find_first_beta(prod[i].str,prod[i].len);

        for(int j=0;j<TNUM;j++){
            if(first_beta[j]&&j!='~') {
                table[p][j]=i+1;
            }
            else if(j=='~' && first_beta[j]){
                for(int k=0;k<TNUM;k++){
                    if(follow[prod[i].str[0]-'A'][k]) table[p][k]=i+1;
                }
            }
        }
    }
    printf("\n\t LL(1) PARSING TABLE\n");
    printf("%-10s", "");
    for(int i=0;i<TNUM;i++){
        if(terminal[i]) printf("%-10c",i);
    }

    p=0;
    for(int i=0;i<idx;i++){
        if(i==0 || (prod[i].str[0]!=prod[i-1].str[0])){
            printf("\n");
            printf("%-10c",prod[i].str[0]);
            for(int j=0;j<TNUM;j++){
                if(table[p][j]) printf("%-10s",prod[table[p][j]-1].str);
                else if(terminal[j]) printf("%-10s","");
            }
            p++;
        }
    }
	return 0;
}