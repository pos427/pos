#pragma once
#include "stdafx.h"
#include <time.h>

class Pos
{
public:
	string GetShoppingList(Report report)
	{
		string result;
		stringstream ss;
		ss << "***商店购物清单***" << endl;
		User user = report.getUser();
		vector<ItemGroup> itemgroup=report.getItemGroupies();
		for( int i = 0;i<itemgroup.size();i++){
			if(user.isisVip()==true){
                report.getItemGroupies()[i].setVip(user.isisVip());
            }
		}
		if(user.isisVip()) {
            int newpoint = PointCalc(user.getPoint(),report.getTotal());
            user.setPoint(newpoint);
			ss << "会员编号： "<< user.getId() << "\t会员积分：" << user.getPoint() << "分" << endl;
			ss << "----------------------" << endl;

        }
		if(user.getId()!=""){
			const time_t t = time(NULL);
			struct tm* ct = localtime(&t);
			ss << "打印时间：" << (ct->tm_year+1900) << "年" << (ct->tm_mon+1) << "月" << ct->tm_mday << "日 " << ct->tm_hour << ":" << ct->tm_min << ":" << ct->tm_sec << endl;
			ss << "----------------------" << endl;
		}
		for (ItemGroup itemGroup : itemgroup)
		{
			if(user.isisVip()==true){
                itemGroup.setVip(user.isisVip());
            }
			ss << "名称：" << itemGroup.groupName() << "，" <<
				"数量：" << itemGroup.groupSize() << itemGroup.groupUnit() << "，" <<
				"单价：" << setprecision(2) << fixed << itemGroup.groupPrice() << "(元)" << "，" <<
				"小计：" << itemGroup.subTotal() << "(元)" << endl;

		}
		if (report.hasPromotion()) {
			ss << "----------------------" << endl;
			ss << "挥泪赠送商品：" << endl;
			for (ItemGroup itemGroup : itemgroup)
			{
				if (itemGroup.groupPromotion())
				{
					ss << "名称：" << itemGroup.groupName() << "，" << "数量：" << itemGroup.PromotionNum() << itemGroup.groupUnit() << endl;
				}

			}
		}
		ss << "----------------------" << endl;
		ss << "总计：" << report.getTotal() << "(元)" << endl;

		double saving = report.getSaving();
		if (saving > 0)
		{
			ss << "节省：" << saving << "(元)" << endl;
		}
		ss << "**********************" << endl;
		result = ss.str();
		return result;
	}

	int PointCalc(int point,double price){
        int addpoint = (int)price / 5;
        int result = point;
        if(0<= point && point <= 200){
            result += (1 * addpoint);
        }
        else if(200<point && point<=500){
            result += (3*addpoint);
        }
        else if(500<point){
            result += (5*addpoint);
        }
        return result;
    }
};
