#include <string>
#include <iostream> //for terminal specific card pickers

using namespace std;

#ifndef CARD_H
#define CARD_H

class Card {

	public:
		Card();
		Card(const Card& other); // copy constructor
		Card(string cardName, int cardPrice);
		//Accessors
		string getName() const;
		int getPrice() const;
		string getType() const;
		//Mutators
		void setName(string cardName);
		void setPrice(int cardPrice);
	
	protected:
		string name;
		int price;
		string type;
	
};

//Our treasure card interface
class TreasureCard : public Card {
	public:
		virtual int getValue() = 0; //mark it as pure virtual
	protected:
		int value; // the value of the card.
};
//Our Action card interface
class ActionCard : public Card { 
	public:
		virtual void execute() = 0;
		virtual string getDescription() = 0;

	protected:
		string description;
};

class VictoryCard: public Card {
	public:
		virtual int getVictoryPoints() = 0; //mark it as pure virtual
	protected:
		int victoryPoints; // the value of the card.
};
//Treasure cards
class Copper: public TreasureCard {
	public:
		Copper();
		int getValue();
};

class Silver: public TreasureCard {
	public:
		Silver();
		int getValue();
};

class Gold: public TreasureCard {
	public:
		Gold();
		int getValue();
};

//Victory cards
class Estate: public VictoryCard {
	public:
		Estate();
		int getVictoryPoints();
};

class Duchy: public VictoryCard {
	public:
		Duchy();
		int getVictoryPoints();
};

class Province: public VictoryCard {
	public:
		Province();
		int getVictoryPoints();
};

//Action cards
class Cellar: public ActionCard {
	public:
		Cellar();
		void execute();
		string getDescription();
};

class Chapel: public ActionCard {
	public:
		Chapel();
		void execute();
		string getDescription();
};

class Moat: public ActionCard {
	public:
		Moat();
		void execute();
		string getDescription();
};

class Chancellor: public ActionCard {
	public:
		Chancellor();
		void execute();
		string getDescription();
};

class Village: public ActionCard {
	public:
		Village();
		void execute();
		string getDescription();
};

class Woodcutter: public ActionCard {
	public:
		Woodcutter();
		void execute();
		string getDescription();
};

class Workshop: public ActionCard {
	public:
		Workshop();
		void execute();
		string getDescription();
};

class Feast: public ActionCard {
	public:
		Feast();
		void execute();
		string getDescription();
};

class Moneylender: public ActionCard {
	public:
		Moneylender();
		void execute();
		string getDescription();
};

class Remodel: public ActionCard {
	public:
		Remodel();
		void execute();
		string getDescription();
};

class Smithy: public ActionCard {
	public:
		Smithy();
		void execute();
		string getDescription();
};

class Throneroom: public ActionCard {
	public:
		Throneroom();
		void execute();
		string getDescription();
};

class Councilroom: public ActionCard {
	public:
		Councilroom();
		void execute();
		string getDescription();
};

class Festival: public ActionCard {
	public:
		Festival();
		void execute();
		string getDescription();
};

class Laboratory: public ActionCard {
	public:
		Laboratory();
		void execute();
		string getDescription();
};

class Library: public ActionCard {
	public:
		Library();
		void execute();
		string getDescription();
};
#endif
