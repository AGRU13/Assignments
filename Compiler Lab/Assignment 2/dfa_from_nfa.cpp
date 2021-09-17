/* Its a C++ program
	State starts from 0, and any character other than e can be used as symbols, character 'e' is used to denote epsilon
*/
#include<bits/stdc++.h>

using namespace std;

//Max states this program can work upon = 60

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

void move(vector<int> &states,vector<vector<node>> &nfa,char ch){
	vector<int> new_states(states.size());

	for(int i=0;i<int(states.size());i++){
		if(states[i]){
			for(int j=0;j<int(nfa[i].size());j++){
				if(nfa[i][j].symbol==ch) {
					new_states[nfa[i][j].to]=1;
				}
			}
		}
	}
	states=new_states;
}

void print_dfa(map<long long,vector<node>> &dfa,int initial_state,vector<int> &isfinal,int num_of_states){
	map<long long ,int> mp;
	int curr=0;
	set<long long> final_states;
	for(map<long long,vector<node>>::iterator it=dfa.begin();it!=dfa.end();it++){
		mp[it->first]=curr;
		long long mask=it->first;
		for(int i=0;i<num_of_states;i++){
			if(mask&1<<i and isfinal[i]) {
				final_states.insert(mask);
				break;
			} 
		}
		curr++;
	}
	cout<<"___________________________________________"<<"\n";
	cout<<"| from state\t|with input->state\t|"<<"\n";
	for(map<long long,vector<node>>::iterator it=dfa.begin();it!=dfa.end();it++){
		cout<<"| "<<mp[it->first]<<"          \t|";	
		for(int i=0;i<int((it->second).size());i++){
			cout<<" "<<(it->second)[i].symbol<<"->"<<mp[(it->second)[i].to]<<"  \t";
		}
		cout<<"\n";
	}
	cout<<"___________________________________________"<<endl;
	cout<<"\n\n Initial state for the dfa is :  "<<mp[initial_state];
	cout<<"\nFinal States of the dfa : ";
	for(set<long long>::iterator it=final_states.begin();it!=final_states.end();it++) cout<<mp[*it]<<" ";
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

	set<char> symbols;

	cout<<"\nEnter the transitons in the format: state state character (character 'e' is used to denote 'epsilon')\n";
	for(int i=0;i<num_of_transitions;i++){
		int st,en;
		char ch;
		cin>>st>>en>>ch;
		node temp;
		temp.symbol=ch;
		temp.to=en;
		nfa[st].push_back(temp);
		symbols.insert(ch);
	}

	map<long long,vector<node>> dfa;

	stack<long long> st;
	vector<int> states(num_of_states);
	states[initial_state]=1;
	find_closure(states,nfa);
	long long mask=0;
	for(int i=0;i<num_of_states;i++){
		if(states[i]) mask|=1<<i;
	}

	initial_state=mask;
	st.push(mask);
	while(!st.empty()){
		long long temp=st.top();
		dfa[temp]=vector<node>();
		st.pop();
		for(set<char>::iterator it=symbols.begin();it!=symbols.end();it++){
			if(*it=='e') continue;
			states=vector<int>(num_of_states);
			for(int i=0;i<num_of_states;i++){
				if(temp&1<<i) states[i]=1;
			}
			move(states,nfa,*it);
			find_closure(states,nfa);
			mask=0;
			for(int i=0;i<num_of_states;i++){
				if(states[i]) mask|=1<<i;
			}
			if(dfa.find(mask)==dfa.end()){
				st.push(mask);
			}

			node curr;
			curr.symbol=*it;
			curr.to=mask;
			dfa[temp].push_back(curr);
		}
	}	

	print_dfa(dfa,initial_state,isfinal,num_of_states);
	return 0;
}