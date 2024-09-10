#include "tokenizer.hpp"


Tokenized_Data get_tokens(std::string line) {
	Tokenized_Data t_d;

	for (char c : line) {
		Token tk;
		tk.c = c;
		switch (c) {
		case '+':
			tk.type = PLUS;
			break;
		case '-':
			tk.type = MINUS;
			break;
		case '/':
			tk.type = FORWARD_SLASH;
			break;
		case '*':
			tk.type = ASTERISK;
			break;
		case '^':
			tk.type = CARET;
			break;
		case '%':
			tk.type = PERCENT;
			break;
		case '\n':
			tk.type = NEWLINE;
			break;
		case ' ':
			tk.type = SPACE;
			break;
		case '"':
			tk.type = QUOTE;
			break;
		case '(':
			tk.type = OPENPARA;
			break;
		case ')':
			tk.type = CLOSEPARA;
			break;
		case '>':
			tk.type = GT;
			break;
		case '<':
			tk.type = LT;
			break;
		case '{':
			tk.type = OPENBRACKET;
			break;
		case '}':
			tk.type = CLOSEBRACKET;
			break;
		case '.':
			tk.type = PERIOD;
			break;
		default:
			tk.type = (isdigit(c) ? INT : CHAR);
			break;
		}
		t_d.tokens.emplace_back(tk);
	}

	return t_d;
}
