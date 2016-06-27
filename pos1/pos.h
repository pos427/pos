#pragma once
#include "stdafx.h"

class Pos
{
public:
	void DoPos(Report report)
	{
		cout << "***�̵깺���嵥***" << endl;
		for (ItemGroup itemGroup : report.getItemGroupies())
		{
			cout << "���ƣ�" << itemGroup.groupName() << "��" <<
				"������" << itemGroup.groupSize() << itemGroup.groupUnit() << "��" <<
				"���ۣ�" << setprecision(2) << fixed << itemGroup.groupPrice() << "(Ԫ)" << "��" <<
				"С�ƣ�" << itemGroup.subTotal() << "(Ԫ)" << endl;

		}
		if (report.hasPromotion()) {
			cout << "----------------------" << endl;
			cout << "����������Ʒ��" << endl;
			for (ItemGroup itemGroup : report.getItemGroupies())
			{
				if (itemGroup.groupPromotion())
				{
					cout << "���ƣ�" << itemGroup.groupName() << "��" << "������" << 1 << itemGroup.groupUnit() << endl;
				}

			}
		}
		cout << "----------------------" << endl;
		cout << "�ܼƣ�" << report.getTotal() << "(Ԫ)" << endl;

		double saving = report.getSaving();
		if (saving > 0)
		{
			cout << "��ʡ��" << saving << "(Ԫ)" << endl;
		}
		cout << "**********************" << endl;
	}
};
