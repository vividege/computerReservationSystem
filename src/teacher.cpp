#include "teacher.h"

void Teacher::operationMenu()
{
    int selection = 0;
    while (true)
    {
        cout << "**** Welcome UESTC Employee [" << this->m_Name << "] back!.******************" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   1. Show All Reservations             *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   2. Review and Approve Reservation    *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   3. Logout                            *" << endl;
        cout << "*                                                        *" << endl;
        cout << "* Please Enter Your Selection:                           *" << endl;
        cout << "*                                                        *" << endl;
        cout << "**********************************************************" << endl;
        cin >> selection;
        switch (selection)
        {
        case 1:
            //
            showAllReservation();
            this->clearScreen();
            break;
        case 2:
            //
            reviewReservation();
            this->clearScreen();
            break;
        case 3:
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

void Teacher::logout()
{
    cout << "UESTC Employee [" << this->m_Name << "] logout..." << endl;
    delete this;
}
void Teacher::showAllReservation()
{
    printAllReservations();
}

bool Teacher::showMyReservations()
{
    bool hasReservationToReview = false;
    for (map<int, Reservation>::iterator it = mRsv->begin(); it != mRsv->end(); it++)
    {
        if ((*it).second.getStatus() == ReservationStatus::underReview)
        {
            (*it).second.print();
            hasReservationToReview = true;
        }
    }
    return hasReservationToReview;
}
void Teacher::reviewReservation()
{
    int reservationID = 0;
    int reviewResults = 0;
    if (showMyReservations())
    {
        while (true)
        {
            cout << "Please input the reservation id to review: input 0 to go back" << endl;
            cin >> reservationID;
            if (0 == reservationID)
            {
                return;
            }
            map<int, Reservation>::iterator it = mRsv->find(reservationID);
            if (it == mRsv->end() || (*it).second.getStatus() != ReservationStatus::underReview)
            {
                cout << "Invalid reservation id, please check and input again!" << endl;
            }
            else
            {
                cout << "Reviewing ... ...";
                (*it).second.print();
                cout << "Please select review results: 1. approve, 2. reject, 3. back" << endl;
                cin >> reviewResults;
                if (1 == reviewResults)
                {
                    (*it).second.setStatus(ReservationStatus::approved);
                }
                else if (2 == reviewResults)
                {
                    (*it).second.setStatus(ReservationStatus::rejected);
                }
                this->rChangeCounter->push_back(1);
                return;
            }
        }
    }
    else
    {
        cout << "No reservation needs to be reviewed and approved." << endl;
    }
}