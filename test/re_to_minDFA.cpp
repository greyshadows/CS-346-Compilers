#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class state {
public:
	static int object_counter;
	int     id;
	int 	edge;		///< Label for edge: character, CLASS, EMPTY or EPSILON
	state 	*next;		///< Next state (or NULL if none)
	state 	*next2;		///< Another next state only if edge is EPSILON
	
	state();
	state(int, state *, state *next2 = NULL);
	bool operator<(const state &) const;
	bool operator>(const state &) const;
	bool operator==(const state &) const;
};

class enfa {
	state *start;
	state *final;
public:
	enfa();						 	///< Default constructor
	enfa(state *, state *);			///< Constructor with given start and final state
	enfa(const enfa &);					///< Copy constructor

	void set_start(const state *);
	const state * get_start(void) const;

	void set_final(const state *);
	const state * get_final(void) const;

	enfa& operator+(const enfa &); 	///< Concatenation of two epsilon-NFAs
	enfa& operator|(const enfa &);	///< Union of two epsilon-NFAs
	enfa& star();					///< Kleen star of an epsilon-NFA
};

#define ED_EPSILON -1
#define ED_EMPTY	-3

int is_final_state(vector<state *>);
int in_array(vector<vector<state *> >, vector<state *>);
vector<state *> closure(vector<state *>, int);
vector<vector<int> > dfa_build(enfa);
vector<vector<int> > min_dfa(vector<vector<int> >);
string InfixToPostfix(string);

/*----------- Main function ---------------*/
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

	//bfs(machines.top().get_start());
	assert(1 == machines.size());
	std::vector<std::vector<int > > v = dfa_build(machines.top());

	using namespace std;
	v = min_dfa(v);
	cout << v.size() << endl;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[i].size(); ++j) {
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
/*----------- Definations -----------------*/
int state::object_counter = 0;

state::state() {
	id = state::object_counter++;
	edge = -3;
	next = NULL;
	next2 = NULL;
}

state::state(int edge, state *next, state *next2) {
	id = state::object_counter++;
	this->edge = edge;
	this->next = next;
	this->next2 = next2;
}

bool state::operator<(const state &b) const {
	return this->id < b.id;
}

bool state::operator>(const state &b) const {
	return this->id > b.id;
}

bool state::operator==(const state &b) const {
	return this->id == b.id;
}

enfa::enfa() {
	start = final = NULL;
}

enfa::enfa(state *s, state *f = NULL) {
	start = s;
	if (NULL != f) {
		final = f;
	} else {
		final = start;
	}
}

enfa::enfa(const enfa &b) {
	start = b.start;
	final = b.final;
}

void enfa::set_start(const state *s) {
	assert(NULL != s);

	start = (state *)s;
}

const state * enfa::get_start(void) const {
	return start;
}

void enfa::set_final(const state *f) {
	assert(NULL != f);
	final = (state *)f;
}
const state * enfa::get_final(void) const {
	return final;
}

/**
 *	Concatenation of two epsilon-NFA
 */
enfa& enfa::operator+(const enfa &b) {
	assert(NULL != final);
	assert(NULL != b.start);

	final->edge = ED_EPSILON;
	final->next = b.start;

	final = b.final;

	return *this;
}

/**
 *	Union of two epsilon-NFA
 */
enfa& enfa::operator|(const enfa &b) {
	assert(NULL != start);
	assert(NULL != final);
	assert(NULL != b.start);
	assert(NULL != b.final);

	state *s0 = new state(ED_EPSILON, start, b.start),
		  *s1 = new state;
	
	final->edge = ED_EPSILON;
	b.final->edge = ED_EPSILON;

	final->next = s1;
	b.final->next = s1;

	start = s0;
	final = s1;

	return *this;
}

/**
 *	Kleen star on an epsilon-NFA
 */
enfa& enfa::star() {
	assert(NULL != start);
	assert(NULL != final);

	state *s1 = new state,
		  *s0 = new state(ED_EPSILON, start, s1);

	final->edge = ED_EPSILON;
	final->next = s1;
	final->next2 = start;

	start = s0;
	final = s1;

	return *this;
}

vector<state *> closure(vector<state *> s, int symbol) {
	bool *visited = new bool[state::object_counter];

	queue<state *> q;
	vector<state *> res;
	state *c;

	for (int i = 0; i < state::object_counter; ++i) {
		visited[i] = false;
	}

	if (ED_EPSILON != symbol) {
		for (int i = 0; i < s.size(); ++i) {
			visited[s[i]->id] = true;
			q.push(s[i]);
			while (!q.empty()) {
				c = q.front(); q.pop();
				if (symbol == c->edge) {
					if (NULL != c->next) {
						q.push(c->next);
						res.push_back(c->next);
					}
					if (NULL != c->next2) {
						q.push(c->next2);
						res.push_back(c->next2);
					}
				}
			}
		}
	} else {
		res.insert(res.begin(), s.begin(), s.end());
	}

	int sz = res.size();

	for (int i = 0; i < sz; ++i) {
		visited[res[i]->id] = true;
		q.push(res[i]);
		while (!q.empty()) {
			c = q.front(); q.pop();
			if (ED_EPSILON == c->edge) {
				if (NULL != c->next) {
					q.push(c->next);
					res.push_back(c->next);
				}
				if (NULL != c->next2) {
					q.push(c->next2);
					res.push_back(c->next2);	
				}
			}
		}
	}

	sort(res.begin(), res.end());

	res.erase( unique( res.begin(), res.end() ), res.end() );

	delete visited;
	return res;
}

int is_final_state(vector<state *> l) {
	for (int i = 0; i < l.size(); ++i) {
		if (l[i]->edge == ED_EMPTY) {
			return 1;
		}
	}
	return 0;
}

int in_array(vector<vector<state *> > haystack, vector<state *> needle) {
	if (0 == needle.size()) {
		return -2;
	}
	for (int i = 0 ; i < haystack.size(); ++i) {
		if (haystack[i].size() == needle.size()) {
			int j;
			for (j = 0; j < needle.size(); ++j) {
				if (haystack[i][j] != needle[j]) {
					break;
				}
			}
			if (j == needle.size()) {
				return i;
			}
		}
	}
	return -1;
}

void printg(vector<vector<int> > groups) {
	for (int i = 0; i < groups.size(); ++i)
	{
		cerr << i << " :: " ;
		for (int j = 0; j < groups[i].size(); ++j)
		{
			cerr << groups[i][j] << "  ";
		}
		cerr << endl;
	}
}

vector<vector<int> > dfa_build(enfa machine) {
	vector<vector<state *> > dfa_states;
	vector<vector<int> > dfa_table;
	vector<state *> cur;
	int index;

	cur.push_back((state *)machine.get_start());
	dfa_states.push_back(closure(cur, ED_EPSILON));
	for (int i = 0; i < dfa_states.size(); ++i) {
		dfa_table.push_back(*(new vector<int>));
		dfa_table[i].push_back(is_final_state(dfa_states[i]));
		for (int j = 'a'; j <= 'b'; ++j) {
			cur.empty();
			cur = closure(dfa_states[i], j);
			index = in_array(dfa_states, cur);
			if (-1 == index) {
				index = dfa_states.size();
				dfa_states.push_back(cur);
			} 
			dfa_table[i].push_back(index);
		}
	}

	// cerr << "DFA table" << endl;
	// printg(dfa_table);

	return dfa_table;
}

int get_group(vector<vector<int> > groups, int s) {
	if (s == -2) return -2;
	for (int i = 0; i < groups.size(); ++i) {
		if (groups[i].end() != find(groups[i].begin(), groups[i].end(), s)) {
			return i;
		}
	}

	cout << "error" << endl;
	return 0;
}

vector<vector<int> > min_dfa(vector<vector<int> > d) {
	vector<vector<int> > groups;
	vector<int> f, nf;
	for (int i = 0; i < d.size(); ++i)
	{
		if (0 == d[i][0]) {
			nf.push_back(i);
		} else {
			f.push_back(i);
		}
	}
	if(nf.size()) {
		if (nf[0] == 0) {
			groups.push_back(nf);
			groups.push_back(f);
		} else {
			groups.push_back(f);
			groups.push_back(nf);
		}
	} else {
		groups.push_back(f);
	}


	// cerr << "minDFA table" << endl;

	int splits = 1;
	while(splits) {
		splits = 0;
		for (int i = 0; i < groups.size(); ++i) {
			vector<int> s1, s2, p1;
			s1.push_back(groups[i][0]);
			p1.push_back(get_group(groups, d[groups[i][0]][1]));
			p1.push_back(get_group(groups, d[groups[i][0]][2]));
			for (int j = 1; j < groups[i].size(); ++j) {
				vector<int> p2;
				for (int k = 1; k < 3; ++k) {
					p2.push_back(get_group(groups, d[groups[i][j]][k]));
				}
				if (p1 == p2) {
					s1.push_back(groups[i][j]);
				} else {
					s2.push_back(groups[i][j]);
				}
			}
			if (s1.size() != groups[i].size()) {
				groups[i] = s1;
				groups.push_back(s2);
				splits++;
				break;
			}
		}
		// cerr << "groups:: " << endl;
		// printg(groups);
		// cerr << endl;
	}

	vector<vector<int> > md;
	for (int i = 0; i < groups.size(); ++i) {
		vector<int> s;
		s.push_back(d[groups[i][0]][0]);
		for (int j = 1; j < 3; ++j){
			s.push_back(get_group(groups, d[groups[i][0]][j]));
		}
		md.push_back(s);
	}

	// printg(md);

	// cerr << endl;

	return md;
}

int priority (char op)
{
    int weight = -1;
    switch(op)
    {
        case '+':
            weight = 1;
            break;
        case '.':
            weight = 2;
            break;
        case '*':
            weight = 3;
    }
    return weight;
}

int HigherPriority(char op1, char op2)
{
    int op1Weight = priority(op1);
    int op2Weight = priority(op2);

    return op1Weight > op2Weight ? true: false;
}


bool Is_operator(char C)
{
    if(C == '+' || C == '.' || C == '*')
        return true;

    return false;
}

bool Is_operand(char C)
{
    if(C == 'a' || C == 'b') return true;
    return false;
}

string InfixToPostfix(string expression)
{
    stack<char> S;
    string postfix = "";
    for(int i = 0;i< expression.length();i++) {

        if(Is_operator(expression[i]))
        {
            while(!S.empty() && S.top() != '(' && HigherPriority(S.top(),expression[i]))
            {
                postfix+= S.top();
                S.pop();
            }
            S.push(expression[i]);
        }
        else if(Is_operand(expression[i]))
        {
            postfix +=expression[i];
        }

        else if (expression[i] == '(')
        {
            S.push(expression[i]);
        }

        else if(expression[i] == ')')
        {
            while(!S.empty() && S.top() != '(') {
                postfix += S.top();
                S.pop();
            }
            S.pop();
        }
    }

    while(!S.empty()) {
        postfix += S.top();
        S.pop();
    }

    return postfix;
}