#pragma once
#include "Patient.h"
#include<queue>
#include<vector>
#include<iostream>
#include<string>
#include<ctime>
#include "input.h"

class Hospital
{
private:
	priority_queue<Patient> lobby;
	vector<Patient> transferredPatients;
public:
	void registerPatient();
	void transferPatient();
	void displayTransferredPatients() const;
};

inline void Hospital::registerPatient()
{
	Patient newPatient;
	newPatient.setName(inputString("\n\tEnter the patient's name: ", true));
	newPatient.setAge(inputInteger("\n\tEnter the patient's age: ", 1, 100));
	newPatient.setGender(inputChar("\n\tEnter the patient's gender (F-Female or M-Male): ", static_cast<string>("FM")));
	cout << "\n\tFrom 1-5: \n\t1>Non-urgent \n\t2>Less Urgent \n\t3>Urgent \n\t4>Emergent \n\t5>Resuscitation";
	newPatient.setPriority(inputInteger("\n\tEnter the ER level: ", 1, 5));
	newPatient.setCheckedInTime(static_cast<unsigned int>(time(nullptr)));
	lobby.push(newPatient);
	cout << "\n\tPatient information has been registered.";
}

inline void Hospital::transferPatient()
{
    if (lobby.empty())
    {
        cout << "\n\tERROR: The lobby is empty.\n";
        return;
    }

    const Patient& patient = lobby.top();
    const char* action = nullptr;

    switch (patient.getPriority())
    {
    case 1:
        action = "examines and gives prescription....";
        break;
    case 2:
        action = "transfers to x-ray lab....";
        break;
    case 3:
        action = "transfers to emergency room....";
        break;
    case 4:
        action = "transfers to surgery room....";
        break;
    case 5:
        action = "transfers to ICU....";
        break;
    default:
        cout << "\n\tERROR: Invalid priority!\n";
        return;
    }

    cout << "\n\t" << patient.getName()
        << " - " << action << '\n';

    transferredPatients.push_back(patient);
    lobby.pop();
}

inline void Hospital::displayTransferredPatients() const
{
    if (transferredPatients.empty())
    {
        cout << "\n\tERROR: No patient transferred.\n";
        return;
    }

    for (size_t i = 0; i < transferredPatients.size(); ++i)
    {
        cout << "\n\t" << i + 1
            << " - " << transferredPatients[i];
    }
}