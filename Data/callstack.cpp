#include "callstack.hpp"

#include <iostream>
static void call(Call c, Stack* stk, Heap* heap) {
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
	else if (c.type == V_CALL) {
		//variable definition
		heap->move(c.call_identifier, *stk->get_r());
	}
}

int Callstack::gettop_args() {
	if (stack.size()) {
		auto& call = stack.back();
		switch (call.type) {
		case C_CALL:
			if (call.call_identifier == "print") { return 1; }
			break;
		case V_CALL:
			return 1;
			break;
		}
	}
	return 0;
}

void Callstack::push(Call c) {
	stack.emplace_back(c);
}
void Callstack::call_top(Stack* stk, Heap* heap) {
	if (stack.size()) {
		call(stack.back(), stk, heap);
		stack.pop_back();
	}
}
