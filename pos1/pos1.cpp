// pos1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "item.h"
#include "itemgroup.h"
#include "report.h"
#include "pos.h"
#include "inputparser.h"
int main(int argc,char * argv[])
{
	switch (argc)
	{
	case 2:
		{
			InputParser inputparser(argv[1]);
			Report report(inputparser.Parser().getItems());
			Pos pos;
			pos.DoPos(report);
			break;
		}
	case 3:
		{
			InputParser inputparser(argv[1], argv[2]);
			ShoppingCart cart = inputparser.parser();
			Report report(cart.getItems());
			Pos pos;
			pos.DoPos(report);
			break;
		}
	default:
		break;
	}
	system("pause");
    return 0;
}

