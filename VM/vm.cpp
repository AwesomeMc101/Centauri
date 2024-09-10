#include "vm.hpp"
#include <iostream>


/* True Arith (ADD)

auto r1 = stk->get_r(); //get ptr to stack registrar 2
	auto r2 = stk->get_r(1); //pointer arith to get stack registrar 1 (assume safe because its a damn language)
	float sum = (r1->f_val + r2->f_val); //add two float values
	CentauriObj* r3 = stk->get_a_r(); //get new registrar
	CentauriObj obj = new_obj(OBJ_FLOAT, sum); //generate a new obj in stack memory
	*r3 = obj; //rewrite the new registrar to the obj value

*/

static void arith(Stack* stk, OpCode a_op) {
	float result = 0;
	switch (a_op) {
	case OP_ADD:
		std::cout << "ARITH ADD: " << stk->get_r()->f_val << " + " << stk->get_r(1)->f_val << "\n";
		result = (stk->get_r()->f_val + stk->get_r(1)->f_val);
		*stk->get_a_r() = new_obj(OBJ_FLOAT, result);
		break;
	case OP_SUB:
		result = (stk->get_r()->f_val - stk->get_r(1)->f_val);
		*stk->get_a_r() = new_obj(OBJ_FLOAT, result);
		break;
	case OP_MUL:
		result = (stk->get_r()->f_val * stk->get_r(1)->f_val);
		*stk->get_a_r() = new_obj(OBJ_FLOAT, result);
		break;
	case OP_DIV:
		result = (stk->get_r()->f_val / (stk->get_r(1)->f_val != 0 ? stk->get_r(1)->f_val : 1)); //Do not allow division by zero!
		*stk->get_a_r() = new_obj(OBJ_FLOAT, result);
		break;
	case OP_CONCAT:
		std::string r = (stk->get_r()->s_val + stk->get_r(1)->s_val);
		*stk->get_a_r() = new_obj(OBJ_STRING, r);
		break;
	}
}

void execute(Serialized_Data* sd) {
	Callstack cstk;
	Stack stk;
	Heap heap;

	Byte cb;
	while (sd->get_next_byte(&cb)) {
		std::cout << "OP_" << cb.op << " -> " << cb.data << "\n";
		switch (cb.op) {
		case OP_PUSHNUM:
			stk.push(new_obj(OBJ_FLOAT, std::stof(cb.data)));
			break;
		case OP_PUSHSTR:
			stk.push(new_obj(OBJ_STRING, cb.data));
			break;
		case OP_ADD:
		case OP_SUB:
		case OP_MUL:
		case OP_DIV:
		case OP_CONCAT:
			arith(&stk, cb.op);
			stk.push(*stk.get_r()); //push new value
			break;
		case OP_POP:
			stk.pop(stk.get_a_r());
			break;
		case OP_CALL:
			cstk.push(new_call(cb.data, C_CALL));
			break;
		case OP_CLOSURE:
			stk.safe_m_pop(cstk.gettop_args());
			cstk.call_top(&stk, &heap);
			break;
		case OP_BACKUPPOP:
			if (stk.get_r() == nullptr) {
				stk.pop(stk.get_a_r());
			}
			break;
		case OP_LOAD: 
			stk.push(*heap.load(cb.data));
			break;
		case OP_MOVE: //assign
			cstk.push(new_call(cb.data, V_CALL));
			break;
		case OP_FLUSH:
			cstk.call_top(&stk, &heap);
			break;
		}
	}
}
