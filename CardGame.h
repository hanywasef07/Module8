#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class CardGame
{
private:
	int cardsPerSuite;
	deque<int> player1;
	deque<int> player2;
	deque<int> player1Won;
	deque<int> player2Won;

	// Precondition: cardsPerSuite is from 1 to 13
	// Postcondition: each player receives half of a shuffled 4-suite deck
	void createAndDealDeck()
	{
		player1.clear();
		player2.clear();
		player1Won.clear();
		player2Won.clear();

		vector<int> deck;
		for (int suite = 0; suite < 4; suite++)
		{
			for (int rank = 1; rank <= cardsPerSuite; rank++)
				deck.push_back(rank);
		}

		for (int i = static_cast<int>(deck.size()) - 1; i > 0; i--)
			swap(deck[i], deck[rand() % (i + 1)]);

		for (size_t i = 0; i < deck.size(); i++)
		{
			if (i % 2 == 0)
				player1.push_back(deck[i]);
			else
				player2.push_back(deck[i]);
		}
	}

	// Precondition: table holds the cards from the current battle
	// Postcondition: those cards are moved to the winner's won-cards pile
	void awardTable(deque<int>& winnerPile, deque<int>& table)
	{
		while (!table.empty())
		{
			winnerPile.push_back(table.front());
			table.pop_front();
		}
	}

	// Precondition: none
	// Postcondition: waits until the user presses Enter before the next play
	void waitForEnter()
	{
		cin.get();
	}

public:
	// Precondition: none
	// Postcondition: a game with 1 card per suite is ready to play
	CardGame()
	{
		cardsPerSuite = 1;
		createAndDealDeck();
	}

	// Precondition: cardsPerSuite is from 1 to 13
	// Postcondition: a shuffled deck of 4 suites is dealt to both players
	CardGame(int cardsPerSuite)
	{
		this->cardsPerSuite = cardsPerSuite;
		createAndDealDeck();
	}

	// Precondition: both players have been dealt cards
	// Postcondition: the war is played until a player cannot continue, then the winner is displayed
	void play()
	{
		deque<int> table;
		bool inTieBreaker = false;

		while (!player1.empty() && !player2.empty())
		{
			int card1 = player1.front();
			player1.pop_front();
			int card2 = player2.front();
			player2.pop_front();

			table.push_back(card1);
			table.push_back(card2);

			cout << "\n\t\tPlayer1:  " << card1 << "\tPlayer2:  " << card2 << " -> ";

			if (card1 > card2)
			{
				if (inTieBreaker)
					cout << "Player1 wins tie breaker!";
				else
					cout << "Player1 wins!";

				awardTable(player1Won, table);
				inTieBreaker = false;
				cout << "\n";
				waitForEnter();
			}
			else if (card2 > card1)
			{
				if (inTieBreaker)
					cout << "Player2 wins tie breaker!";
				else
					cout << "Player2 wins!";

				awardTable(player2Won, table);
				inTieBreaker = false;
				cout << "\n";
				waitForEnter();
			}
			else
			{
				cout << "Tie breaker begins!";
				inTieBreaker = true;

				if (player1.empty())
				{
					cout << "\n\t\tPlayer2 takes all because Player1 has no more card.\n";
					awardTable(player2Won, table);
					waitForEnter();
					break;
				}
				if (player2.empty())
				{
					cout << "\n\t\tPlayer1 takes all because Player2 has no more card.\n";
					awardTable(player1Won, table);
					waitForEnter();
					break;
				}

				cout << "\n";
				waitForEnter();
			}
		}

		int p1Total = static_cast<int>(player1.size() + player1Won.size());
		int p2Total = static_cast<int>(player2.size() + player2Won.size());

		cout << "\n";
		if (p1Total > p2Total)
			cout << "\t\tPlayer1 wins the war with most number of cards (" << p1Total << ").\n";
		else if (p2Total > p1Total)
			cout << "\t\tPlayer2 wins the war with most number of cards (" << p2Total << ").\n";
		else
			cout << "\t\tThe war ends in a tie with " << p1Total << " cards each.\n";
	}
};
