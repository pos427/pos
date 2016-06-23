#include "stdafx.h"

class ItemGroup {
private:
	list<Item> items;
	list<Item>::iterator it;
public:
	ItemGroup(list<Item> items) {
        this->items = items;
    }

	string groupName() {
		it = items.begin();
        return it->getName();
    }

    int groupSize() {
		return items.size();
    }

    string groupUnit() {
		it = items.begin();
        return it->getUnit();
    }

    double groupPrice() {
		it = items.begin();
        return it->getPrice();
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
