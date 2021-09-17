#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 20

int main(){
	char terminals[SIZE],non_terminals[SIZE];
	printf("\nEnter the set of terminals : ");
	gets(terminals);
	printf("\nEnter the set non-terminals: ");
	gets(non_terminals);

	int num; 
	printf("\nEnter the number of production rules for the grammer: ");
	scanf("%d",&num);
	char production[num][SIZE];
	getchar();
	for(int i=1;i<=num;i++){
		printf("\nEnter the %d production rule: ",i);
		gets(production[i-1]);
	}

	char start_symbol;
	printf("\nEnter the stat symbol of the grammer: ");
	scanf("%c",&start_symbol);

	printf("\nGiven Gramme is = ");
	printf("\nSet of non-terminals: ");
	printf("{ ");
	for(int i=0;i<strlen(non_terminals);i++){
		printf("%c, ",non_terminals[i]);
	}
	printf("}");

	printf("\nSet of terminals: ");
	printf("{ ");
	for(int i=0;i<strlen(terminals);i++){
		printf("%c, ",terminals[i]);
	}
	printf("}");

	printf("\nProduction rules: \n");
	for(int i=0;i<num;i++){
		puts(production[i]);
	}

	printf("\nStart Symbol: %c",start_symbol);

	int valid=0;

	for(int i=0;i<strlen(non_terminals);i++){
		valid=0;
		for(int j=0;j<num;j++){
			if(non_terminals[i]==production[j][0]){
				valid=1;
				break;
			}
		}
		if(!valid){
			printf("\n No production exists for the non-terminal: %c",non_terminals[i]);
			return 1;
		}
	}	
	printf("\nProduction rule exists for all non-teminals!!");

	for(int i=0;i<num;i++){
		valid=0;
		for(int j=3;j<strlen(production[i]);j++){
			valid=0;
			if(production[i][j]=='|') continue;
			for(int k=0;k<strlen(non_terminals);k++){
				if(production[i][j]==non_terminals[k]){
					valid=1;
					break;
				}
			}
			if(valid) continue;
			for(int k=0;k<strlen(terminals);k++){
				if(production[i][j]==terminals[k]){
					valid=1;
					break;
				}
			}
			if(!valid){
				printf("\n%c is not in the set of non-terminals: ",production[i][j]);
				return 1;
			}
		}
	}
	printf("\nAll the terminals present in producation rules are also present in the given set of terminals!!");
	return 0;
}