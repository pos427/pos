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
};
