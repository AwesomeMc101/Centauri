#include <vector>
#include <string>

typedef enum {
	CHAR,
	QUOTE,
	INT,
	PERIOD, //for floats

	ASTERISK,
	PLUS,
	MINUS,
	FORWARD_SLASH,
	PERCENT,
	CARET,
	EQUALS,
	
	GT,
	LT,

	SPACE,
	NEWLINE,

	OPENPARA,
	CLOSEPARA,
	OPENBRACKET,
	CLOSEBRACKET
} TokenType;

typedef struct Token {
	TokenType type;
	char c;
};

class Tokenized_Data {
public:
	std::vector<Token> tokens{};
};

Tokenized_Data get_tokens(std::string line);
