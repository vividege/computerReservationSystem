#include "student.h"

void Student::operationMenu()
{
    int selection = 0;
    while (true)
    {
        cout << "**** Welcome Student [" << this->m_Name << "] back!.******************" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   1. Apply Reservation                 *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   2. Show My Reservation               *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   3. Show All Reservations             *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   4. Cancel Reservation                *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   5. Logout                            *" << endl;
        cout << "*                                                        *" << endl;
        cout << "* Please Enter Your Selection:                           *" << endl;
        cout << "*                                                        *" << endl;
        cout << "**********************************************************" << endl;
        cin >> selection;
        switch (selection)
        {
        case 1:
            //
            applyReservation();
            this->clearScreen();
            break;
        case 2:
            //
            showMyReservation();
            this->clearScreen();
            break;
        case 3:
            //
            showAllReservation();
            this->clearScreen();
            break;
        case 4:
            //
            cancelReservation();
            this->clearScreen();
            break;
        case 5:
            //
            logout();
            return;
        default:
            cout << "Invalid selection." << endl;
            this->clearScreen();
            break;
        }
    }
}
void Student::logout()
{
    cout << "Student [" << this->m_Name << "] logout..." << endl;
    delete this;
}
void Student::applyReservation()
{
    int r_date;
    int tmp_time;
    ReservationTime r_time;
    int room;
    Reservation r;

    cout << "::::Apply reservation::::" << endl;
    cout << "Computer room open day: Monday - Friday." << endl;
    cout << "Input the day for reservation: \n1. Monday, 2. Tuesday, 3. Wednesday, 4. Thursday, 5. Friday" << endl;
    cin >> r_date;
    cout << "Input time for reservation:\n1. morning\n2.afternoon" << endl;
    cin >> tmp_time;
    cout << "Input room for reservation: 1, 2, 3" << endl;
    cin >> room;

    if ((*mComp)[room].m_leftSeats > 0)
    {
        r_time = tmp_time == 1 ? ReservationTime::morning : ReservationTime::afternoon;
        cout << "A reservation for " << this->m_Name << " was created! Waiting for review." << endl;
        r.setRID(mRsv->size() + 1);
        r.setOwner(this->m_Name, this->m_StuID);
        r.setDate(r_date);
        r.setTime(r_time);
        r.setRoom(room);
        r.setStatus(ReservationStatus::underReview);
        r.print();

        // update reservation vector

        mRsv->insert(make_pair(r.getRID(), r));
        (*mComp)[room].m_leftSeats -= 1;
        rChangeCounter->push_back(1);
    }
    else
    {
        cout << "Room [" << room << "] has no seat for reservation. Select another room to reserve." << endl;
    }
}
bool Student::showMyReservation()
{
    bool hasReservation = false;
    cout << ":::::::::: My Reservations ::::::::::" << endl;
    for (map<int, Reservation>::iterator it = mRsv->begin(); it != mRsv->end(); it++)
    {
        if ((*it).second.getOwnerID() == this->m_StuID)
        {
            (*it).second.print();
            hasReservation = true;
        }
    }
    if (!hasReservation)
    {
        cout << "\nYou haven't applied any reservation." << endl;
    }
    return hasReservation;
}
void Student::showAllReservation()
{
    cout << ":::::::::: All Reservations ::::::::::" << endl;
    printAllReservations();
}
void Student::cancelReservation()
{
    cout << ":::::::::: Cancel Reservations ::::::::::" << endl;
    if (!showMyReservation())
    {
        cout << "\nYou don't have a reservation yet.\n";
        return;
    }
    map<int, Reservation>::iterator it;
    int rid = 0;
    while (true)
    {
        cout << "\nPlease input Reservation ID to cancel, input 0 to back:\n";
        cin >> rid;
        if (0 == rid)
        {
            return;
        }
        it = mRsv->find(rid);
        if (it == mRsv->end() || (*it).second.getOwnerID() != this->m_StuID || (*it).second.getStatus() == ReservationStatus::cancelled)
        {
            cout << "Invalid reservation ID or reservation is already cancelled, please confirm and input again:" << endl;
        }
        else
        {
            (*it).second.setStatus(ReservationStatus::cancelled);
            this->rChangeCounter->push_back(1);

            // Update room left seat
            int roomID = (*it).second.getRoom();
            (*mComp->find(roomID)).second.m_leftSeats += 1;

            cout << "Reservation with ID = " << rid << " has been cancelled." << endl;
            return;
        }
    }
}