#pragma once
#include "stdafx.h"
#include "user.h"

class ShoppingCart {
	vector<Item> cart;
	User user;
public:
    ShoppingCart(){

    }

    ShoppingCart(User user){
        this->user = user;
    }

	User getUser(){
        return this->user;
    }

	void add(Item it)
	{
		cart.push_back(it);
	}

	vector<Item> getItems() {
		return cart;
	}
};
