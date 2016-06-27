#pragma once
#include "stdafx.h"

class ItemGroup {
private:
	vector<Item> items;
public:
	ItemGroup()
	{
		 
	}

	ItemGroup(vector<Item> items) {
		this->items = items;
	}

	void Add(Item itm)
	{
		items.push_back(itm);
	}

	vector<Item> &getItems()
	{
		return items;
	}

	string groupName() {
		return items[0].getName();
	}

	int groupSize() {
		return items.size();
	}

	string groupUnit() {
		return items[0].getUnit();
	}

	double groupPrice() {
		return items[0].getPrice();
	}

	double subTotal() {
		double result = 0.00;
		for (Item item : items)
		{
			result += item.getPrice() * item.getDiscount();
		}
		return result;
	}

	double saving() {
		double result = 0.00;
		for (Item item : items)
			result += item.getPrice() * (1 - item.getDiscount());
		return result;
	}
};
