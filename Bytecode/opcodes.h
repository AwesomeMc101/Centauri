typedef enum {
	OP_NIL,

	OP_BACKUPPOP,
	OP_POP,
	OP_PUSHNUM,
	OP_PUSHSTR,

	OP_MOVE, //assign var
	OP_LOAD, //load var

	OP_ADD,
	OP_CONCAT,
	OP_SUB,
	OP_MUL,
	OP_DIV,

	OP_CALL,
	OP_CLOSURE,

} OpCode;
