#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "stack.h"

const int MaxQueueSize = 100;

template <class T>
class TQueue : public TStack
{
	int bottom;
	int length;
public:
	TQueue(int _size = MaxQueueSize) : top(-1), bottom(0), length(0) {
		size = _size;
		if ((size < 1) || (size > MaxQueueSize))
			throw "too_large_or_negative_length";
		pMem = new T[size];
	}
	~TQueue() { delete[] pMem; }

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
		length++;
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
};

#endif
