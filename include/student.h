#pragma once
#include <iostream>
#include "basicRole.hpp"
#include "reservation.h"

using namespace std;

class Student : public BasicRole
{
public:
    Student() {}
    Student(int stuID, string name, string pwd)
    {
        this->m_StuID = stuID;
        this->m_Name = name;
        this->m_Password = pwd;
    }
    ~Student() {}

    virtual void operationMenu();
    virtual void logout();

    void applyReservation();
    bool showMyReservation();
    void showAllReservation();
    void cancelReservation();

    int m_StuID;
};
