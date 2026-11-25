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
    //deque<int> player1Won;
    //deque<int> player2Won;

    // Precondition: cardsPerSuite is from 1 to 13
    // Postcondition: each player receives half of a shuffled 4-suite deck
    void createAndDealDeck()
    {
        player1.clear();
        player2.clear();
        //player1Won.clear();
        //player2Won.clear();

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
    // Postcondition: all available rounds are played. Won cards collected by respective players. If final tie cannot be resolved (both exhausted cards), those card remains on the table. Winner will be determined by the number of cards owned.
    /*
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

                //Thanh modified here
                if (player1.empty() && player2.empty())
                {
                    cout << "\n\t\tBoth players have no more cards.";
                    cout << "\n\t\tTie breaker remains unresolved.";
                    cout << "\n\t\tCards remain on the table.\n";

                    waitForEnter();
                    break;
                }
                else if (player1.empty())
                {
                    cout << "\n\t\tPlayer2 takes all because Player1 has no more card.\n";
                    awardTable(player2Won, table);
                    waitForEnter();
                    break;
                }
                else if (player2.empty())
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

        //Thanh added something here
        int unresolvedCardTBK = static_cast<int>(table.size());
        //For debug

        int totalCards = 4 * cardsPerSuite;

        int accountedCards =
            static_cast<int>(
                player1.size() +
                player2.size() +
                player1Won.size() +
                player2Won.size() +
                table.size()
                );

        cout << "\n\tExpected cards: " << totalCards;
        cout << "\n\tAccounted cards: " << accountedCards;
        cout << "\n\tCards still on table: " << table.size();
        cout << "\n\tPlayer 1 total: " << p1Total;
        cout << "\n\tPlayer 2 total: " << p2Total;

        cout << "\n";
        if (unresolvedCardTBK > 0)
        {
            cout << "\t\tUnresolved cards remaining on the table: " << unresolvedCardTBK << ".\n";
        }

        if (p1Total > p2Total)
            cout << "\t\tPlayer1 wins the war with most number of cards (" << p1Total << ").\n";
        else if (p2Total > p1Total)
            cout << "\t\tPlayer2 wins the war with most number of cards (" << p2Total << ").\n";
        else
            cout << "\t\tThe war ends in a tie with " << p1Total << " cards each.\n";
    }
    */
    void play()
    {
        deque<int> table;
        bool inTieBreaker = false;
        bool unresolvedTie = false;
        bool stoppedByLimit = false;

        // Safety limit to prevent extremely long games
        const int MAX_ROUNDS = 10000;
        int roundCount = 0;

        while (!player1.empty() && !player2.empty())
        {
            if (roundCount >= MAX_ROUNDS)
            {
                stoppedByLimit = true;
                cout << "\n\t\tRound limit reached."
                    << "\n\t\tNo winner has been determined.\n";
                break;
            }

            ++roundCount;

            // Each player draws one face-up card
            int card1 = player1.front();
            player1.pop_front();

            int card2 = player2.front();
            player2.pop_front();

            // Place smaller card first, larger card second
            table.push_back(min(card1, card2));
            table.push_back(max(card1, card2));

            cout << "\n\t\tPlayer1: " << card1
                << "\tPlayer2: " << card2 << " -> ";

            // Player 1 wins
            if (card1 > card2)
            {
                if (inTieBreaker)
                    cout << "Player1 wins tie breaker!";
                else
                    cout << "Player1 wins!";

                awardTable(player1, table);
                inTieBreaker = false;

                cout << "\n";
                waitForEnter();
            }

            // Player 2 wins
            else if (card2 > card1)
            {
                if (inTieBreaker)
                    cout << "Player2 wins tie breaker!";
                else
                    cout << "Player2 wins!";

                awardTable(player2, table);
                inTieBreaker = false;

                cout << "\n";
                waitForEnter();
            }

            // Tie - War begins or continues
            else
            {
                if (inTieBreaker)
                    cout << "Tie breaker again!";
                else
                    cout << "Tie breaker begins!";

                inTieBreaker = true;

                // Need 3 face-down cards and 1 showdown card
                bool p1CanWar = player1.size() >= 4;
                bool p2CanWar = player2.size() >= 4;

                // Both players ran out of cards
                if (player1.empty() && player2.empty())
                {
                    cout << "\n\t\tBoth players have no more cards."
                        << "\n\t\tTie breaker remains unresolved."
                        << "\n\t\tCards remain on the table.\n";

                    unresolvedTie = true;
                    waitForEnter();
                    break;
                }

                // Player 1 ran out of cards
                else if (player1.empty())
                {
                    cout << "\n\t\tPlayer2 takes all because "
                        << "Player1 has no more cards.\n";

                    awardTable(player2, table);
                    waitForEnter();
                    break;
                }

                // Player 2 ran out of cards
                else if (player2.empty())
                {
                    cout << "\n\t\tPlayer1 takes all because "
                        << "Player2 has no more cards.\n";

                    awardTable(player1, table);
                    waitForEnter();
                    break;
                }

                // Player 1 cannot complete the bet
                else if (!p1CanWar && p2CanWar)
                {
                    cout << "\n\t\tPlayer1 does not have enough cards"
                        << " to complete the tie breaker."
                        << "\n\t\tPlayer2 takes all remaining cards.\n";

                    awardTable(player2, table);
                    awardTable(player2, player1);

                    waitForEnter();
                    break;
                }

                // Player 2 cannot complete the bet
                else if (!p2CanWar && p1CanWar)
                {
                    cout << "\n\t\tPlayer2 does not have enough cards"
                        << " to complete the tie breaker."
                        << "\n\t\tPlayer1 takes all remaining cards.\n";

                    awardTable(player1, table);
                    awardTable(player1, player2);

                    waitForEnter();
                    break;
                }

                // Neither player has enough cards
                else if (!p1CanWar && !p2CanWar)
                {
                    cout << "\n\t\tNeither player has enough cards"
                        << " to bet 3 face-down cards."
                        << "\n\t\tNext cards will determine the winner.\n";

                    waitForEnter();
                    continue;   // skip the face-down bet, just draw the next card
                }

                // Both players can complete the bet
                // Each player places 3 cards face-down
                for (int i = 0; i < 3; i++)
                {
                    table.push_back(player1.front());
                    player1.pop_front();

                    table.push_back(player2.front());
                    player2.pop_front();
                }

                cout << "\n\t\tBoth players bet 3 face-down cards."
                    << "\n\t\tNext cards will determine the winner.\n";

                waitForEnter();

                // Next iteration draws the showdown cards
            }
        }

        // Final card accounting
        int p1Total = static_cast<int>(player1.size());
        int p2Total = static_cast<int>(player2.size());
        int unresolvedCards = static_cast<int>(table.size());

        int expectedCards = 4 * cardsPerSuite;
        int accountedCards = p1Total + p2Total + unresolvedCards;

        cout << "\n\tExpected cards: " << expectedCards;
        cout << "\n\tAccounted cards: " << accountedCards;
        cout << "\n\tCards still on table: " << unresolvedCards;
        cout << "\n\tPlayer 1 total: " << p1Total;
        cout << "\n\tPlayer 2 total: " << p2Total;
        cout << "\n\tRounds played: " << roundCount;

        cout << "\n\n";

        if (unresolvedTie)
        {
            cout << "\t\tThe war ends with an unresolved tie.\n";
        }
        else if (stoppedByLimit)
        {
            cout << "\t\tThe game was stopped before "
                << "a winner was determined.\n";
        }
        else if (p1Total > p2Total)
        {
            cout << "\t\tPlayer1 wins the war with "
                << p1Total << " cards.\n";
        }
        else if (p2Total > p1Total)
        {
            cout << "\t\tPlayer2 wins the war with "
                << p2Total << " cards.\n";
        }
        else
        {
            cout << "\t\tThe war ends in a tie.\n";
        }
    }

};
