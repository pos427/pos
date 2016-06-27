#pragma once
#include "stdafx.h"

class Report {
private:
	vector<ItemGroup> itemGroupies;
	map<string, vector<Item>> groupByItemBarCode(vector<Item> items)
	{
		map<string, vector<Item>> map;
		for (Item item : items) {
			string itemBarCode = item.getBarcode();
			map[itemBarCode].push_back(item);
		}
		return map;
	}
public:
	Report(vector<ItemGroup> itemGroupies) {
		this->itemGroupies = itemGroupies;
	}

	Report(vector<Item> items){
		map<string, vector<Item>> mapper = groupByItemBarCode(items);
		map<string, vector<Item>>::iterator  iter;

		for (iter = mapper.begin(); iter != mapper.end(); iter++)
		{
			itemGroupies.push_back(iter->second);
		}
	}

	vector<ItemGroup> &getItemGroupies() {
		return itemGroupies;
	}

	bool hasPromotion() {
		bool result = false;
		for (ItemGroup itemGroup : itemGroupies)
			result |= itemGroup.groupPromotion();
		return result;
	}

	double getTotal() {
		double result = 0.00;
		for (ItemGroup itemGroup : itemGroupies)
			result += itemGroup.subTotal();
		return result;
	}

	double getSaving() {
		double result = 0.00;
		for (ItemGroup itemGroup : itemGroupies)
			result += itemGroup.saving();
		return result;
	}
};
