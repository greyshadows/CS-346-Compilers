#include "state.h"

using namespace znck;

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