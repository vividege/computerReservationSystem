#pragma once

#include <iostream>

class ComputerRoom
{
public:
    ComputerRoom() {}
    ComputerRoom(int id, int MaxCap, int left)
    {
        this->m_roomID = id;
        this->m_maxCap = MaxCap;
        this->m_leftSeats = left;
    }
    int m_roomID;
    int m_maxCap;
    int m_leftSeats;
};