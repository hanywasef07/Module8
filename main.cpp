//Name: Hany, Aleeza,Thanh, Victor, and Jacob
// Date: 10/24/2026
// Description: Module 8 - Queues 

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <queue>
#include <vector>
#include "input.h"
#include "CostcoSimulation.h"
#include "Patient.h"
#include "CardGame.h"
using namespace std;

//function prototypes
char menuOption();
void option2();

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
            system("cls");
            cout << "\n\t1> Simulation of War (card game) using deque STL\n";

            int cardsPerSuite = inputInteger("\n\tEnter a number of cards per suite: ", 1, 13);
            CardGame war(cardsPerSuite);
            war.play();

            cout << "\n\n";
            system("pause");
            break;
        }
        case '2':
        {
            option2();
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

void option2()
{
    priority_queue<Patient> lobby;
    vector<Patient> transferredPatients;
    char option;
    do
    {
        system("cls");

        cout << "\n\t2> Simulation of an emergency room (ER) using priority queue STL";
        cout << "\n\t" << string(100, char(205));
        cout << "\n\tA> Register a patient";
        cout << "\n\tB> Transfer patient(s) to the designation";
        cout << "\n\tC> Display transferred patients";
        cout << "\n\t" << string(100, char(196));
        cout << "\n\t0> return";
        cout << "\n\t" << string(100, char(205));

        option = toupper(inputChar("\n\t  option: ", static_cast<string>("ABC0")));


        switch (option)
        {
        case 'A':
        {
            Patient newPatient;
            newPatient.setName(inputString("\n\tEnter the patient's name: ", true));
            newPatient.setAge(inputInteger("\n\tEnter the patient's age: ", true));
            newPatient.setGender(inputChar("\n\tEnter the patient's gender (F-Female or M-Male): ", "FM"));
            cout << "\n\tFrom 1-5: \n\t1>Non-urgent \n\t2>Less Urgent \n\t3>Urgent \n\t4>Emergent \n\t5>Resuscitation";
            newPatient.setPriority(inputInteger("\n\tEnter the ER level: ", 1, 5));
            lobby.push(newPatient);
            cout << "\n\tPatient information has been registered.";
            system("pause");
            break;
        }
        case 'B':
        {
            /*
            1 - "name - examines and gives prescription..."
            2 - "name - transfers to x-ray lab..."
            3 - "name - transfers to emergency room..."
            4 - "name - transfers to surgery room..."
            5 - "name - transfers to ICU..."
            */
            try
            {
                //validation empty lobby - queue
                if (lobby.empty())
                {
                    throw "\n\tERROR: The lobby is empty.";
                }


                cout << "\n\t" << lobby.top().getName();
                switch (lobby.top().getPriority())
                {
                case 1:
                {
                    cout << " - examines and gives prescription....";
                    transferredPatients.push_back(lobby.top());
                    lobby.pop();
                }
                break;
                case 2:
                {
                    cout << " - transfers to x-ray lab....";
                    transferredPatients.push_back(lobby.top());
                    lobby.pop();
                }
                break;
                case 3:
                {
                    cout << " - transfers to emergency room....";
                    transferredPatients.push_back(lobby.top());
                    lobby.pop();
                }
                break;
                case 4:
                {
                    cout << " - transfers to surgery room....";
                    transferredPatients.push_back(lobby.top());
                    lobby.pop();
                }
                break;
                case 5:
                {
                    cout << " - transfers to ICU....";
                    transferredPatients.push_back(lobby.top());
                    lobby.pop();
                }
                break;
                default:
                {
                    cout << "\n\tERROR: Invalid priority!\n";
                }
                }
            }
            catch (const char* msg)
            {
                cout << msg << "\n";
            }

            cout << "\n\n";
            system("pause");
            break;
        }
        case 'C':
        {
            try
            {
                if (transferredPatients.empty())
                {
                    throw "\n\tERROR: No patient transferred.";
                }

                for (int i = 0; i < transferredPatients.size(); i++)
                {
                    cout << "\n\t" << i + 1 << " - " << transferredPatients.at(i);
                }
            }
            catch (const char* msg)
            {
                cout << msg << "\n";
            }

            cout << "\n\n";
            system("pause");
            break;
        }
        case '0':
            cout << "Exiting the option.\n";
            return;
        default:
            cout << "Invalid option. Please try again.\n";
            system("pause");
            break;
        }
    } while (option != 0);

}
