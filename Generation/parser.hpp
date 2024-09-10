#include "tokenizer.hpp"

typedef enum {
	NIL,
	DEFINE_VARIABLE, //we need to define a var
	DEFINE_FUNCTION, //we need to define a function

	UNQUOTED_CHARSET, //like var foo, there's no quotes
	VAR,

	STRING,
	FLOAT,

	FUNCTION_CALL,
	PARAMETER,
	PARAMETER_ENCLOSURE_INCREMENT,
	PARAMETER_ENCLOSURE_DECREMENT,

	ADD,
	SUB,
	MUL,
	DIV

} Parsed_Type;

typedef struct Parse {
	Parsed_Type pt;
	std::string data;
};

struct Branch {
	std::vector<Parse> parsed_data{};
};

class Parsed_Data {
public:
	std::vector<Token> original_tokens{};
	std::vector<Branch> tree{};
};

Parsed_Data create_parsed_data(std::vector<Token>);
