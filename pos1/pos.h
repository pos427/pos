#include "stdafx.h"


class Pos {
public:
	void DoPos(Report report)
	{
		cout << "***�̵깺���嵥***" << endl;
        for (ItemGroup itemGroup : report.getItemGroupies()) {
            cout<< "���ƣ�" << itemGroup.groupName() << "��" <<
                            "������" << itemGroup.groupSize() << itemGroup.groupUnit() <<  "��" <<
                            "���ۣ�" << itemGroup.groupPrice() << "(Ԫ)" << "��" <<
                            "С�ƣ�" << itemGroup.subTotal() << "(Ԫ)" << endl;

        }
       cout<< "----------------------" <<endl;
	   cout<< "�ܼƣ�"<< report.getTotal() << "(Ԫ)" <<endl;

        double saving = report.getSaving();
        if (saving == 0) {
            cout<<"**********************" << endl;
			cout << "��ʡ��"<< saving<<"(Ԫ)"<<endl;
			cout << "**********************" << endl;
        }
	}
};
