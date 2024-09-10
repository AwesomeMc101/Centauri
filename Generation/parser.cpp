#include "parser.hpp"

static void reset(Parse& pb) {
	pb.data = "";
	pb.pt = NIL;
}

Parsed_Data create_parsed_data(std::vector<Token> ts) {
	Parsed_Data pd;
	pd.original_tokens = ts;

	Branch current_branch;
	Parse parse_buf;
	for (int i = 0; i < ts.size(); i++) {
		if (ts[i].type == NEWLINE && parse_buf.pt != STRING) {
			current_branch.parsed_data.emplace_back(parse_buf);
			reset(parse_buf);

			parse_buf.pt = END;
			current_branch.parsed_data.emplace_back(parse_buf);
			reset(parse_buf);

			pd.tree.push_back(current_branch);
			current_branch.parsed_data.clear();
			continue;
		}
		if (parse_buf.pt == STRING || parse_buf.pt == UNQUOTED_CHARSET || parse_buf.pt == FLOAT) {
			if (ts[i].type == CLOSEPARA) {
				if (parse_buf.pt != NIL) {
					current_branch.parsed_data.emplace_back(parse_buf);
				}
				reset(parse_buf);
				parse_buf.pt = PARAMETER_ENCLOSURE_DECREMENT;
				current_branch.parsed_data.emplace_back(parse_buf);
				reset(parse_buf);
				continue;
			}
			bool breakout = true;
			switch (parse_buf.pt) {
			case STRING:
				if (ts[i].type == QUOTE) {
					current_branch.parsed_data.emplace_back(parse_buf);
					reset(parse_buf);
				}
				else {
					parse_buf.data.push_back(ts[i].c);
				}
				break;
			case UNQUOTED_CHARSET:
				switch (ts[i].type) {
				case CHAR:
					parse_buf.data.push_back(ts[i].c);
					break;
				case OPENPARA:
					parse_buf.pt = FUNCTION_CALL; //Don't break.
					current_branch.parsed_data.emplace_back(parse_buf);
					reset(parse_buf);
					parse_buf.pt = PARAMETER_ENCLOSURE_INCREMENT;
					current_branch.parsed_data.emplace_back(parse_buf);
					reset(parse_buf);
					break;
				default:
					//printf("reset\n");
					if (parse_buf.data == "var") {
						parse_buf.pt = VAR;
					}
					current_branch.parsed_data.emplace_back(parse_buf);
					reset(parse_buf);
					breakout = false;
					break;
				}
				break;
			case FLOAT:
				if (ts[i].type == INT || ts[i].type == PERIOD) {
					parse_buf.data.push_back(ts[i].c);
				}
				else {
					current_branch.parsed_data.emplace_back(parse_buf);
					reset(parse_buf);
					breakout = false;
				}
				break;
			}
			
			if (breakout) {
				continue;
			}
		}

		switch (ts[i].type) {
		case PLUS:
			parse_buf.data = '+';
			parse_buf.pt = ADD;
			current_branch.parsed_data.emplace_back(parse_buf);
			reset(parse_buf);
			break;
		case MINUS:
			parse_buf.data = '-';
			parse_buf.pt = SUB;
			current_branch.parsed_data.emplace_back(parse_buf);
			reset(parse_buf);
			break;
		case ASTERISK:
			parse_buf.data = '*';
			parse_buf.pt = MUL;
			current_branch.parsed_data.emplace_back(parse_buf);
			reset(parse_buf);
			break;
		case FORWARD_SLASH:
			parse_buf.data = '/';
			parse_buf.pt = DIV;
			current_branch.parsed_data.emplace_back(parse_buf);
			reset(parse_buf);
			break;
		case QUOTE:
			parse_buf.pt = STRING;
			break;
		case CHAR:
			parse_buf.data.push_back(ts[i].c);
			parse_buf.pt = UNQUOTED_CHARSET;
			break;
		case INT:
			printf("int\n");
			parse_buf.data.push_back(ts[i].c);
			parse_buf.pt = FLOAT;
			break;
		case SPACE:
			reset(parse_buf);
			break;
		case EQUALS:
			printf("eq");
			break;
		case CLOSEPARA:
			if (parse_buf.pt != NIL) {
				current_branch.parsed_data.emplace_back(parse_buf);
			}
			reset(parse_buf);
			parse_buf.pt = PARAMETER_ENCLOSURE_DECREMENT;
			current_branch.parsed_data.emplace_back(parse_buf);
			reset(parse_buf);
			break;
		}
	}
	if (parse_buf.pt != NIL) {
		current_branch.parsed_data.emplace_back(parse_buf);
		reset(parse_buf);
	}
	pd.tree.push_back(current_branch);
	return pd;
}
