#pragma once
#include "stdafx.h"
#include "item.h"
#include "itemgroup.h"
#include "cart.h"
#include <assert.h>
class Test {
public :
	void DoTest()
	{
		this->testGetCorrectShoppingListForMultipleItemsWithMultipleTypes();		
		this->testGetCorrectShoppingListForSingleItem();
		this->testGetCorrectShoppingListForTwoSameItems();
		this->testGetCorrectShoppingListWhenDifferentItemHaveSameItemName();
		this->testIfhaveBothPrommotionAndDiscountDoWhat();
		this->testIfhaveBothPrommotionAndDiscountDoWhatCountThree();
		this->testShouldSupportDiscountWhenHavingOneFavourableItem();
		this->testUserVipDiscount();
		cout << "All test Passed" << endl;
	}
private:
	void testGetCorrectShoppingListForSingleItem()
	{
		// given
		Item cokeCola("ITEM000000", "可口可乐", "瓶", 3.00);
		ShoppingCart shoppingCart;
		shoppingCart.add(cokeCola);
		Report report(shoppingCart.getItems());

		// when
		Pos pos;
		string actualShoppingList = pos.GetShoppingList(report);

		// then
		string expectedShoppingList =
			"***商店购物清单***\n名称：可口可乐，数量：1瓶，单价：3.00(元)，小计：3.00(元)\n----------------------\n总计：3.00(元)\n**********************\n";
		assert(actualShoppingList == expectedShoppingList);
	}


	void testGetCorrectShoppingListForTwoSameItems() {
		// given
		ShoppingCart shoppingCart;
		shoppingCart.add(Item("ITEM000000", "可口可乐", "瓶", 3.00));
		shoppingCart.add(Item("ITEM000000", "可口可乐", "瓶", 3.00));
		Report report(shoppingCart.getItems());

		// when
		Pos pos;
		string actualShoppingList = pos.GetShoppingList(report);

		// then
		string expectedShoppingList =
			"***商店购物清单***\n名称：可口可乐，数量：2瓶，单价：3.00(元)，小计：6.00(元)\n----------------------\n总计：6.00(元)\n**********************\n";
		assert(actualShoppingList == expectedShoppingList);
	}


	void testGetCorrectShoppingListForMultipleItemsWithMultipleTypes() {
		// given
		ShoppingCart shoppingCart;
		shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00));
		shoppingCart.add(Item("ITEM000001", "可口可乐", "瓶", 3.00));
		Report report(shoppingCart.getItems());

		// when
		Pos pos;
		string actualShoppingList = pos.GetShoppingList(report);
		// then
		string expectedShoppingList =
			"***商店购物清单***\n名称：雪碧，数量：1瓶，单价：2.00(元)，小计：2.00(元)\n名称：可口可乐，数量：1瓶，单价：3.00(元)，小计：3.00(元)\n----------------------\n总计：5.00(元)\n**********************\n";
		assert(actualShoppingList == expectedShoppingList);
	}


	void testGetCorrectShoppingListWhenDifferentItemHaveSameItemName(){
		// given
		ShoppingCart shoppingCart;
		shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00));
		shoppingCart.add(Item("ITEM000002", "雪碧", "瓶", 3.00));
		Report report(shoppingCart.getItems());

		// when
		Pos pos;
		string actualShoppingList = pos.GetShoppingList(report);

		// then
		string expectedShoppingList =
			"***商店购物清单***\n名称：雪碧，数量：1瓶，单价：2.00(元)，小计：2.00(元)\n名称：雪碧，数量：1瓶，单价：3.00(元)，小计：3.00(元)\n----------------------\n总计：5.00(元)\n**********************\n";
		assert(actualShoppingList == expectedShoppingList);
	}

	void testShouldSupportDiscountWhenHavingOneFavourableItem(){
		// given
		ShoppingCart shoppingCart;
		shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00, 0.8));
		Report report(shoppingCart.getItems());

		// when
		Pos pos;
		string actualShoppingList = pos.GetShoppingList(report);

		// then
		string expectedShoppingList =
			"***商店购物清单***\n名称：雪碧，数量：1瓶，单价：2.00(元)，小计：1.60(元)\n----------------------\n总计：1.60(元)\n节省：0.40(元)\n**********************\n";
		assert(actualShoppingList == expectedShoppingList);
	}



	void testIfhaveBothPrommotionAndDiscountDoWhat(){
		// given
		ShoppingCart shoppingCart;
		shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00, 0.8, true));
		Report report(shoppingCart.getItems());

		// when
		Pos pos;
		string actualShoppingList = pos.GetShoppingList(report);

		// then
		string expectedShoppingList =
			"***商店购物清单***\n名称：雪碧，数量：1瓶，单价：2.00(元)，小计：1.60(元)\n----------------------\n总计：1.60(元)\n节省：0.40(元)\n**********************\n";
		assert(actualShoppingList == expectedShoppingList);
	}



	void testIfhaveBothPrommotionAndDiscountDoWhatCountThree(){
		// given
		ShoppingCart shoppingCart;
		shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00, 0.8, true));
		shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00, 0.8, true));
		shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00, 0.8, true));
		Report report(shoppingCart.getItems());

		// when
		Pos pos;
		string actualShoppingList = pos.GetShoppingList(report);

		// then
		string expectedShoppingList =
			"***商店购物清单***\n名称：雪碧，数量：3瓶，单价：2.00(元)，小计：4.00(元)\n----------------------\n挥泪赠送商品：\n名称：雪碧，数量：1瓶\n----------------------\n总计：4.00(元)\n节省：2.00(元)\n**********************\n";
		assert(actualShoppingList == expectedShoppingList);
	}

	string GetTime(){
		stringstream ss;
		const time_t t = time(NULL);
		struct tm* ct = localtime(&t);
		ss << "打印时间：" << (ct->tm_year+1900) << "年" << (ct->tm_mon+1) << "月" << ct->tm_mday << "日 " << ct->tm_hour << ":" << ct->tm_min << ":" << ct->tm_sec << endl;
		return ss.str();
	}

	 void testUserVipDiscount()
	{
        // given
        User user("USERTEST","Test",true);
        ShoppingCart shoppingCart(user);
        shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00, 0.8,false,0.75));
        shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00, 0.8,false,0.75));
        shoppingCart.add(Item("ITEM000000", "雪碧", "瓶", 2.00, 0.8,false,0.75));

        // when
        Pos pos;
		Report report(shoppingCart.getItems(),shoppingCart.getUser());
        string actualShoppingList = pos.GetShoppingList(report);


        // then
        string expectedShoppingList =
                "***商店购物清单***\n会员编号： USERTEST\t会员积分：0分\n----------------------\n" + GetTime() + 
                        + "----------------------\n"
                        + "名称：雪碧，数量：3瓶，单价：2.00(元)，小计：3.60(元)\n"
                        + "----------------------\n"
                        + "总计：3.60(元)\n"
                        + "节省：2.40(元)\n"
                        + "**********************\n";
        assert(actualShoppingList == expectedShoppingList);
    }
};




