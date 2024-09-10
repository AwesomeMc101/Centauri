#include "callstack.hpp"

#include <iostream>
static void call(Call c, Stack* stk) {
	if (c.type == C_CALL) {
		if (c.call_identifier == "print") {
			auto r1 = stk->get_r();
			switch (r1->ot) {
			case OBJ_FLOAT:
				std::cout << "Print (FLOAT): " << r1->f_val << "\n";
				break;
			case OBJ_STRING:
				std::cout << "Print (STRING): " << r1->s_val << "\n";
				break;
			}
		}
		else if (c.call_identifier == "+") {
			auto r1 = stk->get_a_r();
			auto r2 = stk->get_a_r();

			float nv = r1->f_val + r2->f_val;
			float ov = r1->f_val;
			r1->f_val = nv;
			stk->push(*r1);
			r1->f_val = ov;
		}
	}
}


void Callstack::push(Call c) {
	stack.emplace_back(c);
}
void Callstack::call_top(Stack* stk) {
	if (stack.size()) {
		call(stack.back(), stk);
		stack.pop_back();
	}
}
