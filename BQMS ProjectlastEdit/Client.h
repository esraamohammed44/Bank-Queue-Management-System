#pragma once
#include<string>
#include <ctime> 
using namespace std;
class  Client {
public:
    string name;
    int age;
    long eventTime;//arrival time or leave time  Depending on EventType
    /*
     int Arrival_time;
    int Leave_time;
    */
    string eventType = "Arrival";//arrive or leave
   long waitingTime;
    long serviceTime;


    // Constructor
    Client(){}
    Client(string Name, long Event_time, int Service_time, int Age )
    {
        name = Name;
        eventTime = Event_time;
        serviceTime = Service_time;
        age = Age;

    }
};


