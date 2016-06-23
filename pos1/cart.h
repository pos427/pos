#include "stdafx.h"

class ShoppingCart{
	list<Item> cart;
public:
	void add(Item it)
	{
		cart.push_back(it);
	}
};