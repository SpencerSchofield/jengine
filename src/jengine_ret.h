#ifndef JENGINE_RET_H
#define JENGINE_RET_H

template <typename T>
struct Ret {
	T data;
	bool flag {true};

	operator T() {
		return this->data;
	}

	operator bool() {
		return this->flag;
	}
};

#endif // JENGINE_RET_H
