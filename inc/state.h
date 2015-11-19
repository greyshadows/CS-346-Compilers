#ifndef _state_h_
#define _state_h_


#define ED_EPSILON -1
#define ED_EMPTY	-3

#include <iostream>

namespace znck {
	/**
	 *	\brief	class to hold a state of epsilon-NFA
	 *
	 *	This class holds a state of epsilon-NFA along with its outgoing 
	 *	edge symbols and accepted string in case of final state.
	 *	Source: Compiler Design in C by Allen I. Holub from Page 85, Listing 2.20
	 */
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
}

#endif