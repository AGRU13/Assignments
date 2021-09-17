//states start from 0 and allowed symbols are alphabets

#include<stdio.h>
#include<string.h>

int main(){
    int num_of_states,num_of_alphabets;
    printf("\nEnter the number of States of the DFA: ");
    scanf("%d",&num_of_states);
    printf("\nEnter the number of symbols: ");
    scanf("%d",&num_of_alphabets);

    int transition_table[num_of_states][num_of_alphabets];

    for(int i=0;i<num_of_states;i++){
        printf("\nFor the state %d",i);
        for(int j=0;j<num_of_alphabets;j++){
            printf("\nand the alphabet %c the next state is : ",('a'+j));
            scanf("%d",&transition_table[i][j]);
        }
    }
    
    int initial_state,num_of_final_states;
    printf("\nEnter the initial state for the dfa: ");
    scanf("%d",&initial_state);
    printf("\nEnter the number of final states: ");
    scanf("%d",&num_of_final_states);

    int final_states[num_of_final_states];
    printf("\nEnter the final states: ");
    for(int i=0;i<num_of_final_states;i++)
        scanf("%d",&final_states[i]);

    printf("\nGiven Transition table for the DFA : \n");
    for(int i=0;i<num_of_states;i++){
        printf("\t%d",i);
    }
    for(int j=0;j<num_of_alphabets;j++){
        printf("\n%c",('a'+j));
        for(int i=0;i<num_of_states;i++)
            printf("\t%d",transition_table[i][j]);
    }

    char string[256];
    int yes=0;
    do{
        printf("\nEnter a string to check if it is accepted by the dfa : ");
        getchar();
        gets(string);
        int curr_state=initial_state,index=0;
        while(string[index]!='\0'){
            if(transition_table[curr_state][string[index]-'a']<0) break;
            curr_state=transition_table[curr_state][string[index]-'a'];
            index++;
        }   

        if(index<strlen(string)) printf("\nGiven string is not accepted by the DFA!!");
        else {
            for(int i=0;i<num_of_final_states;i++){
                if(final_states[i]==curr_state){
                    printf("\nGiven string is accepted by the DFA!!");
                    goto AA;
                }
            }
            printf("\nGiven string not accepted by the DFA!!");
        }
        AA:
        printf("\n Do you want to check another string: (1 for yes, 0 for no): ");
        scanf("%d",&yes);
    }while(yes);
    return 0;
}
