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

	void createAndDealDeck();
	void awardTable(deque<int>& winner, deque<int>& table);

public:
	CardGame();
	CardGame(int cardsPerSuite);
	void play();
};

// Precondition: none
// Postcondition: a game with 1 card per suite is ready to play
inline CardGame::CardGame() : CardGame(1)
{
}

// Precondition: cardsPerSuite is from 1 to 13
// Postcondition: a shuffled deck of 4 suites is dealt to both players
inline CardGame::CardGame(int cardsPerSuite)
{
	this->cardsPerSuite = cardsPerSuite;
	createAndDealDeck();
}

// Precondition: cardsPerSuite is from 1 to 13
// Postcondition: each player receives half of a shuffled 4-suite deck
inline void CardGame::createAndDealDeck()
{
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
// Postcondition: those cards are moved to the back of the winner's deque
inline void CardGame::awardTable(deque<int>& winner, deque<int>& table)
{
	while (!table.empty())
	{
		winner.push_back(table.front());
		table.pop_front();
	}
}

// Precondition: both players have been dealt cards
// Postcondition: the war is played until one player cannot continue, then the winner is displayed
inline void CardGame::play()
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

			awardTable(player1, table);
			inTieBreaker = false;
			cout << "\n";
		}
		else if (card2 > card1)
		{
			if (inTieBreaker)
				cout << "Player2 wins tie breaker!";
			else
				cout << "Player2 wins!";

			awardTable(player2, table);
			inTieBreaker = false;
			cout << "\n";
		}
		else
		{
			cout << "Tie breaker begins!";
			inTieBreaker = true;

			if (player1.empty())
			{
				cout << "\n\t\tPlayer2 takes all because Player1 has no more card.\n";
				awardTable(player2, table);
				break;
			}
			if (player2.empty())
			{
				cout << "\n\t\tPlayer1 takes all because Player2 has no more card.\n";
				awardTable(player1, table);
				break;
			}
		}
	}

	cout << "\n";
	if (player1.size() > player2.size())
		cout << "\t\tPlayer1 wins the war with most number of cards (" << player1.size() << ").\n";
	else if (player2.size() > player1.size())
		cout << "\t\tPlayer2 wins the war with most number of cards (" << player2.size() << ").\n";
	else
		cout << "\t\tThe war ends in a tie with " << player1.size() << " cards each.\n";
}
