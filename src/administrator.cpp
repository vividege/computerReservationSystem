#include "administrator.h"

void Administrator::operationMenu()
{
    int selection = 0;
    while (true)
    {
        cout << "**** Welcome Administrator [" << this->m_Name << "] back!.******************" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   1. Add User                          *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   2. Show All Users                    *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   3. Show All Computers                *" << endl;
        cout << "*                                                        *" << endl;
        cout << "*                   4. Clear All Reservation             *" << endl;
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
            addUser();
            this->clearScreen();
            break;
        case 2:
            //
            showAllUsers();
            this->clearScreen();
            break;
        case 3:
            //
            showComputers();
            this->clearScreen();
            break;
        case 4:
            //
            clearAllReservations();
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

void Administrator::logout()
{
    cout << "Administrator [" << this->m_Name << "] logout..." << endl;
    saveUserToFile();
    delete this;
}

void Administrator::addUser()
{
    int userType = 0;
    int id;
    string userName;
    string passwd;
    string fileName;
    Student s;
    Teacher t;

    cout << "**********  Add User  *************" << endl;
    cout << "*                                 *" << endl;
    cout << "* Please Select User Type To Add: *" << endl;
    cout << "*                                 *" << endl;
    cout << "*     1. Student                  *" << endl;
    cout << "*                                 *" << endl;
    cout << "*     2. Teacher                  *" << endl;
    cout << "*                                *" << endl;
    cout << "***********************************" << endl;
    cin >> userType;
    while (true)
    {
        if (userType == STUDENT)
        {
            cout << "Student ID:" << endl;
            cin >> id;
            if (isUserExist(STUDENT, id))
            {
                cout << "Student with ID: " << id << " already exists." << endl;
                continue;
            }
            cout << "Username:" << endl;
            cin >> userName;
            cout << "Password:" << endl;
            cin >> passwd;

            // update vector
            s.m_StuID = id;
            s.m_Name = userName;
            s.m_Password = passwd;
            vStu.push_back(s);
            cout << "Student " << s.m_Name << " was added successfully!" << endl;
            return;
        }
        else
        {
            cout << "UEST Employee ID:" << endl;
            cin >> id;
            if (isUserExist(TEACHER, id))
            {
                cout << "Teacher with Employee ID: " << id << " already exists." << endl;
                continue;
            }
            cout << "Username:" << endl;
            cin >> userName;
            cout << "Password:" << endl;
            cin >> passwd;

            // update vector
            t.m_EmpID = id;
            t.m_Name = userName;
            t.m_Password = passwd;
            vTea.push_back(t);
            cout << "Teacher " << t.m_Name << " was added successfully!" << endl;
            return;
        }
    }
}
void Administrator::showAllUsers()
{
    // readUserFromFile(STUDENT);
    // readUserFromFile(TEACHER);
    // readUserFromFile(ADMIN);
    int selection = 0;
    cout << "Select users to show:" << endl;
    cout << "1. Show all students" << endl;
    cout << "2. Show all teachers" << endl;
    cin >> selection;
    if (selection != STUDENT && selection != TEACHER)
    {
        cout << "Invalid selection." << endl;
    }
    readUsersFromVector(selection);
}
void Administrator::showComputers()
{
    cout << "::::::::::Computer Room Info::::::::::\n"
         << endl;
    for (map<int, ComputerRoom>::iterator it = mComp->begin(); it != mComp->end(); it++)
    {
        cout << "[Room ID]:\t" << (*it).second.m_roomID
             << "\t [Max Capacity]:\t" << (*it).second.m_maxCap
             << "\t [Left Seats]:\t" << (*it).second.m_leftSeats << endl;
    }
}

void Administrator::clearAllReservations()
{
    int selection = 0;
    cout << "Confirm to clear all reservations:" << endl;
    cout << "1. Clear\n2. Cancel" << endl;
    cin >> selection;
    if (selection == 1)
    {
        ComputerRoom c1(1, 20, 20);
        ComputerRoom c2(2, 50, 50);
        ComputerRoom c3(3, 100, 100);
        this->mRsv->clear();
        this->rChangeCounter->push_back(1);

        // Initialize Computer Room Map
        this->mComp->clear();
        this->mComp->insert(make_pair(c1.m_roomID, c1));
        this->mComp->insert(make_pair(c2.m_roomID, c2));
        this->mComp->insert(make_pair(c3.m_roomID, c3));
        cout << "Clear successfully!" << endl;
    }
    return;
}

void Administrator::saveUserToFile()
{
    string stuFile = STUDENT_FILE;
    string teaFile = TEACHER_FILE;
    ofstream ofs;
    ofs.open(stuFile, ios::out);
    if (!ofs.is_open())
    {
        cout << "File \"" << stuFile << "\" doesn't exist!" << endl;
        return;
    }
    for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
    {
        ofs << (*it).m_StuID << " " << (*it).m_Name << " " << (*it).m_Password << endl;
    }
    ofs.close();

    ofs.open(teaFile, ios::out);
    if (!ofs.is_open())
    {
        cout << "File \"" << teaFile << "\" doesn't exist!" << endl;
        return;
    }
    for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
    {
        ofs << (*it).m_EmpID << " " << (*it).m_Name << " " << (*it).m_Password << endl;
    }
    ofs.close();

    /*
    string filename;
    if (userType == STUDENT)
    {
        filename = STUDENT_FILE;
    }
    else if (userType == TEACHER)
    {
        filename = TEACHER_FILE;
    }

    ofstream ofs;
    ofs.open(filename, ios::out | ios::app);
    if (!ofs.is_open())
    {
        cout << "File \"" << filename << "\" doesn't exist!" << endl;
        return;
    }
    ofs << id << " " << username << " " << passwd << endl;
    ofs.close();
    cout << "User " << username << " was added successfully!" << endl;
    */
}

void Administrator::readUsersFromVector(int userType)
{
    vector<BasicRole> v;
    if (userType == STUDENT)
    {
        cout << " \n::::::::::::Students::::::::::::" << endl;
        cout << "[ID]\t\t\t\t\t"
             << "[Username]\t\t\t\t"
             << "[Password]\n"
             << endl;
        for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
        {
            cout << it->m_StuID << "\t\t\t\t\t" << it->m_Name << "\t\t\t\t\t" << it->m_Password << endl;
        }
    }
    else if (userType == TEACHER)
    {
        cout << "\n::::::::::::UESTC Employees::::::::::::" << endl;
        cout << "[ID]\t\t\t\t\t"
             << "[Username]\t\t\t\t"
             << "[Password]\n"
             << endl;
        for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
        {
            cout << it->m_EmpID << "\t\t\t\t\t" << it->m_Name << "\t\t\t\t\t" << it->m_Password << endl;
        }
    }
}

void Administrator::getExistingUsers()
{
    this->vStu.clear();
    this->vTea.clear();

    Student s;
    Teacher t;
    ifstream ifs;
    // get student info
    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "File \"" << STUDENT_FILE << "\" doesn't exist!" << endl;
        return;
    }
    while (ifs >> s.m_StuID && ifs >> s.m_Name && ifs >> s.m_Password)
    {
        vStu.push_back(s);
    }
    ifs.close();

    // get teacher info
    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "File \"" << TEACHER_FILE << "\" doesn't exist!" << endl;
        return;
    }
    while (ifs >> t.m_EmpID && ifs >> t.m_Name && ifs >> t.m_Password)
    {
        vTea.push_back(t);
    }
    ifs.close();
    // cout<<"Student No: "<<vStu.size()<<endl;
    // cout<<"Teacher No: "<<vTea.size()<<endl;
}

bool Administrator::isUserExist(int userType, int userID)
{
    if (userType == STUDENT)
    {
        for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
        {
            if (userID == (*it).m_StuID)
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
        {
            if (userID == (*it).m_EmpID)
            {
                return true;
            }
        }
        return false;
    }
}