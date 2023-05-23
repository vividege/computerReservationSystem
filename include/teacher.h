#pragma once
#include <iostream>
#include "basicRole.hpp"

using namespace std;

class Teacher : public BasicRole
{
public:
    Teacher() {}
    Teacher(int empID, string name, string pwd) 
    {
        this->m_EmpID = empID;
        this->m_Name = name;
        this->m_Password = pwd;
    }
    ~Teacher()
    {
        // cout<<"Delete teacher "<<m_EmpID<<endl;
    }

    virtual void operationMenu();
    virtual void logout();
    void showAllReservation();
    void reviewReservation();
    int m_EmpID;

private:
    bool showMyReservations();
};
