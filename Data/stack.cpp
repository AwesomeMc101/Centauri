#include "stack.hpp"
#include <iostream>
void Stack::pop(CentauriObj* coptr) {
	*coptr = stack.back();
	std::cout << "popped: " << coptr->f_val << "\n";
	stack.pop_back();
}
void Stack::push(CentauriObj co) {
	stack.emplace_back(co);
}

CentauriObj* Stack::get_r(int s) {
	if (s == 0) {
		return r_ptr;
	}
	signed int diff = (rc_ptr - s);
	if (diff >= 0) {
		return &registers[diff];
	}
	return &registers[(s % register_size)];
}

CentauriObj* Stack::get_a_r() { /* Accessible register */
	if (r_ptr == nullptr) {
		r_ptr = &registers[0];
		rc_ptr = 0;
	}
	else if (r_ptr == &registers[register_size-1]) {
		r_ptr = &registers[0];
		rc_ptr = 0;
	}
	else
	{
		r_ptr++;
		rc_ptr++;
	}
	return r_ptr;
}
