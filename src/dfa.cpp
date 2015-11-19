#include "dfa.h"
#include <iostream>

using namespace std;
using namespace znck;

vector<state *> znck::closure(vector<state *> s, int symbol) {
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

int znck::is_final_state(vector<state *> l) {
	for (int i = 0; i < l.size(); ++i) {
		if (l[i]->edge == ED_EMPTY) {
			return 1;
		}
	}
	return 0;
}

int znck::in_array(vector<vector<state *> > haystack, vector<state *> needle) {
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

vector<vector<int> > znck::dfa_build(enfa machine) {
	vector<vector<state *> > dfa_states;
	vector<vector<int> > dfa_table;
	vector<state *> cur;
	int index;

	cur.push_back((state *)machine.get_start());
	dfa_states.push_back(closure(cur, ED_EPSILON));
	for (int i = 0; i < dfa_states.size(); ++i) {
		cerr << i << endl;
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

	cerr << "DFA table" << endl;
	printg(dfa_table);

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

vector<vector<int> > znck::min_dfa(vector<vector<int> > d) {
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


	cerr << "minDFA table" << endl;

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
		cerr << "groups:: " << endl;
		printg(groups);
		cerr << endl;
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

	printg(md);

	cerr << endl;

	return md;
}