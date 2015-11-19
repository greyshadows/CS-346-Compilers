#ifndef _dfa_h
#define _dfa_h 

#include "state.h"
#include "enfa.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <string>


std::string InfixToPostfix(std::string);

namespace znck {
	using namespace std;

	int is_final_state(vector<state *>);
	int in_array(vector<vector<state *> >, vector<state *>);
	vector<state *> closure(vector<state *>, int);
	vector<vector<int> > dfa_build(enfa);
	vector<vector<int> > min_dfa(vector<vector<int> >);
}

#endif