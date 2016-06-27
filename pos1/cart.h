#pragma once
#include "stdafx.h"

class ShoppingCart {
	vector<Item> cart;
public:
	void add(Item it)
	{
		cart.push_back(it);
	}

	vector<Item> getItems() {
		return cart;
	}
};
