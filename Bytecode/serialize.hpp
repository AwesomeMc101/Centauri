#include "parser.hpp"
#include "opcodes.h"



struct Byte {
	OpCode op;
	std::string data;
};

class Serialized_Data {
private:
	std::vector<Byte> bytes{};
	int byte_ptr;
public:
	void serialize(Parsed_Data);
	void write_byte(OpCode, std::string);

	int get_next_byte(Byte*);
};
