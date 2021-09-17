/* Its a C++ program
	State starts from 0, and any character other than e can be used as symbols, character 'e' is used to denote epsilon
*/
#include<bits/stdc++.h>

using namespace std;

struct node{
	char symbol;
	int to;
	node *next;
};

int priority(char ch){
	if(ch=='*') return 3;
	else if(ch=='.') return 2;
	else if(ch=='|') return 1;
	return -1;
}

void addconcat(string &reg){
	string nreg;
	for(int i=0;i<int(reg.size()-1);i++){
		nreg+=reg[i];
		if(reg[i]=='.' or reg[i]=='|' or reg[i]=='+' or reg[i]=='(' or reg[i+1]=='|' or reg[i+1]=='+' or reg[i+1]==')' or reg[i+1]=='.' or (reg[i]==')' and reg[i+1]=='*')) continue;
		nreg+='.';
	}	
	nreg+=reg.back();
	reg=nreg;
}

string to_postfix(string &reg){
	stack<char> st;
	string postfix;
	for(int i=0;i<reg.size();i++){
		if((reg[i]>='a' and reg[i]<='z') or (reg[i]>='A' and reg[i]<='Z')) postfix+=reg[i];
		else if(reg[i]=='(') st.push(reg[i]);
		else if(reg[i]==')') {
			while(!st.empty() and st.top()!='('){
				postfix+=st.top();
				st.pop();
			}
			if(st.empty()) return "";
			st.pop();
		}else{
			while(!st.empty() and priority(reg[i])<=priority(st.top())){
				postfix+=st.top();
				st.pop();
			}
			st.push(reg[i]);
		} 
	}
	while(!st.empty()){
		postfix+=st.top();
		st.pop();
	}
	return postfix;
}

node *newnode(char ch,int to){
	node *temp=new node;
	temp->symbol=ch;
	temp->to=to;
	temp->next=NULL;
	return temp;
}

int addconcat(vector<node*> &nfa,vector<vector<int>> &st){
	if(st.size()<2) return 1;
	int s0=st[st.size()-2][1];
	int s1=st[st.size()-1][0];
	int newfirst=st[st.size()-2][0];
	int newlast=st[st.size()-1][1];
	st.pop_back();
	st.pop_back();
	node *curr=nfa[s0],*temp=nfa[s1];
	while(curr->next){
		curr=curr->next;
	}
	while(temp){
		if(temp->to!=-1){
			curr->next=newnode(temp->symbol,temp->to);
			curr=curr->next;
		}
		temp=temp->next;
	}
	temp=nfa[s1];
	curr=temp->next;
	while(curr){
		free(temp);
		temp=curr;
		curr=curr->next;
	}
	free(curr);
	nfa[s1]=newnode('e',-1);
	st.push_back({newfirst,newlast});
	return 0;
}

int addor(vector<node*> &nfa,vector<vector<int>> &st){
	if(st.size()<2) return 1;
	int s10=st[st.size()-2][0],s11=st[st.size()-2][1];
	int s20=st[st.size()-1][0],s21=st[st.size()-1][1];
	int newstart=nfa.size();
	node *temp=newnode('e',s10);
	temp->next=newnode('e',s20);
	nfa.push_back(temp);
	int newlast=nfa.size();
	temp=newnode('e',-1);
	nfa.push_back(temp);
	st.pop_back();
	st.pop_back();
	st.push_back({newstart,newlast});
	node *curr=nfa[s11];
	while(curr->next){
		curr=curr->next;
	}
	curr->next=newnode('e',newlast);
	curr=nfa[s21];
	while(curr->next){
		curr=curr->next;
	}
	curr->next=newnode('e',newlast);
	return 0;
}

int addstar(vector<node*> &nfa,vector<vector<int>> &st){
	int s0=st[st.size()-1][0],s1=st[st.size()-1][1];
	int newstart=nfa.size(),newlast=nfa.size()+1;

	st.pop_back();
	st.push_back({newstart,newlast});
	node *temp=newnode('e',s0);
	temp->next=newnode('e',newlast);
	nfa.push_back(temp);
	temp=newnode('e',-1);
	nfa.push_back(temp);
	node *curr=nfa[s1];
	while(curr->next){
		curr=curr->next;
	}
	curr->next=newnode('e',s0);
	curr=curr->next;
	curr->next=newnode('e',newlast);
	return 0;
}

int table(vector<node*> &nfa){
	cout<<"___________________________________________"<<endl;
	cout<<"| from state\t|with input->state\t|"<<endl;
	for(int i=0;i<nfa.size();i++){
		cout<<"| "<<i+1<<"          \t|";
		node* head = nfa[i];
		while(head!=NULL){
			if(head->to==-1){
				head = head->next;
				continue;
			}
			cout<<" "<<head->symbol<<"->"<<head->to+1<<"  \t";
			head=head->next;
		}
		cout<<endl;
	}
	cout<<"___________________________________________"<<endl;
}

int main(){
	string reg;
	cout<<"Enter the regular expression: \n";
	cin>>reg;
	string postfix;
	vector<node*> nfa;
	addconcat(reg);
	postfix=to_postfix(reg);
	cout<<"postfix expression is = "<<postfix<<"\n";

	vector<vector<int>> st;
	cout<<reg<<"\n";
	for(int i=0;i<postfix.size();i++){
		if((postfix[i]>='a' and postfix[i]<='z') or (postfix[i]>='A' and postfix[i]<='Z')){
			node *s0=newnode(postfix[i],nfa.size()+1);
			node *s1=newnode('e',-1);
			nfa.push_back(s0);
			nfa.push_back(s1);
			st.push_back({int(nfa.size())-2,int(nfa.size())-1});
		}else if(postfix[i]=='*') {
			if(addstar(nfa,st)) {
				cout<<"Invalid";
				return 0;
			}
		}
		else if(postfix[i]=='.') {
			if(addconcat(nfa,st)) {
				cout<<"Invalid";
				return 0;
			}
		}
		else if(postfix[i]=='|') {
			if(addor(nfa,st)){
				cout<<"Invalid";
				return 0;
			}
		}
	}

	cout<<"table for nfa: \n";
	table(nfa);
	cout<<"starting state for the nfa is : "<<st[st.size()-1][0]+1<<"\n";
	cout<<"final state for the nfa is : "<<st[st.size()-1][1]+1<<"\n";
	return 0;
}