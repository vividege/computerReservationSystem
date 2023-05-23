#pragma once
#include <iostream>
#include <string>
#include <map>
#include "globalFiles.h"
#include "basicRole.hpp"
#include "computerRoom.h"

using namespace std;

class ReservationManager
{
public:
    void start();

    map<int, Reservation> m_MapAllReservations;
    vector<int> m_VRevChangeCounter;
    map<int, ComputerRoom> m_MapComputers;

private:
    void showMenu();
    void clearScreen();
    void login(int userType);
    bool validateUser(int userType, string username, string passwd, int id = 0);
    void saveReservations();
    void loadReservations();
    void getComputerRooms();
    void saveComputerRooms();
};