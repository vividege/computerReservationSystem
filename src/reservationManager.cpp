#include "reservationManager.h"
#include <fstream>
#include <string>
#include "student.h"
#include "teacher.h"
#include "administrator.h"

void ReservationManager::start()
{
    loadReservations();
    getComputerRooms();
    this->showMenu();
}
void ReservationManager::showMenu()
{
    int selection;
    while (true)
    {
        cout << "******* Welcome to UESTC Computer Reservation System *****" << endl;
        cout << "*                                                        *" << endl;
        cout << "* Please Enter Your Selection:                           *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   1. Student Login                     *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   2. Teacher Login                     *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   3. Administrator                     *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   4. Exit                              *" << endl;
        cout << "*                                                        *" << endl;
        cout << "**********************************************************" << endl;
        cin >> selection;
        switch (selection)
        {
        case 1:
            // student login
            login(STUDENT);
            break;
        case 2:
            // teacher login
            login(TEACHER);
            break;
        case 3:
            // admin login
            login(ADMIN);
            break;
        case 4:
            // exit system
            saveReservations();
            saveComputerRooms();
            cout << "Looking forward to seeing you again, bye ~~~ :)\n\n"
                 << endl;
            return;
            break;
        case 1024:
            superAdminMenu();
            break;
        default:
            cout << "Invalid selection ~~~ :(" << endl;
            break;
        }
        clearScreen();
    }
    return;
}

void ReservationManager::clearScreen()
{
    cout << "Press ENTER key to continue... ..." << endl;
    cin.ignore().get();
    system("clear");
}

bool ReservationManager::validateUser(int userType, string username, string passwd, int id)
{
    string fileName;
    string fUsername;
    string fPasswd;
    int fId;
    if (STUDENT == userType)
    {
        fileName = STUDENT_FILE;
    }
    else if (TEACHER == userType)
    {
        fileName = TEACHER_FILE;
    }
    else if (ADMIN == userType)
    {
        fileName = ADMIN_FILE;
    }
    ifstream ifs;
    ifs.open(fileName, ios::in);
    if (!ifs.is_open())
    {
        cout << "File \"" << fileName << "\" doesn't exist!" << endl;
        return false;
    }

    if (STUDENT == userType || TEACHER == userType)
    {
        while (ifs >> fId && ifs >> fUsername && ifs >> fPasswd)
        {
            if (fId == id && fUsername == username && fPasswd == passwd)
            {
                ifs.close();
                return true;
            }
        }
    }
    else if (ADMIN == userType)
    {
        while (ifs >> fUsername && ifs >> fPasswd)
        {
            if (fUsername == username && fPasswd == passwd)
            {
                ifs.close();
                return true;
            }
        }
    }
    ifs.close();
    return false;
}

void ReservationManager::login(int userType)
{
    BasicRole *person = NULL;
    string fileName;
    string username;
    string password;
    int id;
    string fUsername;
    string fPasswd;
    int fId;

    // 1. validate user type
    if (userType != STUDENT && userType != TEACHER && userType != ADMIN)
    {
        cout << "Incorrect user type: " << userType << endl;
        return;
    }

    // 2. validate username and password to login
    cout << "Please input username:" << endl;
    cin >> username;
    cout << "Please input password:" << endl;
    cin >> password;
    if (STUDENT == userType)
    {
        cout << "Please input student id:" << endl;
        cin >> id;
        if (validateUser(STUDENT, username, password, id))
        {
            cout << "Student login successfully!\n\n"
                 << endl;
            person = new Student(id, username, password);
            // person->vRsv = &vAllReservations;
            // Show Student menu
            // return;
        }
    }
    else if (TEACHER == userType)
    {
        cout << "Please input UESTC employee id: " << endl;
        cin >> id;
        if (validateUser(TEACHER, username, password, id))
        {
            cout << "Teacher login successfully!\n\n"
                 << endl;
            person = new Teacher(id, username, password);
            // person->vRsv = &vAllReservations;
            // Show Teacher menu
            // return;
        }
    }
    else if (ADMIN == userType)
    {
        if (validateUser(ADMIN, username, password, 0))
        {
            cout << "Administrator login successfully!\n\n"
                 << endl;
            person = new Administrator(username, password);
            // Show Admin menu
            // return;
        }
    }
    if (person == NULL)
    {
        cout << "Fail to login :(" << endl;
        return;
    }
    else
    {
        // show menu
        this->clearScreen();
        person->setReservation(&m_MapAllReservations, &m_VRevChangeCounter);
        person->setComputerRoom(&m_MapComputers);
        person->operationMenu();
    }
}

void ReservationManager::saveReservations()
{
    if (this->m_VRevChangeCounter.size() == 0)
    {
        cout << "No change was made to reservation" << endl;
        return;
    }
    ofstream ofs;
    if (0 == m_MapAllReservations.size())
    {
        ofs.open(RESERVATION_FILE, ios::trunc);
    }
    else
    {
        ofs.open(RESERVATION_FILE, ios::out);
    }

    if (!ofs.is_open())
    {
        cout << "File \"" << RESERVATION_FILE << "\" open error!" << endl;
        return;
    }
    for (map<int, Reservation>::iterator it = m_MapAllReservations.begin(); it != m_MapAllReservations.end(); it++)
    {
        ofs << (*it).first << " "
            << (*it).second.getDate() << " "
            << (*it).second.getTime() << " "
            << (*it).second.getOwnerID() << " "
            << (*it).second.getOwnerName() << " "
            << (*it).second.getRoom() << " "
            << (*it).second.getStatus() << endl;
    }
    ofs.close();
}

void ReservationManager::loadReservations()
{
    m_MapAllReservations.clear();
    // get all reservations
    Reservation r;
    int r_id;
    int r_date;
    int r_time;
    int r_stuID;
    string r_stuName;
    int r_room;
    int r_status;

    ifstream ifs;
    ifs.open(RESERVATION_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "Open file: " << RESERVATION_FILE << " failed!" << endl;
        return;
    }

    while (ifs >> r_id && ifs >> r_date && ifs >> r_time && ifs >> r_stuID && ifs >> r_stuName && ifs >> r_room && ifs >> r_status)
    {
        r.setRID(r_id);
        r.setDate(r_date);
        if (r_time == 0)
        {
            r.setTime(ReservationTime::morning);
        }
        else
        {
            r.setTime(ReservationTime::afternoon);
        }
        r.setOwner(r_stuName, r_stuID);
        r.setRoom(r_room);
        if (r_status == 0)
        {
            r.setStatus(ReservationStatus::underReview);
        }
        else if (r_status == 1)
        {
            r.setStatus(ReservationStatus::approved);
        }
        else if (r_status == 2)
        {
            r.setStatus(ReservationStatus::cancelled);
        }
        else
        {
            r.setStatus(ReservationStatus::rejected);
        }
        m_MapAllReservations.insert(make_pair(r_id, r));
    }
}

void ReservationManager::getComputerRooms()
{
    this->m_MapComputers.clear();
    ifstream ifs;
    ComputerRoom cr;

    ifs.open(COMPUTER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "File \"" << COMPUTER_FILE << "\" doesn't exist!" << endl;
        return;
    }
    while (ifs >> cr.m_roomID && ifs >> cr.m_maxCap && ifs >> cr.m_leftSeats)
    {
        m_MapComputers.insert(make_pair(cr.m_roomID, cr));
    }
    ifs.close();
}

void ReservationManager::saveComputerRooms()
{
    ofstream ofs;
    if (0 == m_MapComputers.size())
    {
        ofs.open(COMPUTER_FILE, ios::trunc);
    }
    else
    {
        ofs.open(COMPUTER_FILE, ios::out);
    }

    if (!ofs.is_open())
    {
        cout << "File \"" << COMPUTER_FILE << "\" open error!" << endl;
        return;
    }
    for (map<int, ComputerRoom>::iterator it = m_MapComputers.begin(); it != m_MapComputers.end(); it++)
    {
        ofs << (*it).first << " "
            << (*it).second.m_maxCap << " "
            << (*it).second.m_leftSeats << endl;
    }
    ofs.close();
}

void ReservationManager::superAdminMenu()
{
    int passcode = 0;
    while (true)
    {
        cout << "Please input the passcode for super administrator: input [0] to exit." << endl;
        cin >> passcode;
        if (passcode == 4201)
        {
            cout << "This is super admin menu." << endl;
            return;
        }
        else if (passcode == 0)
        {
            return;
        }
        else
        {
            cout << "Invalid passcode for super administrator." << endl
                 << endl;
        }
    }
}