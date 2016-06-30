#pragma once
#include "stdafx.h"

class User {
private:
	string id;
    string name;
    bool isVip;
    int point;
public:
    User(){
        setId("");
        setName("");
        setisVip(false);
		setPoint(0.0);
    }

    User(string id,string name,bool vip)
    {
        setId(id);
        setName(name);
        setisVip(vip);
		setPoint(0.0);
    }

    string getId() {
        return id;
    }

    void setId(string id) {
        this->id = id;
    }

    string getName() {
        return name;
    }

    void setName(string name) {
        this->name = name;
    }

    bool isisVip() {
        return isVip;
    }

    void setisVip(bool vip) {
        this->isVip = vip;
    }

    int getPoint() {
        return point;
    }

    void  setPoint(int point) {
        this->point = point;
    }
};
