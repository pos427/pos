// pos1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "item.h"
#include "itemgroup.h"
#include "report.h"
#include "pos.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Item item("ITEM000000", "可口可乐", "瓶", 3.0);
	Item item2("ITEM000001", "可口可乐", "瓶", 3.0);

	list<Item> items;
	items.push_back(item);

	ItemGroup itemgroup(items);
	list<ItemGroup> itemGroupies;
	itemGroupies.push_back(itemgroup);

	Report report(itemGroupies);
	Pos pos;
	

	pos.DoPos(report);
	system("pause");
	return 0;
}

