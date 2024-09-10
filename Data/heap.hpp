//picture a world where you can only allocate variables on the heap

#include <map>
#include "object.hpp"

class Heap {
private:
	std::map<std::string, CentauriObj> variable_map{};
public:
	CentauriObj* load(std::string);
	void move(std::string, CentauriObj);
};
