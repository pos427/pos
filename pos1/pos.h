#include "stdafx.h"


class Pos {
public:
	void DoPos(Report report)
	{
		cout << "***商店购物清单***" << endl;
        for (ItemGroup itemGroup : report.getItemGroupies()) {
            cout<< "名称：" << itemGroup.groupName() << "，" <<
                            "数量：" << itemGroup.groupSize() << itemGroup.groupUnit() <<  "，" <<
                            "单价：" << itemGroup.groupPrice() << "(元)" << "，" <<
                            "小计：" << itemGroup.subTotal() << "(元)" << endl;

        }
       cout<< "----------------------" <<endl;
	   cout<< "总计："<< report.getTotal() << "(元)" <<endl;

        double saving = report.getSaving();
        if (saving == 0) {
            cout<<"**********************" << endl;
			cout << "节省："<< saving<<"(元)"<<endl;
			cout << "**********************" << endl;
        }
	}
};
