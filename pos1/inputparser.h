#pragma once
#include "stdafx.h"
#include "item.h"
#include "itemgroup.h"
#include "cart.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
using namespace rapidjson;

class InputParser {
private:
	string indexFile;
	string itemsFile;
public:
	InputParser(string itFileName) {
		itemsFile = itFileName;
	}

	InputParser(string iFileName, string itFileName) {
		indexFile = iFileName;
		itemsFile = itFileName;
	}

	ShoppingCart parser(){
		return BuildShoppingChart(getBoughtItemBarCodes(), getItemIndexes());
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
			Item item(barcode, name, unit, price, discount, promotion);
			ItemIndexes.insert(pair<string, Item>(barcode, item));
		}
		fclose(fp);
		return ItemIndexes;
	}

};
