
/*#include"Client.h"
#include <iostream>
#include "Bank.h"
using namespace std;
int main()
{
   
    Bank b1;
    cout << " \t\t\t\t\t************************************\t\t\t\t" << endl;
    cout << " \t\t\t \t\t Bank Queue Management System(BQMS)  ";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t************************************\t\t\t\t\t" << endl;
    cout << endl;
    int numOfCusromers;
    cout << "Enter Number of Customers that they want service from tellers :" << endl;
    cin >> numOfCusromers;

    for (int i = 0; i < numOfCusromers; i++)
    {
        string name;
        int arrivalTime, serviceTime;
        cout << "Enter Details of Customer " << i + 1 << ":" << endl;
        cout << "Name of Client  : ";
        cin >> name;
        cout << "Arrival Time : ";
        cin >> arrivalTime;
        cout << "service Time : ";
        cin >> serviceTime;
        cout << "***************************************************" << endl;
        Client client(name, arrivalTime, serviceTime);
        b1.addClientToPriorityQueue(client);


    }
    b1.run();




}*/

// enter data during run time 
// setw()----> function for space

#include <iostream>
#include <iomanip> // Include for setw
#include "Bank.h"
using namespace std;

bool isAllDigits(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

bool isAllAlphaOrSpace(const string& str) {
    return all_of(str.begin(), str.end(), [](unsigned char c) { return isalpha(c) || isspace(c); });
}

int main()
{
    Bank b1;
    int numOfCustomers;


    SetColor(FOREGROUND_YELLOW); // Set color to yellow
    cout << " \t\t\t\t\t************************************\t\t\t\t" << endl;
    SetColor(FOREGROUND_WHITE); // Set color back to default (white)
    SetColor(FOREGROUND_BABY_BLUE);
    cout << " \t\t\t \t\t Bank Queue Management System(BQMS)  ";
    SetColor(FOREGROUND_WHITE);
    SetColor(FOREGROUND_YELLOW); // Set color to yellow
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t************************************\t\t\t\t\t" << endl;
    SetColor(FOREGROUND_WHITE); // Set color back to default (white)
   
    cout << endl;
    SetColor(FOREGROUND_BABY_BLUE);
    cout << "Enter Number of Clients that they want service from tellers :" << endl;
    SetColor(FOREGROUND_WHITE); // Set color back to default (white)
    // Input validation for numOfCustomers
    while (true)
    {
        string input;
        cin >> input;
        if (isAllDigits(input))
        {
            numOfCustomers = stoi(input);
            break;
        }
        else
        {
            cout << "Invalid input! Please enter a valid number.\n";
        }
    }

    for (int i = 0; i < numOfCustomers; i++)
    {

        // Set a unique color for each client
        int clientColor = i % 15 + 1;  // Use numbers 1-15 for different colors
        SetColor(clientColor);

        cout << " \t\t\t\t\t************************************\t\t\t\t" << endl;
        cout << " \t\t\t \t\t Information about each  Client " << i + 1 << " ";
        cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t************************************\t\t\t\t\t" << endl;

        SetColor(FOREGROUND_WHITE); // Set color back to default (white) after displaying client information


        string name;
        long arrivalTime, serviceTime, age;

        cout << "Enter Details of Client " << i + 1 << ":" << endl;

        // Input validation for name
        do
        {
            cout << "Name of Client  : ";
            cin.ignore(); // Ignore any previous newline character in the input buffer
            getline(cin, name);

            if (!isAllAlphaOrSpace(name))
            {
                cout << "Invalid input! Name should contain only letters or spaces.\n";
            }
        } while (!isAllAlphaOrSpace(name));

        // Input validation for age
        do
        {
            cout << "Age of Client : ";
            string ageStr;
            cin >> ageStr;

            if (isAllDigits(ageStr))
            {
                age = stoi(ageStr);
                break;
            }
            else
            {
                cout << "Invalid input! Age should contain only digits.\n";
            }
        } while (true);

        // Input validation for arrivalTime
        do
        {
            cout << "Arrival Time : ";
            string arrivalStr;
            cin >> arrivalStr;

            if (isAllDigits(arrivalStr))
            {
                arrivalTime = stoi(arrivalStr);
                break;
            }
            else
            {
                cout << "Invalid input! Arrival time should contain only digits.\n";
            }
        } while (true);

        // Input validation for serviceTime
        do
        {
            cout << "Service Time : ";
            string serviceStr;
            cin >> serviceStr;

            if (isAllDigits(serviceStr))
            {
                serviceTime = stoi(serviceStr);
                break;
            }
            else
            {
                cout << "Invalid input! Service time should contain only digits.\n";
            }
        } while (true);

        cout << endl;
        cout << "***************************************************" << endl;
        Client client(name, arrivalTime, serviceTime, age);
        b1.addClientToPriorityQueue(client);
        
    }

    SetColor(FOREGROUND_CYAN); // Set color to cyan
    cout << " \t\t\t\t\t************************************\t\t\t\t" << endl;
    cout << " \t\t\t \t\t Information about Clients  ";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t************************************\t\t\t\t\t" << endl;
    b1.run();
    SetColor(FOREGROUND_WHITE); // Set color back to default (white)

    return 0;
}










