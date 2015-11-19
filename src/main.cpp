#include <iostream>
#include <stack>
#include <queue>
#include "enfa.h"
#include "dfa.h"

using namespace znck;

void bfs(const state *s) {
	bool visited[1000] = {false};
	queue<state *> q;
	q.push((state *)s);
	state *t;
	visited[s->id] = true;
	while(!q.empty()) {
		t = q.front(); q.pop();
		cout << "state: " << t->id << endl;
		cout << "edge:  " << t->edge << endl;
		if (t->next != NULL) {
			cout << "next:  " << t->next->id << endl;
			if (!visited[t->next->id]) q.push(t->next);
			visited[t->next->id] = true;
		}
		if (t->next2 != NULL) {
			cout << "next2: " << t->next2->id << endl;
			if (!visited[t->next2->id]) q.push(t->next2);
			visited[t->next2->id] = true;
		}
		cout << "--------" << endl;
	}
}

int main(void) {
	enfa test, cur, op;
	char ch;
	bool ex = false;
	state *s0, *s1;
	std::stack<enfa> machines;
	std::cerr << "Input:: " ;
	char buffer[300];
	cin.getline(buffer, 300);
	string input = InfixToPostfix(string(buffer)) + "c";
	if (input.length() == 1) {
		cerr << "Error in re" ;
		return -1;
	}
	for(int i = 0; i < input.length(); ++i) {
		ch = input[i];		
		switch(ch) {
			case 'a':
			case 'b':
				s1 = new state;
				s0 = new state((int)ch, s1);
				cur = *(new enfa(s0, s1));
				break;
			case '.':
				assert(machines.size() > 0);
				cur = machines.top(); machines.pop();
				assert(machines.size() > 0);
				op = machines.top(); machines.pop();
				cur = op + cur;
				break;
			case '+':
				assert(machines.size() > 0);
				cur = machines.top(); machines.pop();
				assert(machines.size() > 0);
				op = machines.top(); machines.pop();
				cur = cur | op;
				break;
			case '*':
				assert(machines.size() > 0);
				cur = machines.top(); machines.pop();
				cur = cur.star();
				break;
			default:
				ex = true;
		}
		if (ex) {
			break;
		} else {
			machines.push(cur);	
		}
	}

	// bfs(machines.top().get_start());
	cerr << "states:: " << state::object_counter << endl;
	assert(1 == machines.size());
	std::vector<std::vector<int > > v = dfa_build(machines.top());
	cerr << "states:: " << v.size() << endl;
	using namespace std;
	v = min_dfa(v);
	cerr << "states:: " << v.size() << endl;
	cout << v.size() << endl;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[i].size(); ++j) {
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}