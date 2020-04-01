// CircularQueue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "sCircularQueue.h"

int wmain(int argv, wchar_t const *argc[])
{
	{
		sCircularQueue queue(32);

		if (queue.ExtractFromOwnPool(4) == false)
			return 0;
		std::cout << "Max " << queue.max << '\n';
		std::cout << "Extracted " << queue.number_of_entries << '\n';
		queue.PutBackFromOwnPool();
		if (queue.ExtractFromOwnPool(4) == false)
			return 0;
		std::cout << "Max " << queue.max << '\n';
		std::cout << "Extracted " << queue.number_of_entries << '\n';
		queue.PutBackFromOwnPool();
		for (int i = 1; i < 39; ++i) {
			if (queue.ExtractFromOwnPool(1) == false) {
				std::cout << "Couldn't extract from pool. " << i << '\n';
				queue.PutBackFromOwnPool();
				break;
			}
			else {
				std::cout << i << '\n';
			}
		}
		std::cout << "Max " << queue.max << '\n';
		std::cout << "Extracted " << queue.number_of_entries << '\n';
		queue.PutBackFromOwnPool();
		std::cout << "Max " << queue.max << '\n';
		std::cout << "Extracted " << queue.number_of_entries << " from pool.\n";
	}
	return 1;
}
