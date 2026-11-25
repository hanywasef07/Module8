#pragma once
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class Patient
{
private:
	int priority;
	unsigned int checkedInTime;
	string name;
	int age;
	char gender;
	unsigned int admittedTime;
	//string careUnit;
	static string ER_description[5];
public:
	//Precondition: None
	//Postcondition: Create a patient object
	Patient()
	{
		checkedInTime = 0;
		admittedTime = 0;
		priority = 0;
		name = "unknown";
		age = 0;
		gender = 'u';
	}

	//Precondition: Valid checked in time
	//Postcondition: Set the checkedInTime to t
	void setCheckedInTime(unsigned int t)
	{
		this->checkedInTime = t;
	}

	//Precondition: None
	//Postcondition: Returns the patient's checkedInTime
	unsigned int getCheckedInTime() const
	{
		return checkedInTime;
	}

	//Precondition: Priority is valid (from 1-5)
	//Postcondition: Set patient priority to the provided input
	void setPriority(int priority)
	{
		this->priority = priority;
	}

	//Precondition: None
	//Postcondition: Returns the patient's priority level
	int getPriority() const
	{
		return priority;
	}

	//Precondition: Valid patient's name
	//Postcondition: Set patient name to the provided input
	void setName(string name)
	{
		this->name = name;
	}

	//Precondition: None
	//Postcondition: Returns the patient's name
	string getName() const
	{
		return name;
	}

	//Precondition: Valid patient's age
	//Postcondition: Set patient age to the provided input
	void setAge(int age)
	{
		this->age = age;
	}

	//Precondition: None
	//Postcondition: Returns the patient's age
	int getAge() const
	{
		return age;
	}

	//Precondition: Valid patient's gender
	//Postcondition: Set patient gender to the provided input
	void setGender(char gender)
	{
		this->gender = gender;
	}

	//Precondition: None
	//Postcondition: Returns the patient's age
	char getGender() const
	{
		return gender;
	}

	friend bool operator <(const Patient& P1, const Patient& P2); //key in priority queue

	friend ostream& operator<<(ostream& outs, const Patient& obj);
};

//Precondition: Both Patients objects have valid priority level
//Postcondition: Returns true if P1 has lower priority than P2
bool operator <(const Patient& P1, const Patient& P2)
{
	if (P1.priority == P2.priority)
		return P1.checkedInTime > P2.checkedInTime; // same level: whoever checked in first goes first
	return P1.priority < P2.priority;
}

string Patient::ER_description[5] = { "Stable, with no resources anticipated or prescriptions", "Stable, with only one type of resource anticipated " ,"Stable, with multiple types of resources needed to investigate or treat", "High risk of deterioration, or signs of a time-critical problem", "Immediate, life-saving intervention required without delay" };

//Precondition: None
//Postcondition: Display the patient's data
ostream& operator <<(ostream& outs, const Patient& obj)
{
	outs << "ER level: " << obj.getPriority() << " - " << obj.ER_description[obj.getPriority() - 1] << '\n';
	time_t checkedIn = obj.getCheckedInTime();
	char timeText[26];
	ctime_s(timeText, sizeof(timeText), &checkedIn);
	outs << "\t\t\tChecked-In time: " << timeText;   // timeText already ends with a new line
	outs << "\t\t\tPatient's name: " << obj.getName() << '\n';
	outs << "\t\t\tPatient's age: " << obj.getAge() << '\n';
	outs << "\t\t\tPatient's gender: " << obj.getGender() << '\n';
	return outs;
}
