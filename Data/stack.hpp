#include <vector>
#include "heap.hpp"

class Stack {
private:
	std::vector<CentauriObj> stack{};

	const unsigned int register_size = 4;
	CentauriObj registers[4];
	CentauriObj* r_ptr;
	int rc_ptr;
public:
	void pop(CentauriObj*);
	void push(CentauriObj);

	CentauriObj* get_r(int s = 0); //get last written to register
	CentauriObj* get_a_r(); //get accessible register

	void safe_m_pop(int);
};
