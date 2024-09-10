#include "vm.hpp"

int main(){

  std::string line =
		R"(print("hello " + "world"))";
  
	Tokenized_Data tok = get_tokens(line); //Tokenize
	Parsed_Data f = create_parsed_data(tok.tokens); //parse
	Serialized_Data bytecode = Serialized_Data(); //create serialized data object
	bytecode.serialize(f); //serialize parsed data
  
	printf("\n\n"); //yk what this does
	execute(&bytecode); //run the bytecode

}
