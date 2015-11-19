#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char * argv[]) {
	using namespace std;

	ifstream fin;
	bool select = argc > 1;
	if (select) {
		fin.open(argv[1]);
	} 

	if (!fin.good()) {
		cerr << "Invalid file" << endl;
		exit(-1);
	}

	int n_states;

	(select ? fin : cin) >> n_states;

	assert (n_states > 0);

	int (*dfa)[3] = new int[n_states][3];

	for (int i = 0; i < n_states; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (!fin.good()) {
				cerr << "Invalid dfa table" << endl;
				exit(-1);
			}
			(select ? fin : cin) >> dfa[i][j];
		}
	}

	cout << "Press ctrl + D to exit" << endl;

	string input;
	char buf[256];

	int l = 0;
	while(!cin.eof()) {
		++l;
		cin.getline(buf, 256);
		input = string(buf);
		for (int i = 0; i < input.length(); ++i) {
			int state = 0;
			int j;
			for (j = i; j < input.length(); ++j) {
				if ( !(input[j] == 'a' || input[j] == 'b')) {
					if ( !(input[j] == ' ' || input[j] == '\n')) {
						state = -2;
					}
					break;
				}

				state = dfa[state][input[j] - 'a' + 1];
				if (-2 == state) break;
			}
			if (-2 != state && dfa[state][0] && (0 == i || ' ' == input[i - 1] || '\n' == input[i-1])) {
				cout << "Line:: " << l << " Position:: (" << i << ", " << j-1 << ") Accepted string:: " 
				<< input.substr(i, j - i) << endl;
			}
		}
	}

	return 0;
}