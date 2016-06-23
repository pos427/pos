#include "stdafx.h"

class Report{
private:
	list<ItemGroup> itemGroupies;
public :
    Report(list<ItemGroup> itemGroupies){
        this->itemGroupies = itemGroupies;
    }

    list<ItemGroup> &getItemGroupies() {
        return itemGroupies;
    }

    double getTotal(){
        double result = 0.00;
        for (ItemGroup itemGroup : itemGroupies)
            result += itemGroup.subTotal();
        return result;
    }

    double getSaving(){
        double result = 0.00;
        for (ItemGroup itemGroup : itemGroupies)
            result += itemGroup.saving();
        return result;
    }
};