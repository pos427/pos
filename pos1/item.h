#pragma once
#include "stdafx.h"

class Item
{
private:
	string barcode;
	string name;
	string unit;
	float price;
	double discount;
public:
	Item() {
	}

	Item(string barcode, string name, string unit, double price) {

		this->setBarcode(barcode);
		this->setName(name);
		this->setUnit(unit);
		this->setPrice(price);
		this->setDiscount(1.00);
	}

	Item(string barcode, string name, string unit, double price, double discount) {
		this->setBarcode(barcode);
		this->setName(name);
		this->setUnit(unit);
		this->setPrice(price);
		this->setDiscount(discount);
	}

	string getName() {
		return name;
	}

	string getUnit() {
		return unit;
	}

	double getPrice() {
		return price;
	}

	string getBarcode() { 
		return barcode; 
	}

	double getDiscount() {
		if (discount == 0.00)
			return 1.00;
		return discount;
	}

	void setBarcode(string barcode) {
		this->barcode = barcode;
	}

	void setName(string name) {
		this->name = name;
	}

	void setUnit(string unit) {
		this->unit = unit;
	}

	void setPrice(double price) {
		this->price = price;
	}

	void setDiscount(double discount) {
		this->discount = discount;
	}
};
