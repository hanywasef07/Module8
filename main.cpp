//Name: Hany, Aleeza,Thanh, Victor, and Jacob
// Date: 10/24/2026
// Description: Module 8 - Queues 

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include "input.h"
#include "CostcoSimulation.h"

using namespace std;

//function prototypes
char menuOption();


int main()
{
    srand(static_cast<unsigned int>(time(0)));
    bool running = true;
    char option;

    while (running)
    {
        system("cls");

        option = menuOption();
        switch (option)
        {
        case '1':
        {

            cout << "\n\n";
            system("pause");
            break;
        }
        case '2':
        {

            cout << "\n\n";
            system("pause");
            break;
        }
        case '3':
        {
            system("cls");

            cout << "\n\t3> Simulation of checkout lines at a CostCo warehouse store\n";
            cout << "\t" << string(75, char(196)) << "\n";

            // Prompt for the operating time
            unsigned int totalTime = inputInteger("\n\tEnter the time (0..37800 in seconds) of the store will be operated:", 0, 37800);

            // Prompt for the number of cash registers
            int numRegisters = inputInteger("\n\tEnter the number of cash registers (1...10): ", 1, 10);
            

            // Create the Costco simulation
            CostcoSimulation<int> costco(totalTime, numRegisters);

            // Run the simulation
            costco.simulate();


            cout << "\n\n";
            system("pause");

            break;
        }
        case '0':
            cout << "Exiting the program.\n";
            running = false;
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}


char menuOption()
{
    cout << "\t\t  CMPR131 Chapter 8: Applications using Queues by Hany, Aleeza, Thanh, Victor, and Jacob (10/24/2026)\n";
    cout << "\t\t" << string(100, char(205));
    cout << "\n\t\t  1> Simulation of War (card game) using deque STL";
    cout << "\n\t\t  2> Simulation of an emergency room (ER) using priority queue STL";
    cout << "\n\t\t  3> Simulation of checkout lines at CostCo using multiple queues STL\n";
    cout << "\t\t" << string(100, char(196));
    cout << "\n\t\t  0 > Exit\n";
    cout << "\t\t" << string(100, char(205));

    char option = toupper(inputChar("\n\t\t  option: ", static_cast<string>("1,2,3,0")));
    return option;
}