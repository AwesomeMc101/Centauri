#include "object.hpp"

CentauriObj new_obj(ObjType ot, float f_val) {
	CentauriObj co;
	co.ot = ot;
	co.f_val = f_val;
	return co;
}
CentauriObj new_obj(ObjType ot, std::string s_val) {
	CentauriObj co;
	co.ot = ot;
	co.s_val = s_val;
	return co;
}

Call new_call(std::string s, int v) {
	Call c;
	c.call_identifier = s;
	c.type = v;
	return c;
}
