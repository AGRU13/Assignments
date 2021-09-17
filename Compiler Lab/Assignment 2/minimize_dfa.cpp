/*states are number from 0
  symbols are int integer form like 0,1,2,3
  list p[2] stores the sets representing dfa
*/

#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> p[2];

int find_index(int x){
	for(int i=0; i<p[1].size(); i++) {
		for(int j=0; j<p[1][i].size(); j++) {
			if(p[1][i][j] == x) return i;
		}
	}
}

void printf_dfa(vector<vector<int>> &transition_table,int intitial_sate,vector<int>&isfinal){
	int num_of_symbols=transition_table[0].size(),num_of_states=p[1].size();

	cout<<"\nMinimized Dfa table: ";
	cout<<"\n---------------------\n";
	for(int i=0;i<num_of_symbols;i++){
		cout<<"\t"<<i;
	}

	for(int i=0;i<num_of_states;i++){
		cout<<"\n"<<i;
		for(int j=0;j<num_of_symbols;j++){
			cout<<"\t"<<find_index(transition_table[p[1][i][0]][j]);
		}
	}
	cout<<"\nInitial State for the dfa : "<<find_index(intitial_sate);
	set<int> s;
	for(int i=0;i<int(isfinal.size());i++){
		if(!isfinal[i]) continue;
		s.insert(find_index(isfinal[i]));
	}
	cout<<"\nFinal states for the dfa are : ";
	for(set<int>::iterator it=s.begin();it!=s.end();it++){
		cout<<*it<<" ";
	}
}

int main(){
	int num_of_states,num_of_symbols;
	cout<<"Enter the number of states for the dfa: ";
	cin>>num_of_states;
	cout<<"\nEnter the number of symbols: ";
	cin>>num_of_symbols;

	vector<vector<int>> transition_table(num_of_states,vector<int>(num_of_symbols));

	for(int i=0;i<num_of_states;i++){
		cout<<"\nFor the state "<<i<<": ";
		for(int j=0;j<num_of_symbols;j++){
			cout<<"\nand the symbol "<<j<<" the next state is : ";
			cin>>transition_table[i][j];
		}
	}

	int initial_state,num_of_final;
	cout<<"\nEnter the initial state for the dfa: ";
	cin>>initial_state;
	cout<<"\nEnter the number of final states: ";
	cin>>num_of_final;

	vector<int> isfinal(num_of_states);
	cout<<"\nEnter the final states: ";
	for(int i=0;i<num_of_final;i++){
		int temp;
		cin>>temp;
		isfinal[temp]=1;
	}

	vector<int> v[2];
	for(int i=0;i<num_of_states;i++){
		v[isfinal[i]].push_back(i);
	}

	p[0].push_back(v[0]);
	p[0].push_back(v[1]);
	p[1]=p[0];
	int change;
	while(1){
		p[0]=p[1]; //p[0] is the old set , p[1] new set

		for(int i=0;i<p[1].size();i++){
			for(int j=1;j<p[1][i].size();j++){
				change=0;
				for(int k=0;k<num_of_symbols;k++){
					if(find_index(transition_table[p[1][i][j]][k])!=find_index(transition_table[p[1][i][0]][k])){
						change=1;
						break;
					}
				}
				if(!change) continue;

				for(int x=p[0].size();x<p[1].size();x++){
					change=0;
					for(int k=0;k<num_of_symbols;k++){
						if(find_index(transition_table[p[1][i][j]][k])!=find_index(transition_table[p[1][x][0]][k])){
							change=1;
							break;
						}
					}
					if(!change){
						p[1][x].push_back(p[1][i][j]);
						p[1][i].erase(p[1][i].begin()+j);
						break;
					}
				}

				if(change){
					p[1].push_back({p[1][i][j]});
					p[1][i].erase(p[1][i].begin()+j);
				}
			}
		}
		if(p[0].size()==p[1].size()) break;
	}

	printf_dfa(transition_table,initial_state,isfinal);
	return 0;
}