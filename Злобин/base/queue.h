#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "stack.h"

template <class T>
class TQueue : public TStack<T>
{
	int bottom;
	int length;
public:
	TQueue(int _size) : TStack(_size), bottom(0), length(0) {}
	TQueue(const TQueue& _qu) : TStack(_qu.size), bottom(_qu.bottom), length(_qu.length) {}

	bool IsEmpty(void) const { return length == 0; }
	bool IsFull(void) const { return length == size; }

	virtual void Push(const T& Val) {
		if (IsFull()) throw "queue_is_full";
		top = ++top % size;
		pMem[top] = Val;
		length++;
	}
	virtual T Pop(void) {
		if (IsEmpty()) throw "queue_is_empty";
		int tmp = bottom++;
		bottom = bottom % size;
		length--;
		return pMem[tmp];
	}
	virtual T Begin(void) {
		if (IsEmpty()) throw "queue_is_empty";
		return pMem[bottom];
	}
	virtual T End(void) {
		if (IsEmpty()) throw "queue_is_empty";
		return pMem[top];
	}
	int Size(void) { return size; }
	int Length(void) { return length; }
};

#endif
