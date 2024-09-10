#include "heap.hpp"

static void load_failure_object(CentauriObj* c) {
	c->ot = OBJ_STRING;
	c->s_val = "VAR_INDEX_FAIL";
	c->f_val = 0;
}

CentauriObj* Heap::load(std::string v) {
	if (variable_map.count(v) == 0) {
		CentauriObj* nc = new CentauriObj;
		load_failure_object(nc);
		return nc;
	}
	return (&variable_map[v]);
}
void Heap::move(std::string s, CentauriObj v) {
	variable_map[s] = v;
}
