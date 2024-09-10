#include <string>
typedef enum {
	OBJ_FLOAT,
	OBJ_STRING
} ObjType;

struct CentauriObj {
	ObjType ot;
	std::string s_val;
	float f_val;
};

CentauriObj new_obj(ObjType ot, float f_val);
CentauriObj new_obj(ObjType ot, std::string s_val);


#define C_CALL 1
#define U_CALL 2
struct Call {
	int type;
	std::string call_identifier;
};

Call new_call(std::string, int);
