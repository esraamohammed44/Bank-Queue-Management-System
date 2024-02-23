 #pragma once
#include<iostream>
#include "Client.h"
#include <queue>
#include<iostream>
#include <ctime> 
#include <windows.h>  // Include this header for Windows-specific console functions
using namespace std;
// Define color constants
const int FOREGROUND_MAGENTA = 13;  // Magenta text
const int FOREGROUND_CYAN = 11;
const int FOREGROUND_WHITE = 15;
const int FOREGROUND_YELLOW = 14;  // Numerical value for yellow text color
const int FOREGROUND_BABY_BLUE = 11;  // Numerical value for a color resembling baby blue
const int FOREGROUND_VIOLET = FOREGROUND_BLUE | FOREGROUND_RED;
// Comparison function for priority_queue
class compareEventTime
{
public:
	bool operator()(const Client& lhs, const Client& rhs) const
	{

		if (lhs.eventTime == rhs.eventTime) {
			// If arrival times are equal, compare by age
			return lhs.age < rhs.age;
		}
		return lhs.eventTime > rhs.eventTime;
	}
};
void SetColor(int ForgC)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

class Bank
{
private:

	/*
	-> there three paremeter :
	1- Client -->  the type of elements the priority queue will store.
	2- vector<Client> -->  container used by the priority queue (store Clients).
	3- compareEventTime-->  used to define the ordering criterion for a priority queue
	(here depending on arrival time )
	** clientPriorityQueue ---> name of priority queue
	*/
	priority_queue<Client, vector<Client>, compareEventTime> clientPriorityQueue;// origin queue
	int tellerNumber = 3;// initial -->3
	queue<Client> clientNormalQueue;// waiting place
	int currentTimeOfBank = 0;// Time of Bank 
	int maxTellers = 5; // Maximum number of tellers
	vector<Client> tellers; // Vector to store active tellers

	double totalTellerBusyTime = 0;
	double totalSimulationTime = 0;
	
	int totalClientsServed = 0;
	double totalWaitingTime = 0;
	double totalServiceTime = 0;

public:


	// function to add client into priority queue
	// to avoid unnecessary copying of objects.
	void addClientToPriorityQueue(const Client clientPriority)
	{
		clientPriorityQueue.push(clientPriority);
	}
	// function to add client into normal queue
	//to avoid unnecessary copying of objects.
	void addClientToNormalQueue(const Client clientNormal)
	{
		clientNormalQueue.push(clientNormal);
	}



	void run()
	{
		while (!clientPriorityQueue.empty()) // priority queue is full
		{

			Client currentClientPriority = clientPriorityQueue.top();// get the first Client
			currentTimeOfBank = currentClientPriority.eventTime;//time of bank = arrival time=0 
			clientPriorityQueue.pop();// delete this client from Priority

			if (currentClientPriority.eventType == "Arrival")// if client arrival the teller
			{
				if (tellerNumber != 0) // check teller is empty
				{
					/*
					** waiting time = time of bank - arrival time
					**the first client:
					- time of bank == arrival time (assume=35)
					- waiting time =0
					*/

					//2- 
					currentClientPriority.waitingTime = currentTimeOfBank - currentClientPriority.eventTime;
					currentClientPriority.eventTime = currentTimeOfBank + currentClientPriority.serviceTime;
					//4- 
					currentClientPriority.eventType = "Leave";//client priority leave the teller
					// 3- 

					SetColor(FOREGROUND_BABY_BLUE);
					cout << "Client name : " << currentClientPriority.name
						<< "\t Waiting Time : " << currentClientPriority.waitingTime
						<< "\t Leave Time : " << currentClientPriority.eventTime << endl;
					SetColor(FOREGROUND_WHITE);

					//1- 
					tellerNumber--;

					totalTellerBusyTime += currentClientPriority.serviceTime;


					//add again client to priority queue with new status or event type is leave not arrival 
					addClientToPriorityQueue(currentClientPriority);

				}
				else
				{
					// if teller is full with client from priority queue
					addClientToNormalQueue(currentClientPriority);
				}
			}
			//if client priority leave from teller
			else if (currentClientPriority.eventType == "Leave")
			{


				if (!clientNormalQueue.empty())// clientNormalQueue is full
				{

					Client currentClientNormal = clientNormalQueue.front();// get the first client 
					clientNormalQueue.pop();
					//1- 


					//2-
					currentClientNormal.waitingTime = currentTimeOfBank - currentClientNormal.eventTime;
					currentClientNormal.eventTime = currentTimeOfBank + currentClientNormal.serviceTime;
					//4- 
					currentClientNormal.eventType = "Leave";//client normal leave the teller
					//3-


					SetColor(FOREGROUND_BABY_BLUE);
					cout << "client name : " << currentClientNormal.name
						<< "\t Waiting Time : " << currentClientNormal.waitingTime
						<< " \t Leave Time : " << currentClientNormal.eventTime << endl;
					SetColor(FOREGROUND_WHITE);

					addClientToPriorityQueue(currentClientNormal);

				}
				else
				{

					tellerNumber++;
				}

				totalClientsServed++;
				totalWaitingTime += currentClientPriority.waitingTime;
				totalServiceTime += currentClientPriority.serviceTime;

			}

		}
		//Teller Utilization Rate Calculation:
		/*
		The total time tellers are busy serving clients is divided by the total simulation time
		   to calculate the teller utilization rate
		*/
		cout << "*************************************************************" << endl;
		SetColor(FOREGROUND_YELLOW); // Set color to yellow
		cout << " \t\t\t\t\t************************************\t\t\t\t" << endl;
		cout << " \t\t\t \t\t Final Result of  : " << endl;
		cout << "\t\t\t\t\t************************************\t\t\t\t\t" << endl;
		SetColor(FOREGROUND_WHITE); // Set color back to default (white)
		// Calculate metrics only if clients were served to avoid division by zero
		if (totalClientsServed > 0) {
			// Teller Utilization Rate Calculation
			totalSimulationTime = currentTimeOfBank;
			double tellerUtilizationRate = totalTellerBusyTime / totalSimulationTime;

			SetColor(FOREGROUND_VIOLET);
			cout << "Teller Utilization Rate: " << fixed << setprecision(2) << tellerUtilizationRate << endl;

			// Average Waiting Time Calculation
			double averageWaitingTime = totalWaitingTime / totalClientsServed;

			SetColor(FOREGROUND_CYAN);
			cout << "Average Waiting Time: " << fixed << setprecision(2) << averageWaitingTime << endl;

			// Average Service Time Calculation
			double averageServiceTime = totalServiceTime / totalClientsServed;

			SetColor(FOREGROUND_YELLOW);
			cout << "Average Service Time: " << fixed << setprecision(2) << averageServiceTime << endl;

			SetColor(FOREGROUND_WHITE);
		}
	}

};

