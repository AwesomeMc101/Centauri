#include <vector>
#include <string>
#include "stack.hpp"

class Callstack {
private:
	std::vector<Call> stack;
public:
	void push(Call);
	void call_top(Stack*, Heap*);
	int gettop_args();
};
