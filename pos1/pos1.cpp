// pos1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "item.h"
#include "itemgroup.h"
#include "report.h"
#include "pos.h"
#include "inputparser.h"
int main()
{
	InputParser inputparser("in2.json");
	Report report(inputparser.Parser().getItems());
	Pos pos;

	pos.DoPos(report);
	
	system("pause");
    return 0;
}

