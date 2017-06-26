#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include "Card.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

extern vector<Card*> board;
extern vector<Card*> trash;
template<class T>
extern T* downcastCard(Card* card);

class Player {
	public:
		Player(string playerName);
		void addToDeck(Card* cardToAdd);
		void addToHand(Card* cardToAdd);
		void addToDiscard(Card* CardToAdd);
		void buyCard(string cardToBuy); 
		void playAction(Card* cardToPlay);
		void shuffleCards();
		void drawCards(int numCards);
		void discardCard(Card* cardToDiscard);
		void trashCard (Card* cardToTrash);
		void discardDeck(); //used by chancellor card.
		bool cardInHand(Card* cardToCheck);
		//adders
		void addMoney(int amount);
		void addBuys(int amount);
		void addActions(int amount);
		//Accessors/Mutators
		string getName();
		vector<Card*> getHand(); 
		stack<Card*> getDeck();
		int getCurrentMoney();
		unsigned int getBuys();
		unsigned int getActions();

		string takeTurn();

	private:
		string name; //name of the player
		unsigned int victoryPoints; //number of victory points the player has
		unsigned int money; //money the player has 		
		unsigned int buys; //number of cards player can buy
		unsigned int actions; //number of actions that can be played
		
		vector<Card*> hand; //player's hand
		stack<Card*> deck; //player's deck
		stack<Card*> discardPile; //player's discard pile
			
};

#endif
