#include "serialize.hpp"

static void serialize_type(Serialized_Data* sd, Parse pd, int& i, Branch& c_branch);

static Parse peek(int i, const Branch& branch) {
	if (i+1 < branch.parsed_data.size()) {
		return branch.parsed_data[i + 1];
	}
	else {
		return branch.parsed_data.back();
	}
}

static void write_dual_pop(Serialized_Data* sd) {
	sd->write_byte(OP_POP, "");
	sd->write_byte(OP_POP, "");
}

static void peek_write(Serialized_Data* sd, int i, Branch& branch, bool erase = false, Parsed_Type req = NIL) {
	auto peeked_token = peek(i, branch);
	if (req == NIL || req == peeked_token.pt) {
		serialize_type(sd, peeked_token, i, branch);
		if (erase) {
			if (i + 1 < branch.parsed_data.size()) {
				branch.parsed_data.erase(branch.parsed_data.begin() + i + 1);
			}
			else {
				branch.parsed_data.pop_back();
			}
		}
	}
}

static void serialize_type(Serialized_Data* sd, Parse pd, int& i, Branch& c_branch) {
	auto type = pd.pt;
	auto data = pd.data;
	switch (type) {
	case ADD:
		if (peek(i, c_branch).pt == STRING) {
			peek_write(sd, i, c_branch, true, STRING);
			write_dual_pop(sd);
			sd->write_byte(OP_CONCAT, data);
		}
		else {
			//It can only be one of the two following, but we need to allow for variables.
			peek_write(sd, i, c_branch, true, FLOAT);
			peek_write(sd, i, c_branch, true, UNQUOTED_CHARSET);
			write_dual_pop(sd);
			sd->write_byte(OP_ADD, data);
		}
		break;
	case SUB:
		peek_write(sd, i, c_branch, true, FLOAT);
		peek_write(sd, i, c_branch, true, UNQUOTED_CHARSET);
		write_dual_pop(sd);
		sd->write_byte(OP_SUB, data);
		break;
	case MUL:
		peek_write(sd, i, c_branch, true, FLOAT);
		peek_write(sd, i, c_branch, true, UNQUOTED_CHARSET);
		write_dual_pop(sd);
		sd->write_byte(OP_MUL, data);
		break;
	case DIV:
		peek_write(sd, i, c_branch, true, FLOAT);
		peek_write(sd, i, c_branch, true, UNQUOTED_CHARSET);
		write_dual_pop(sd);
		sd->write_byte(OP_DIV, data);
		break;
	case STRING:
		sd->write_byte(OP_PUSHSTR, data);
		break;
	case FLOAT:
		sd->write_byte(OP_PUSHNUM, data);
		break;
	case FUNCTION_CALL:
		sd->write_byte(OP_CALL, data);
		break;
	case PARAMETER_ENCLOSURE_DECREMENT:
		sd->write_byte(OP_BACKUPPOP, data);
		sd->write_byte(OP_CLOSURE, data);
		break;
	case UNQUOTED_CHARSET:
		sd->write_byte(OP_LOAD, data);
		break;
	case VAR:
		if (peek(i, c_branch).pt == UNQUOTED_CHARSET) {
			peek_write(sd, (i + 2), c_branch, true); //+1 is =sign.
			sd->write_byte(OP_POP, "");
			sd->write_byte(OP_MOVE, peek(i, c_branch).data);
			i++;
		}
		break;
	}
}

void Serialized_Data::serialize(Parsed_Data pd) {
	printf("Serialize\n\n");
	for (Branch& branch : pd.tree) {
		size_t sz = branch.parsed_data.size();
		for (int i = 0; i < sz; i++) {
			std::cout << i << branch.parsed_data[i].data << "\n";
			serialize_type(this, branch.parsed_data[i], i, branch);
			sz = branch.parsed_data.size();
		}
	}
}

void Serialized_Data::write_byte(OpCode op, std::string s) {
	Byte b;
	b.op = op;
	b.data = s;
	bytes.push_back(b);
}

int Serialized_Data::get_next_byte(Byte* byteptr) {
	if (byte_ptr < bytes.size()) {
		*byteptr = bytes[byte_ptr];
		byte_ptr++;
		return 1;
	}
	return 0;
}
