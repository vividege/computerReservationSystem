#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "reservationTime.h"
#include "reservationStatus.h"
#include "globalFiles.h"
using namespace std;

class Reservation
{
public:
    void print();
    void setStatus(ReservationStatus rs);
    void setOwner(string name, int id);
    void setRoom(int room);
    void setTime(ReservationTime rt);
    void setDate(int rd);
    void setRID(int rid);

    ReservationStatus getStatus();
    string getOwnerName();
    int getOwnerID();
    int getRoom();
    ReservationTime getTime();
    int getDate();
    int getRID();

    string m_OwnerName;
    int m_OwnerID;
    int m_RDate;
    int m_RoomNo;
    int m_RID;
    ReservationTime m_RTime;
    ReservationStatus m_RStatus;
};