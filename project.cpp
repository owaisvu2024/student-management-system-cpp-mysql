#include <iostream>
#include <mysql.h>
#include <string>
#include <cctype>
using namespace std;

class school_managment_system
{
private:
    MYSQL *conn;

public:
    school_managment_system()
    {
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "root", "12345", "school", 3306, NULL, 0);
        if (!conn)
        {
            cout << "DATABASE NOT CONNECT " << mysql_error(conn) << endl;
        }
    }

    bool isStrongPassword(string password)
    {
        if (password.length() < 8)
        {
            return false;
        }
        bool hasUpper = false;
        bool hasLower = false;
        bool hasDigit = false;
        bool hasSpecial = false;

        for (int i = 0; i < password.length(); i++)
        {
            char ch = password[i];

            if (isupper(ch))
                hasUpper = true;
            else if (islower(ch))
                hasLower = true;
            else if (isdigit(ch))
                hasDigit = true;
            else
                hasSpecial = true;
        }
        if (hasUpper && hasLower && hasDigit && hasSpecial)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void add_data()
    {
        system("cls");
        int id;
        string name, grade;
        float percentage;

        cout << "------ ADD STUDENT DATA -------" << endl
             << endl;
        cout << " ENTER STUDENT ID: ";
        cin >> id;
        cin.ignore();
        cout << " ENTER STUDENT NAME: ";
        getline(cin, name);
        cout << " ENTER STUDENT GRDAE: ";
        cin >> grade;
        cout << " ENTER STUDENT PERCENTAGE: ";
        cin >> percentage;

        char query[514];
        sprintf(query, "insert into student (id,name,grade,percentage) values (%d,'%s','%s',%f)", id, name.c_str(), grade.c_str(), percentage);
        if (mysql_query(conn, query) == 0)
        {
            system("cls");
            cout << "----------------------" << endl;
            cout << "DATA ADD SUCCESSFULLY IN DATABASE " << endl;
        }
        else
        {
            system("cls");
            cout << "----------------------" << endl;
            cout << "ERROR !  " << mysql_error(conn) << endl;
        }
    }
    void search_record()
    {
        system("cls");
        int id;
        cout << "------ SEARCH STUDENT DATA ------" << endl
             << endl;
        cout << "ENTER ID: ";
        cin >> id;

        char query[512];
        sprintf(query, "select * from student where id=%d", id);
        if (mysql_query(conn, query) == 0)
        {
            MYSQL_RES *res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0)
            {
                system("cls");
                MYSQL_ROW row = mysql_fetch_row(res);
                cout << "------ RECORD FOUND ------" << endl
                     << endl;
                cout << "ID : " << row[0] << endl;
                cout << "NAME : " << row[1] << endl;
                cout << "GRADE : " << row[2] << endl;
                cout << "PERCENTAGE : " << row[3] << endl
                     << endl;
            }
            else
            {
                system("cls");
                cout << "RECORD NOT FOUND ! " << endl
                     << endl;
            }
            mysql_free_result(res);
        }
        else
        {
            system("cls");
            cout << "ERROR !" << mysql_error(conn) << endl;
        }
    }

    void delete_record()
    {
        system("cls");
        int id;
        cout << "----- DELETE RECORD -----" << endl
             << endl;
        cout << "ENTER ID : ";
        cin >> id;

        char query[512];
        sprintf(query, "delete from student where id=%d", id);
        if (mysql_query(conn, query) == 0)
        {
            if (mysql_affected_rows(conn) > 0)
            {
                system("cls");
                cout << "DATA DELETE SUCEESSFULLY " << endl
                     << endl;
            }
            else
            {
                system("cls");
                cout << "DATA DELETE NOT SUCEESSFULLY " << endl
                     << endl;
            }
        }
        else
        {
            system("cls");
            cout << "ERRORS " << mysql_error(conn) << endl;
        }
    }
    void record_update()
    {
        system("cls");
        int id;
        string name, grade;
        float percentage;

        cout << "----- DATA UPDATE ----- " << endl
             << endl;
        cout << "ENTER ID: ";
        cin >> id;
        cin.ignore();
        cout << "ENTER NEW NAME: ";
        getline(cin, name);
        cout << "ENTER NEW GRADE: ";
        cin >> grade;
        cout << "ENTER NEW PERCENTAGE: ";
        cin >> percentage;

        char query[512];
        sprintf(query, "update student set name='%s',grade='%s',percentage=%f where id=%d", name.c_str(), grade.c_str(), percentage, id);
        if (mysql_query(conn, query) == 0)
        {
            if (mysql_affected_rows(conn) > 0)
            {
                system("cls");
                cout << "----------------------" << endl;
                cout << "UPDATE SUCEESSFULLY " << endl
                     << endl;
            }
            else
            {
                system("cls");
                cout << "----------------------" << endl;
                cout << "RECORD NOT FOUND ! " << endl
                     << endl;
            }
        }
        else
        {
            system("cls");
            cout << "ERROR ! " << mysql_error(conn) << endl;
        }
    }
    void show_record()
    {
        system("cls");
        cout << "------ ALL STUDENT DATA ------" << endl
             << endl;
        char query[512];
        sprintf(query, "select * from student ");
        if (mysql_query(conn, query) == 0)
        {
            MYSQL_RES *res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0)
            {
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res)) != NULL)
                {
                    cout << "----------------------" << endl;
                    cout << "ID: " << row[0] << endl;
                    cout << "NAME: " << row[1] << endl;
                    cout << "GRADE: " << row[2] << endl;
                    cout << "PERCENTAGE: " << row[3] << endl;
                    cout << "----------------------" << endl;
                }
            }
            else
            {
                system("cls");
                cout << "----------------------" << endl;
                cout << "RECORD NOT FOUND " << endl;
            }
            mysql_free_result(res);
        }
        else
        {
            system("cls");
            cout << "ERROR " << mysql_error(conn) << endl;
        }
    }

    void count_record()
    {

        char query[512];
        sprintf(query, "select count(id) from student");
        if (mysql_query(conn, query) == 0)
        {
            MYSQL_RES *res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0)
            {
                MYSQL_ROW row = mysql_fetch_row(res);
                system("cls");
                cout << "TOTAL RECORD: " << row[0] << endl;
            }

            else
            {
                system("cls");
                cout << "----------------------" << endl;
                cout << " RECORD NOT FOUND " << endl;
            }
            mysql_free_result(res);
        }
        else
        {
            system("cls");
            cout << "ERROR " << mysql_error(conn);
        }
    }

    void sign_up()
    {
        system("cls");
        string username, password;
        cout << "----- SIGN UP -----" << endl;
        cin.ignore();
        cout << "ENTER USERNAME " << endl;

        getline(cin, username);
        cout << "ENTER PASSWORD (Min 8 chars, 1 Capital, 1 Small, 1 Number, 1 Symbol): " << endl;
        cin >> password;
        if (isStrongPassword(password) == false)
        {
            cout << "❌ WEAK PASSWORD! Please follow the password rules." << endl;
            return;
        }

        char query[512];
        sprintf(query, "insert into admin (username,password) values ('%s','%s')", username.c_str(), password.c_str());
        if (mysql_query(conn, query) == 0)
        {
            system("cls");
            cout << "SIGN UP SUCCESSFULLY " << endl;
        }
        else
        {
            cout << "ERROR " << mysql_error(conn) << endl;
        }
    }

    void login()
    {
        system("cls");
        string username, password;
        cout << "LOGIN " << endl;
        cin.ignore();
        cout << "ENTER USERNAME " << endl;
        getline(cin, username);

        cout << "ENTER PASSWORD " << endl;
        cin >> password;

        char query[512];
        sprintf(query, "select * from admin where username='%s' and password='%s'", username.c_str(), password.c_str());
        if (mysql_query(conn, query) == 0)
        {
            MYSQL_RES *res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0)
            {
                system("cls");
                cout << "LOGIN SUCCESSFULLY " << endl
                     << endl;
                int choice;
                while (true)
                {

                    cout << "STUDENT MANAGEMENT SYSTEM" << endl;
                    cout << "----------------------" << endl;
                    cout << "1. ADD STUDENT " << endl;
                    cout << "2. SERACH STUDENT DATA " << endl;
                    cout << "3. DELETE DATA " << endl;
                    cout << "4. UPDATE DATA " << endl;
                    cout << "5. SHOW ALL STUDENT DATA " << endl;
                    cout << "6. COUNT TOTAL STUDENT " << endl;
                    cout << "7. EXIST " << endl;
                    cout << "----------------------" << endl;
                    cout << "ENTER ANY CHOICE : ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        this->add_data();
                        break;
                    case 2:
                        this->search_record();
                        break;
                    case 3:
                        this->delete_record();
                        break;
                    case 4:
                        this->record_update();
                        break;
                    case 5:
                        this->show_record();
                        break;
                    case 6:
                        this->count_record();
                        break;
                    case 7:
                        system("cls");
                        cout << "PROGRAM EXIST GOOD BY!" << endl;
                        return;
                        break;

                    default:
                        cout << "THIS VALUE IS NOT AVAILABLE " << endl;
                        break;
                    }
                }
            }
            else
            {
                system("cls");
                cout << "Login Failed " << endl
                     << endl;
            }
            mysql_free_result(res);
        }
    }

    void password_forgot()
    {
        system("cls");
        string username, password;
        cout << "------ FORGOT PASSWORD ------ " << endl
             << endl;
        cin.ignore();
        cout << "ENTER USERNAME " << endl;
        getline(cin, username);

        cout << "ENTER NEW PASSWORD " << endl;
        cin >> password;

        char query[512];
        sprintf(query, "update admin set password = '%s' where username='%s'", password.c_str(), username.c_str());
        if (mysql_query(conn, query) == 0)
        {
            if (mysql_affected_rows(conn) > 0)
            {
                system("cls");
                cout << "PASSWORD UPDATE SUCESSFULLY " << endl;
            }
            else
            {
                system("cls");
                cout << "RECORD NOT FOUND !   " << endl;
            }
        }
        else
        {
            cout << "ERROR " << mysql_error(conn) << endl;
        }
    }
};
int main()
{
    school_managment_system obj;
    int s;
    system("cls");
    while (true)
    {
        cout << "----------------------" << endl;
        cout << "1. SIGN UP " << endl;
        cout << "2. LOGIN " << endl;
        cout << "3. FORGOT PASSWORD " << endl;
        cout << "4. EXIT " << endl;
        cout << "----------------------" << endl;
        cout << "CHOICE ANY ONE ";
        cin >> s;
        switch (s)
        {
        case 1:
            obj.sign_up();
            break;

        case 2:
            obj.login();
            break;

        case 3:
            obj.password_forgot();
            break;
        case 4:
            system("cls");
            cout << "------ PROGRAM EXIST------";
            return 0;
            break;

        default:
            system("cls");
            cout << "THIS VALUE IS NOT AVAILABLE " << endl;
            break;
        }
    }

    return 0;
}