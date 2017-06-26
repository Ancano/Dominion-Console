#include "Player.h"

Player::Player(string playerName) {
	this->name = playerName;	
	this->victoryPoints = 0;
	this->money = 0;
	this->buys = 0;
	this->actions = 0;
}

string Player::getName(){
	return this->name;
}

void Player::addToDeck(Card* cardToAdd) {
	deck.push(cardToAdd);
}

void Player::addToHand(Card* cardToAdd)	{
	hand.push_back(cardToAdd);
}

void Player::addToDiscard(Card* cardToAdd){
	discardPile.push(cardToAdd);
}

void Player::buyCard(string cardToBuy) {
	int cardLocation = -1;
	for(int i = 0; i < board.size(); ++i) {
		if(board.at(i)->getName() == cardToBuy){
			cardLocation = i; //find the right card
		}
	}
	if( cardLocation >= 0 ) {
		//make sure player has enough money for the card
		if(board.at(cardLocation)->getPrice() <= this->money) {
			this->money -= board.at(cardLocation)->getPrice();
			addToDiscard(board.at(cardLocation));
			board.erase( board.begin() + cardLocation);
		}
	}
}

void Player::playAction(Card* cardToPlay) {
	bool cardInHand = false;
	for(int i = 0; i < hand.size(); ++i) {
		if(hand.at(i)->getName() == cardToPlay->getName()) {
			cardInHand = true;
		}
	}
	if(cardInHand) {
		downcastCard<ActionCard>(cardToPlay)->execute(); //action cards must be in players hand
	}
}

void Player::shuffleCards() {
	//make sure the deck is empty before shuffling
	if(this->deck.size() == 0){
		//move all cards from discard to the hand 
		while( !discardPile.empty() ) {
			this->addToHand(discardPile.top());
			this->discardPile.pop();
		}
		std::random_shuffle( hand.begin(), hand.end() ); //actually shuffle	
		while( !hand.empty() ) {
			//move everything from the hand to the deck
			this->addToDeck(hand.back());	
			hand.pop_back();
		}
	}
}

//Move a specified number of cards from the deck to the hand
void Player::drawCards(int numCards) { 

	if(numCards > deck.size()){
		numCards = deck.size();
	}

	for(int i = 0; i < numCards; ++i){
		addToHand(deck.top());
		deck.pop();
	}
	//count up the  money in the players hand for them
	for(int i = 0; i < this->hand.size();++i) {
		if(this->hand.at(i)->getName() == "Copper") {
			Copper *cptr = (Copper*)this->hand.at(i);
			this->money += cptr->getValue();	
		}
		if(this->hand.at(i)->getName() == "Silver") {
			Silver *sptr = (Silver*)this->hand.at(i);
			this->money += sptr->getValue();	
		}
		if(this->hand.at(i)->getName() == "Gold") {
			Gold *gptr = (Gold*)this->hand.at(i);
			this->money += gptr->getValue();	
		}
	}
}

void Player::discardCard(Card* cardToDiscard) {
	int cardLocation = -1;
	for(int i = 0; i < this->hand.size(); ++i) {
		if(this->hand.at(i)->getName() == cardToDiscard->getName()) {
			//Move the card to the discard pile and remove from the this->hand
			cardLocation = i;
		}
	}
	if(cardLocation >= 0) {
		discardPile.push(cardToDiscard); 
		this->hand.erase(this->hand.begin() + cardLocation);
	}
}

void Player::trashCard(Card* cardToTrash) {
	int cardLocation = -1;
	for(int i = 0; i < this->hand.size(); ++i) {
		if(this->hand.at(i)->getName() == cardToTrash->getName()) {
			//Move the card to the discard pile and remove from the this->hand
			cardLocation = i;
		}
	}
	if(cardLocation >= 0) {
		trash.push_back(cardToTrash);
		this->hand.erase(this->hand.begin() + cardLocation);
	}
}

void Player::discardDeck() {
	while(!deck.empty()) {
		addToDiscard(deck.top()); //move all cards from deck to discard pile
		deck.pop();
	}	
}

bool Player::cardInHand(Card* cardToCheck) {
	bool found = false;
	for(int i = 0; i < hand.size(); ++i) {
		if(cardToCheck->getName() == hand.at(i)->getName()) {
			found = true;
		}
	}
	return found;
}

void Player::addMoney(int amount) { 
	//give player specified amount of money
	money += amount;
}

void Player::addBuys(int amount) {
	buys += amount;
}

void Player::addActions(int amount) {
	actions += amount;
}

vector<Card*> Player::getHand() {
	return this->hand;
}

stack<Card*> Player::getDeck() {
	return this->deck;
}

int Player::getCurrentMoney() {
	return this->money;
}

unsigned int Player::getBuys() {
	return this->buys;
}

unsigned int Player::getActions() {
	//returns the number of actions that the player has
	return this->actions;
}

string Player::takeTurn() { 
	//cleanup phase?
	//this->money = 0;
	return this->name + " took their turn.";
}
