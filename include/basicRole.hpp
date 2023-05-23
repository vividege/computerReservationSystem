#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "reservationStatus.h"
#include "reservationTime.h"
#include "reservation.h"
#include "computerRoom.h"

#define STUDENT 1
#define TEACHER 2
#define ADMIN 3

using namespace std;

class BasicRole
{
public:
    string m_Name;
    string m_Password;
    map<int, Reservation> *mRsv;
    map<int, ComputerRoom> *mComp;
    vector<int> *rChangeCounter;

    virtual void operationMenu() = 0; // different role has different menu after login.
    virtual void logout() = 0;
    void clearScreen()
    {
        cout << "Press ENTER key to continue... ..." << endl;
        cin.ignore().get();
        system("clear");
    }

    void printAllReservations()
    {
        if (0 == mRsv->size())
        {
            cout << "No reservation was created." << endl;
            return;
        }
        for (map<int, Reservation>::iterator it = mRsv->begin(); it != mRsv->end(); it++)
        {
            (*it).second.print();
        }
    }
    void loadReservation(map<int, Reservation> *v, vector<int> *c)
    {
        this->mRsv = v;
        this->rChangeCounter = c;
    }
    void setComputerRoom(map<int, ComputerRoom> *c)
    {
        this->mComp = c;
    }
};