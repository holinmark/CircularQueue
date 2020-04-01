#pragma once

#include <iostream>
#include <Windows.h>

struct sCircularQueueNode
{
	DWORD data;
	sCircularQueueNode *p_next;

	sCircularQueueNode();
	~sCircularQueueNode();
};

struct sCircularQueuePool
{
	sCircularQueueNode *p_first, *p_last;
	DWORD max;

	sCircularQueuePool(DWORD);
	~sCircularQueuePool();
	operator bool() { return (max > 0); }
	bool ExtractFromPool(void*, DWORD);
	bool ExtractFromOwnPool(DWORD);
	void PutBack(void*);
	void PutBackFromOwnPool();
};

struct sCircularQueue : sCircularQueuePool
{
	sCircularQueueNode *p_first, *p_last;
	DWORD number_of_entries;

	sCircularQueue(DWORD);
	~sCircularQueue();
	bool Insert(DWORD);
	void ShiftLeft(DWORD);
};
