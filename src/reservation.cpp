#include "../include/reservation.h"

void Reservation::print()
{
    string d;
    if (1 == getDate())
    {
        d = "Monday";
    }
    else if (2 == getDate())
    {
        d = "Tuesday";
    }
    else if (3 == getDate())
    {
        d = "Wednesday";
    }
    else if (4 == getDate())
    {
        d = "Thursday";
    }
    else
    {
        d = "Friday";
    }

    cout << endl
         << "[RID]: " << this->getRID() << " [Date]: " << d << " [Time]: ";
    // << this->getTime() << " "
    if (this->getTime() == ReservationTime::morning)
    {
        cout << "Morning ";
    }
    else
    {
        cout << "Afternoon ";
    }
    cout << "[StuID]: " << this->getOwnerID() << " [Name]: ";
    cout << this->getOwnerName() << " [Room]: ";
    cout << this->getRoom() << " [Status]: ";
    if (this->getStatus() == ReservationStatus::underReview)
    {
        cout << "UnderReview" << endl;
    }
    else if (this->getStatus() == ReservationStatus::approved)
    {
        cout << "Approved" << endl;
    }
    else if (this->getStatus() == ReservationStatus::rejected)
    {
        cout << "Rejected" << endl;
    }
    else
    {
        cout << "Cancelled" << endl;
    }
    cout << endl;
}
void Reservation::setStatus(ReservationStatus rs)
{
    this->m_RStatus = rs;
}
void Reservation::setOwner(string name, int id)
{
    this->m_OwnerName = name;
    this->m_OwnerID = id;
}
void Reservation::setRoom(int room)
{
    this->m_RoomNo = room;
}
void Reservation::setTime(ReservationTime rt)
{
    this->m_RTime = rt;
}
void Reservation::setDate(int rd)
{
    this->m_RDate = rd;
}
void Reservation::setRID(int id)
{
    this->m_RID = id;
}

ReservationStatus Reservation::getStatus()
{
    return this->m_RStatus;
}
string Reservation::getOwnerName()
{
    return this->m_OwnerName;
}
int Reservation::getOwnerID()
{
    return this->m_OwnerID;
}
int Reservation::getRoom()
{
    return this->m_RoomNo;
}
ReservationTime Reservation::getTime()
{
    return this->m_RTime;
}
int Reservation::getDate()
{
    return this->m_RDate;
}

int Reservation::getRID()
{
    return this->m_RID;
}