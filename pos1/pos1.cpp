// pos1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "item.h"
#include "itemgroup.h"
#include "report.h"
#include "pos.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Item item("ITEM000000", "�ɿڿ���", "ƿ", 3.0);
	Item item2("ITEM000001", "�ɿڿ���", "ƿ", 3.0);

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

