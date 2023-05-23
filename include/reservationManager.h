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

    map<int, Reservation> vAllReservations;
    vector<int> reservationChangeCounter;
    map<int, ComputerRoom> vCom;

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