#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <algorithm>
#include <string>


using namespace std;

template <class T>
class CostcoSimulation
{
private:
	unsigned int totalTime; // Total time the store will be operated in seconds 
	unsigned int remainingTime; // Current time in the simulation
	size_t numRegisters; // Number of cash registers available    
	size_t servedCustomers; // Number of customers that have been served
	size_t totalCustomers; // Total number of customers that have been added to the store
	vector<queue<T>> registers; // Vector of queues representing cash registers
	vector<unsigned int> checkoutTime;    // Remaining checkout time for each register

	//helper functions
	size_t findShortestQueue() const; // Find the index of the shortest queue (cash register)

public:
	// Constructor
	CostcoSimulation();
	CostcoSimulation(unsigned int time, size_t numRegisters);



	// Add a customer to the shortest queue
	void addCustomer(const T& customer);

	// Generate random customers
	void generateCustomers();

	// Process customers at each register
	void processCheckout();

	// Display all cash registers
	void displayRegisters() const;

	// Run the simulation
	void simulate();

	// Getters
	unsigned int getTotalTime() const; // Get the total operating time of the store
	unsigned int getRemainingTime() const; // Get the remaining time in the simulation
	size_t getNumRegisters() const; // Get the number of cash registers
	size_t getServedCustomers() const; // Get the number of customers that have been served
	size_t getTotalCustomers() const; // Get the total number of customers that have been added to the store

};

// Default constructor initializes the simulation with 0 seconds and 1 cash register.
template <class T>
CostcoSimulation<T>::CostcoSimulation() : CostcoSimulation(0, 1)
{
}

// Precondition: time is between 0 and 37800,
// and numRegisters is between 1 and 10.
// Postcondition: Initializes the operating time, cash registers,
// customer counters, and checkout timers.
template <class T>
CostcoSimulation<T>::CostcoSimulation(unsigned int time, size_t numRegisters)
{
	totalTime = min(time, 37800u); // Limit the total time to a maximum of 37800 seconds (10.5 hours)
	remainingTime = totalTime; // Initialize the remaining time to the total time

	if (numRegisters < 1) // Ensure at least one cash register is available
	{
		this->numRegisters = 1;
	}
	else if (numRegisters > 10) // Limit the number of cash registers to a maximum of 10
	{
		this->numRegisters = 10;
	}
	else
	{
		this->numRegisters = numRegisters; // Set the number of cash registers to the specified value
	}

	servedCustomers = 0; // Initialize the number of served customers to 0
	totalCustomers = 0; // Initialize the total number of customers to 0

	registers.resize(this->numRegisters); // Resize the vector of queues to match the number of cash registers
	checkoutTime.resize(this->numRegisters, 0); // Resize the vector of checkout timers to match the number of cash registers and initialize them to 0
}

// Precondition: There is at least one cash register.
// Postcondition: Returns the index of the cash register with the shortest queue.
template <class T>
size_t CostcoSimulation<T>::findShortestQueue() const
{
	if (numRegisters == 0 || registers.empty())
	{
		return 0;
	}

	size_t shortestIndex = 0;
	size_t shortestSize = registers[0].size();

	for (size_t i = 1; i < numRegisters; ++i)
	{
		if (registers[i].size() < shortestSize)
		{
			shortestSize = registers[i].size();
			shortestIndex = i;
		}
	}

	return shortestIndex;
}

// Precondition: There is at least one cash register.
// Postcondition: Adds a customer to the shortest queue.
template <class T>
void CostcoSimulation<T>::addCustomer(const T& customer)
{
	if (numRegisters == 0 || registers.empty())
	{
		return;
	}

	const size_t shortestIndex = findShortestQueue();
	registers[shortestIndex].push(customer);
	++totalCustomers;
}

// Precondition: The random number generator has been seeded.
// Postcondition: Randomly generates a customer with a shopping cart
// and adds the customer to the shortest checkout queue.
template <class T>
void CostcoSimulation<T>::generateCustomers()
{
	const double arrivalProbability = 0.98;
	const int ONE = 1;
	const int FIFTY = 50;

	// 98% chance of generating a customer
	if (std::rand() < arrivalProbability * RAND_MAX)
	{
		const T customer = static_cast<T>(rand() % FIFTY + ONE);
		addCustomer(customer);
	}
}

// Precondition: Registers and checkout timers have been initialized.
// Postcondition: Processes one second of checkout at each register.
template <class T>
void CostcoSimulation<T>::processCheckout()
{
	const unsigned int ONE = 1u;
	const unsigned int FIVE = 5u;

	for (size_t i = 0; i < numRegisters; ++i)
	{
		if (!registers[i].empty())
		{
			if (checkoutTime[i] == 0)
			{
				const unsigned int items = static_cast<unsigned int>(registers[i].front());
				checkoutTime[i] = max(ONE, items / FIVE); // Each item takes 0.2 seconds
			}

			--checkoutTime[i];

			if (checkoutTime[i] == 0)
			{
				registers[i].pop();
				++servedCustomers;
			}
		}
		else
		{
			checkoutTime[i] = 0;
		}
	}
}

// Precondition: The simulation has been initialized with a total time and number of registers.
// Postcondition: Displays the current state of the simulation, including the remaining time,
template <class T>
void CostcoSimulation<T>::displayRegisters() const
{
	system("cls");
	const int ONE = 1, FOUR = 4;
	// Display the current state of the simulation
	cout << "\n\tCostCo warehouse store: " << remainingTime << "\tTotal customers served: " << servedCustomers << "\tTotal customers: " << totalCustomers << "\n";
	// Display the state of each cash register
	for (size_t i = 0; i < numRegisters; ++i)
	{
		cout << "\n\t\tCash register #" << i + ONE << ":\n";

		queue<T> temp = registers[i];

		cout << "\t\t\t\t";

		if (!temp.empty())
		{
			cout << char(254) << temp.front() << char(254) << " "; // Display the first customer in the queue
			temp.pop();

			while (!temp.empty())
			{
				cout << " " << string(FOUR, char(254)) << " "; // Display the remaining customers in the queue
				temp.pop();
			}
		}

		cout << "\n";
	}
}

// Precondition: The simulation has been initialized with a total time and number of registers.
// Postcondition: Runs the simulation for the specified total time.
template <class T>
void CostcoSimulation<T>::simulate()
{
	remainingTime = totalTime;

	const int ONE = 1;
	const int FIFTY = 50;

	// Generate the initial customer
	const T customer = static_cast<T>(std::rand() % FIFTY + ONE);
	addCustomer(customer);

	for (unsigned int t = 0; t < totalTime; ++t)
	{
		generateCustomers();
		processCheckout();

		--remainingTime;
		displayRegisters();

		Sleep(50);
	}

	if (totalTime == 0)
	{
		displayRegisters();
	}
}

// Getters for the simulation parameters and statistics
// Precondition: None
// Postcondition: Returns the total operating time of the store
template <class T>
unsigned int CostcoSimulation<T>::getTotalTime() const
{
	return totalTime;
}
// Precondition: None
// Postcondition: Returns the remaining time in the simulation
template <class T>
unsigned int CostcoSimulation<T>::getRemainingTime() const
{
	return remainingTime;
}
// Precondition: None
// Postcondition: Returns the number of cash registers
template <class T>
size_t CostcoSimulation<T>::getNumRegisters() const
{
	return numRegisters;
}

// Precondition: None
// Postcondition: Returns the number of customers that have been served
template <class T>
size_t CostcoSimulation<T>::getServedCustomers() const
{
	return servedCustomers;
}

// Precondition: None
// Postcondition: Returns the total number of customers
template <class T>
size_t CostcoSimulation<T>::getTotalCustomers() const
{
	return totalCustomers;
}