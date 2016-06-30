#pragma once
#include "stdafx.h"
#include "item.h"
#include "itemgroup.h"
#include "cart.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
using namespace rapidjson;

class ItemList{
private:
	string user;
	vector<string> items;

public:
	ItemList(){

	}

	ItemList(string user,vector<string> items){
		setUser(user);
		setItems(items);
	}

	string getUser(){
		return user;
	}

	void setUser(string user){
		this->user = user;
	}

	vector<string> getItems(){
		return items;
	}

	void setItems(vector<string> items){
		this->items = items;
	}
};

class InputParser {
private:
	string indexFile;
	string itemsFile;
	string usersFile;
	int ParserType;
public:
	InputParser(string itFileName) {
		itemsFile = itFileName;
		ParserType = 1;
	}

	InputParser(string iFileName, string itFileName) {
		indexFile = iFileName;
		itemsFile = itFileName;
		ParserType = 2;
	}

	InputParser(string iFileName, string itFileName,string usFileName) {
		indexFile = iFileName;
		itemsFile = itFileName;
		usersFile = usFileName;
		ParserType = 3;
	}

	ShoppingCart parser(){
		if(ParserType==2)
			return BuildShoppingChart(getBoughtItemBarCodes(), getItemIndexes());
		else if(ParserType==3){
			return BuildShoppingChart(getItemList(),getItemIndexes(),getUsers());
		}
	}

	ItemGroup Parser(){
		ItemGroup items;
		FILE* fp = fopen(itemsFile.c_str(), "rb"); // 非Windows平台使用"r"
		char readBuffer[65536];
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		Document d;
		d.ParseStream(is);
		rapidjson::Value::Array a = d.GetArray();
		for (int i =0 ;i<a.Size();i++)
		{
			rapidjson::Value::Object obj = a[i].GetObject();
			string barcode = obj["barcode"].GetString();
			string name = obj["name"].GetString();
			string unit = obj["unit"].GetString();
			float price = obj["price"].GetFloat();
			double discount = 1.0;
			if(obj.HasMember("discount"))
				discount = obj["discount"].GetFloat();
			Item itm(barcode,name,unit,price,discount);
			items.Add(itm);
		}
		return items;
	}
private:
	ShoppingCart BuildShoppingChart(vector<string> barCodes, map<string, Item> itemIndexes) {
		ShoppingCart shoppingCart;
		for (string barcode : barCodes) {
			shoppingCart.add(itemIndexes[barcode]);
		}
		return shoppingCart;
	}

	ShoppingCart BuildShoppingChart(ItemList itemList, map<string, Item> itemIndexes,map<string, User> users) {
        User user = users[itemList.getUser()];
        if(user.getId() == "")
		{
			user.setId(itemList.getUser());
            user.setName(itemList.getUser());
			user.setisVip(false);
		}
        ShoppingCart shoppingCart(user);
        for (string barcode : itemList.getItems()) {
            Item mappedItem = itemIndexes[barcode];
            if(mappedItem.getBarcode() == ""){
                continue;
            }
            Item item(barcode, mappedItem.getName(), mappedItem.getUnit(), mappedItem.getPrice(), mappedItem.getDiscount(),mappedItem.getPromotion(),mappedItem.getVipDiscount());
            shoppingCart.add(item);
        }
        return shoppingCart;
    }

	vector<string> getBoughtItemBarCodes(){
		vector<string> BoughtItemBarCodes;
		FILE* fp = fopen(itemsFile.c_str(), "rb"); // 非Windows平台使用"r"
		char readBuffer[65536];
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		Document d;
		d.ParseStream(is);
		rapidjson::Value::Array a = d.GetArray();
		for (int i =0 ;i<a.Size();i++)
		{
			BoughtItemBarCodes.push_back(a[i].GetString());
		}
		fclose(fp);
		return BoughtItemBarCodes;
	}

	map<string, Item> getItemIndexes(){
		map<string, Item> ItemIndexes;
		FILE* fp = fopen(indexFile.c_str(), "rb"); // 非Windows平台使用"r"
		char readBuffer[65536];
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		Document d;
		d.ParseStream(is);
		for (Value::ConstMemberIterator itr = d.MemberBegin();itr != d.MemberEnd(); ++itr)
		{
			string barcode = itr->name.GetString();
			string name = itr->value["name"].GetString();
			string unit = itr->value["unit"].GetString();
			float price = itr->value["price"].GetFloat();
			double discount = 1.0;
			if(itr->value.HasMember("discount"))
				discount = itr->value["discount"].GetFloat();
			bool promotion = false;
			if (itr->value.HasMember("promotion"))
				promotion = itr->value["promotion"].GetBool();
			double vipDiscount = 1.0;
			if (itr->value.HasMember("vipDiscount"))
				vipDiscount = itr->value["vipDiscount"].GetDouble();
			Item item(barcode, name, unit, price, discount, promotion,vipDiscount);
			ItemIndexes.insert(pair<string, Item>(barcode, item));
		}
		fclose(fp);
		return ItemIndexes;
	}

	ItemList getItemList(){
		ItemList itemlist;
		string userid;
		vector<string> BoughtItemBarCodes;
		FILE* fp = fopen(itemsFile.c_str(), "rb"); // 非Windows平台使用"r"
		char readBuffer[65536];
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		Document d;
		d.ParseStream(is);
		Value::Object itmlst = d.GetObject();
		userid = itmlst["user"].GetString();
		Value::Array a = itmlst["items"].GetArray();
		for (int i =0 ;i<a.Size();i++)
		{
			BoughtItemBarCodes.push_back(a[i].GetString());
		}
		fclose(fp);
		itemlist.setItems(BoughtItemBarCodes);
		itemlist.setUser(userid);
		return itemlist;
    }

	map<string, User> getUsers(){
		map<string, User> ItemIndexes;
		FILE* fp = fopen(usersFile.c_str(), "rb"); // 非Windows平台使用"r"
		char readBuffer[65536];
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		Document d;
		d.ParseStream(is);
		for (Value::ConstMemberIterator itr = d.MemberBegin();itr != d.MemberEnd(); ++itr)
		{
			string userID = itr->name.GetString();
			string name = itr->value["name"].GetString();
			bool isVip = false;
			if(itr->value.HasMember("isVip"))
				isVip= itr->value["isVip"].GetBool();

			int point = 0;
			if(itr->value.HasMember("point"))
				point = itr->value["point"].GetInt();

			User user(userID,name,isVip);
			user.setPoint(point);
			ItemIndexes.insert(pair<string, User>(userID, user));
		}
		fclose(fp);
		return ItemIndexes;
    }
};
