#pragma once
#include <iostream>
#include "basicRole.hpp"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"
#include "globalFiles.h"
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Administrator : public BasicRole
{
public:
    Administrator() {}
    Administrator(string name, string pwd)
    {
        this->m_Name = name;
        this->m_Password = pwd;
        loadExistingUsers();
    }

    virtual void operationMenu();
    virtual void logout();

    void addUser();
    void showAllUsers();
    void showComputers();
    void clearAllReservations();
    void saveUserToFile();

    vector<Student> vStu;
    vector<Teacher> vTea;

private:
    void readUsersFromVector(int userType);
    void loadExistingUsers();
    bool isUserExist(int userType, int userID);
};
