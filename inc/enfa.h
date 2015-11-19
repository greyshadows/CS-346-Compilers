#ifndef _enfa_h_
#define _enfa_h_

#include <cassert>
#include "state.h"

namespace znck {
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
}

#endif