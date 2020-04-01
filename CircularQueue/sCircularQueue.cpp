#include "sCircularQueue.h"

sCircularQueueNode::sCircularQueueNode()
{
	data = 0;
	p_next = NULL;
}

sCircularQueueNode::~sCircularQueueNode()
{
	data = 0;
	if (p_next) {
		delete p_next;
		p_next = NULL;
	}
}

// ---------------------------------------------------------------------------------------------

sCircularQueuePool::sCircularQueuePool(DWORD maxnumberofentries)
{
	sCircularQueueNode *p_tmp = NULL;

	p_first = NULL;
	p_last = NULL;
	max = 0;
	for (DWORD i = 0; i < maxnumberofentries; ++i) {
		p_tmp = new sCircularQueueNode;
		if (p_tmp) {
			if (p_last) {
				p_last->p_next = p_tmp;
				p_last = p_tmp;
			}
			else {
				p_first = p_tmp;
				p_last = p_first;
			}
			max++;
		}
		else {
			break;
		}
	}
}

sCircularQueuePool::~sCircularQueuePool()
{
	if (p_first) {
		delete p_first;
		p_first = NULL;
		p_last = NULL;
		max = 0;
	}
}

bool sCircularQueuePool::ExtractFromPool(void *p, DWORD amount_to_extract)
{
	sCircularQueue *p_queue = (sCircularQueue*)p;

	if (max > 0) {
		if (amount_to_extract > 0 && amount_to_extract <= max) {
			sCircularQueueNode *p_tmp = p_first;
			DWORD i = 1;

			for (; i < amount_to_extract; ++i) {
				p_tmp = p_tmp->p_next;
			}
			max -= i;
			p_queue->number_of_entries += i;
			if (p_queue->p_first) {
				if (p_tmp) {
					if (p_tmp->p_next != NULL) {
						p_queue->p_last->p_next = p_first;
						p_queue->p_last = p_tmp;
						p_first = p_tmp->p_next;
						p_queue->p_last->p_next = p_queue->p_first;
					}
					else {
						p_queue->p_last->p_next = p_first;
						p_queue->p_last = p_last;
						p_queue->p_last->p_next = p_queue->p_first;
						p_first = NULL;
						p_last = NULL;
					}
				}
			}
			else {
				if (p_tmp) {
					if (p_tmp->p_next != NULL) {
						p_queue->p_first = p_first;
						p_queue->p_last = p_tmp;
						p_first = p_tmp->p_next;
						p_queue->p_last->p_next = p_queue->p_first;
					}
					else {
						p_queue->p_first = p_first;
						p_queue->p_last = p_tmp;
						p_queue->p_last->p_next = p_queue->p_first;
						p_first = NULL;
						p_last = NULL;
					}
				}
			}
			return true;
		}
	}
	return false;
}

bool sCircularQueuePool::ExtractFromOwnPool(DWORD amout_to_extract)
{
	return this->ExtractFromPool(this, amout_to_extract);
}

void sCircularQueuePool::PutBack(void *p)
{
	sCircularQueue *p_queue = (sCircularQueue*)p;

	if (p_queue) {
		if (p_first) {
			if (p_queue->p_last) {
				p_queue->p_last->p_next = p_first;
				p_first = p_queue->p_first;
				p_queue->p_first = NULL;
				p_queue->p_last = NULL;
				max += p_queue->number_of_entries;
				p_queue->number_of_entries = 0;
			}
		}
		else {
			p_first = p_queue->p_first;
			p_last = p_queue->p_last;
			p_last->p_next = NULL;
			max = p_queue->number_of_entries;
			p_queue->number_of_entries = 0;
			p_queue->p_first = NULL;
			p_queue->p_last = NULL;
		}
	}
}

void sCircularQueuePool::PutBackFromOwnPool()
{
	this->PutBack(this);
}

// ----------------------------------------------------------------------------------------------

sCircularQueue::sCircularQueue(DWORD max_number_of_nodes) : sCircularQueuePool(max_number_of_nodes)
{
	p_first = NULL;
	p_last = NULL;
	number_of_entries = 0;
}

sCircularQueue::~sCircularQueue()
{
	if (p_first) {
		p_last->p_next = NULL;
		delete p_first;
		p_first = NULL;
		p_last = NULL;
		number_of_entries = 0;
	}
}

bool sCircularQueue::Insert(DWORD data)
{
	if (ExtractFromOwnPool(1)) {
		p_last->data = data;
		return true;
	}
	return false;
}

void sCircularQueue::ShiftLeft(DWORD amount_to_shift_left)
{
	if (p_first) {
		for (DWORD i = 0; i < amount_to_shift_left; ++i) {
			p_last = p_last->p_next;
		}
		p_last->p_next = p_first;
	}
}
