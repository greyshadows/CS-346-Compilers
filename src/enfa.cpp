#include "enfa.h"

using namespace znck;

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