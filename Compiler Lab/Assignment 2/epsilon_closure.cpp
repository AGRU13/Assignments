/* Its a C++ program
	State starts from 0, and any character other than e can be used as symbols, character 'e' is used to denote epsilon
*/
#include<bits/stdc++.h>

using namespace std;

struct node{
	char symbol;
	int to;
};

void find_closure(vector<int> &states,vector<vector<node>> &nfa){
	stack<int> st;
	for(int i=0;i<int(states.size());i++){
		if(states[i]) st.push(i);
	}

	while(!st.empty()){
		int temp=st.top();
		st.pop();
		for(int j=0;j<int(nfa[temp].size());j++){
			if(nfa[temp][j].symbol=='e' and states[nfa[temp][j].to]==0) {
				states[nfa[temp][j].to]=1;
				st.push(nfa[temp][j].to);
			}
		}
	}
}

int main(){
	int num_of_states,num_of_final_states,initial_state,num_of_transitions;
	
	cout<<"\nEnter the number of states in the nfa: ";
	cin>>num_of_states;
	vector<vector<node>> nfa(num_of_states);

	cout<<"\nEnter the initial state of the nfa:  ";
	cin>>initial_state;

	cout<<"\nEnter the number of final states: ";
	cin>>num_of_final_states;
	cout<<"\nNow enter the final states: ";
	vector<int> isfinal(num_of_states);
	for(int i=0;i<num_of_final_states;i++){
		int state;
		cin>>state;
		isfinal[state]=1;
	}

	cout<<"\nEnter the number of transitions for the nfa: ";
	cin>>num_of_transitions;

	cout<<"\nEnter the transitons in the format: state state character (character 'e' is used to denote 'epsilon')\n";
	for(int i=0;i<num_of_transitions;i++){
		int st,en;
		char ch;
		cin>>st>>en>>ch;
		node temp;
		temp.symbol=ch;
		temp.to=en;
		nfa[st].push_back(temp);
	}

	for(int i=0;i<num_of_states;i++){
		cout<<"\n\nEpsilon Closure of state "<<i<<" is = ";
		vector<int> states(num_of_states);
		states[i]=1;
		find_closure(states,nfa);
		cout<<"\n{ ";
		for(int j=0;j<num_of_states;j++){
			if(states[j])
				cout<<j<<", ";
		}
		cout<<"}";
	}
	return 0;
}