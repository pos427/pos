#pragma once
#include "stdafx.h"

class ItemGroup {
private:
	vector<Item> items;
	bool Vip;
public:
	ItemGroup()
	{
		 Vip = false;
	}

	ItemGroup(vector<Item> items) {
		Vip = false;
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

	bool groupPromotion() {
		if (items.size() >= 3 && items[0].getPromotion()) {
			return true;
		}
		return false;
	}

	int PromotionNum(){
		int itemnum = items.size();
		int promotionnum = itemnum / 3;
		return promotionnum;
	}

	bool getVip(){
        return this->Vip;
    }

	void setVip(bool vip){
        this->Vip = vip;
    }

	double subTotal() {
		double result = 0.00;
		int itemnum = items.size();
		int discountnum = itemnum % 3;
		int promotionnum = itemnum / 3;
		Item item = items[0];
		result = item.getPrice() * itemnum;
		if(groupPromotion()==true){
			result -= item.getPrice() * promotionnum;
			result -= (item.getPrice() * (1 - item.getDiscount() * (Vip==true?item.getVipDiscount():1.0))) * discountnum;
		}
		else{
			result -= (item.getPrice() * (1 - item.getDiscount() * (Vip==true?item.getVipDiscount():1.0))) * itemnum;
		}
		return result;
	}

	double saving() {
		double result = 0.00;
		Item item = items[0];
		result = item.getPrice() * items.size()- subTotal();
		return result;
	}
};
