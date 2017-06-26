#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include "conio.h"
#include "Card.h"
#include "Player.h"

using namespace std;

void showBoard(vector<Card*> playerBoard, int location);
void showHand(vector<Card*> playerHand);
void showStack(stack<Card*> cardStack); 
Card* getCardByName(string cardName);
void setUpBoard();

template<class T>T* downcastCard(Card* card); //do I even need this function?
unsigned int numCopper = 10;
unsigned int numSilver = 10;
unsigned int numGold = 10;
unsigned int numEstate = 10;
unsigned int numDuchy = 10;
unsigned int numProvince = 3;
unsigned int numCellar = 10;
unsigned int numChapel = 10;
unsigned int numMoat = 10;
unsigned int numChancellor = 10;
unsigned int numVillage = 10;
unsigned int numWoodcutter = 10;
unsigned int numWorkshop = 10;
unsigned int numFeast = 10;
unsigned int numMoneylender = 10;
unsigned int numRemodel = 10;
unsigned int numSmithy = 10;
unsigned int numThroneroom = 10;
unsigned int numCouncilroom= 10;
unsigned int numFestival = 10;
unsigned int numLaboratory = 10;
unsigned int numLibrary = 10;

//make these final?
Copper copper;
Silver silver;
Gold gold;	
Estate estate;
Duchy duchy;
Province province;
Cellar cellar;
Chapel chapel;
Moat moat;
Chancellor chancellor;
Village village;
Woodcutter woodcutter;
Workshop workshop;
Feast feast;
Moneylender moneylender;
Remodel remodel;
Smithy smithy;
Throneroom throneroom;
Councilroom councilroom;
Festival festival;
Laboratory laboratory;
Library library;

vector<Card*> board; //all the cards on the table
vector<Card*> trash; //trash pile
vector<Player> players; //all players in the game
Player* currentPlayer;//the current player 

int main() { 
	srand(time(NULL)); //Seed random number generator

	bool gameIsDone = false;

	char choice = '\0';

	setUpBoard();

	Player tyler("Tyler");
	Player jeb("Jeb");
	Player eddie("Eddie");
	players.push_back(tyler);
	players.push_back(jeb);
	players.push_back(eddie);

	for(int i = 0; i < players.size(); ++i){
		for(int j = 1; j <= 7; ++j){
			//Each player takes 7 copper cards to start
			players.at(i).addToDiscard(&copper);
		} 

		for(int k = 1; k <=3; ++k){
			players.at(i).addToDiscard(&estate); //Each player takes 3 estates to start
		}
		players.at(i).shuffleCards(); // each player shuffles their cards
	}

	while(!gameIsDone){
		cout << conio::clrscr();
		showBoard(board,0);
		int numProvinces = 0;

		//check if the province pile is empty and end game if true
		for(int i = 0; i < board.size();++i){
			if( board.at(i)->getName() == "Province" ) {
				numProvinces++;
			}
		}
		if(numProvinces <= 0){
			gameIsDone = true;
			break;
		}
		//make every player take their turn
		for(int i = 0; i < players.size(); ++i){
			cout <<	players[i].takeTurn() << endl;
		}

		currentPlayer = &players[0];
		cout << endl;
		cout << "money: " << currentPlayer->getCurrentMoney() << endl;
		cout << "buys: " << currentPlayer->getBuys() << endl;
		cout << "actions: " << currentPlayer->getActions() << endl;
		cout << "Your hand: " << endl;
		showHand(currentPlayer->getHand());
		//showBoard(players[0].getHand(), 25);
		cout << "what do you want to do?" << endl;
		cout << "(d)raw cards (s)huffle deck (b)uy card (p)lay card (v)iew card description" << endl;
		cin >> choice;
		switch(choice){
			case 'd': {
				int num = 0;
				cout << "how many?" << endl;
				cin >> num;
				currentPlayer->drawCards(num);
				cout << "drew " << num << " cards" << endl;
			}	break;
			case 's': {
				currentPlayer->shuffleCards();
				cout << "shuffled the cards" << endl;
			}	break;
			case 'b': {
				string cardName;
				cout << "what card do you want to buy?" << endl;
				cin >> cardName;
				currentPlayer->buyCard(cardName);
				break;
			}
			case 'p': {
				string cardName;
				cout << "what card?"<< endl; 
				cin >> cardName;
				Card* actionCard;
				for( int i = 0; i < board.size(); ++i) {
					if(board.at(i)->getName() == cardName) {
						actionCard = board[i];
					};
				}
				if(actionCard != NULL){ 
					currentPlayer->playAction(actionCard);

				}
				break;
			}
			case 'v': {
				string cardName;
				cout << "what card?"<< endl; 
				cin >> cardName;
				Card* theCard;
				for( int i = 0; i < board.size(); ++i) {
					if(board.at(i)->getName() == cardName) {
						theCard = board[i];
					};
				}
				if(theCard != NULL) {
					// downcast the generic Card* pointer to a ActionCard pointer so getDescription() can be called
					cout << downcastCard<ActionCard>(theCard)->getDescription() << endl;
					cin >> cardName;
				}
				break;
			}
		} 
	}
	cout << conio::clrscr();
	cout << "GAME OVER: hope you had fun!" << endl;
	return 0;
}

//Output a visual representation of what's on the board to the console
void showBoard(vector<Card*> playerBoard, int location) {
	int curlock = 0; //horizontal interval	
	int stacks = -1; //number of cards that are grouped together
	int loc = location; // the vertical location you want to print the card thing
	string tempCardName = "";
	for(int i = 0; i < playerBoard.size(); ++i){
		if(tempCardName != playerBoard.at(i)->getName())	{
			stacks++;
			tempCardName = playerBoard.at(i)->getName();
			int quantity = 0;
			for(int j = 0; j < playerBoard.size(); ++j){
				if(tempCardName	== playerBoard.at(j)->getName())
					quantity++;
			}
			if(stacks % 6 == 0 && stacks != 0) {
				//create a 'newline' of terminal cards every 4 
				loc += 9;
				curlock = 0;
			}
			cout << conio::gotoRowCol (loc + 1,16*curlock) << "---------------"<< endl;
			cout << conio::gotoRowCol (loc + 2,16*curlock) << "|" << setw(10)  << "(" << quantity << ")" <<"|" << endl;
			cout << conio::gotoRowCol (loc + 3,16*curlock) << "|" << setw(9) << tempCardName << "    |"<<  endl;
			cout << conio::gotoRowCol (loc + 4,16*curlock) <<  "|             |" << endl;
			cout << conio::gotoRowCol (loc + 5,16*curlock) <<  "|             |" << endl;
			cout << conio::gotoRowCol (loc + 6,16*curlock) <<  "|             |" << endl;
			cout << conio::gotoRowCol (loc + 7,16*curlock) <<  "|           " << playerBoard.at(i)->getPrice() << " |" << endl;
			if( playerBoard.at(i)->getType() == "Treasure") { 
				//if it's a treasure card color it yellow
				cout << conio::gotoRowCol (loc + 8,16*curlock) << "|" << conio::fgColor(conio::YELLOW) << setw(10) << playerBoard.at(i)->getType() << conio::resetAll() <<"   |"<< endl;
			}
			if( playerBoard.at(i)->getType() == "Victory") {
				//if it's a victory card color it green
				cout << conio::gotoRowCol (loc + 8,16*curlock) << "|" << conio::fgColor(conio::GREEN) << setw(10) << playerBoard.at(i)->getType() << conio::resetAll() <<"   |"<< endl;
			}
			if( playerBoard.at(i)->getType() == "Action") {
				//if it's an action card color it blue
				cout << conio::gotoRowCol (loc + 8,16*curlock) << "|" << conio::fgColor(conio::BLUE) << setw(10) << playerBoard.at(i)->getType() << conio::resetAll() <<"   |"<< endl;
			}
			if( playerBoard.at(i)->getType() == "Action - Reaction") {
				//if it's an action card color it blue
				cout << conio::gotoRowCol (loc + 8,16*curlock) << "|" << conio::fgColor(conio::BLUE) << setw(10) << "Action(R)" << conio::resetAll() <<"   |"<< endl;
			}
			cout << conio::gotoRowCol (loc + 9,16*curlock) << "---------------"<< endl;
			curlock++;
		};
	}	
}

//downcasts a Card pointer to an unknown subclass pointer T and returns
//it as type T.
template<class T>
T* downcastCard(Card* card) { 
	T* tptr = (T*)card;
	return tptr;
}
void setUpBoard() { 
	//set up the board with all the cards 
	//TODO:Allow user to select scenarios
	for(int i = 1; i <=numCopper; ++i){
		board.push_back(&copper);
	}
	for(int i = 1; i <= numSilver; ++i){
		board.push_back(&silver);
	}
	for(int i = 1; i <= numGold; ++i){
		board.push_back(&gold);
	}
	for(int i = 1; i <= numEstate; ++i){
		board.push_back(&estate);
	}
	for(int i = 1; i <= numDuchy; ++i){
		board.push_back(&duchy);
	}
	for(int i = 1; i <= numProvince; ++i){
		board.push_back(&province);
	}
	for(int i = 1; i <=numCellar; ++i){
		board.push_back(&cellar);
	}
	for(int i = 1; i <=numChapel; ++i){
		board.push_back(&chapel);
	}
	for(int i = 1; i <=numMoat; ++i){
		board.push_back(&moat);
	}
	for(int i = 1; i <=numChancellor; ++i){
		board.push_back(&chancellor);
	}
	for(int i = 1; i <=numVillage; ++i){
		board.push_back(&village);
	}
	for(int i = 1; i <=numWoodcutter; ++i){
		board.push_back(&woodcutter);
	}
	for(int i = 1; i <=numWorkshop; ++i){
		board.push_back(&workshop);
	}
	for(int i = 1; i <=numFeast; ++i){
		board.push_back(&feast);
	}
	for(int i = 1; i <=numMoneylender; ++i){
		board.push_back(&moneylender);
	}
	for(int i = 1; i <=numRemodel; ++i){
		board.push_back(&remodel);
	}
	for(int i = 1; i <=numSmithy; ++i){
		board.push_back(&smithy);
	}
	for(int i = 1; i <=numThroneroom; ++i){
		board.push_back(&throneroom);
	}
	for(int i = 1; i <=numCouncilroom; ++i){
		board.push_back(&councilroom);
	}
	for(int i = 1; i <=numFestival; ++i){
		board.push_back(&festival);
	}
	for(int i = 1; i <=numLaboratory; ++i){
		board.push_back(&laboratory);
	}
	for(int i = 1; i <=numLibrary; ++i){
		board.push_back(&library);
	}
}

void showHand(vector<Card*> playerHand) {
	for(int i = 0; i < playerHand.size(); ++i){
		cout << playerHand.at(i)->getName() + "\t";
	}
	cout << endl;

}

void showStack(stack<Card*> cardStack) { 
	while ( !cardStack.empty() ) {
		cout << cardStack.top()->getName() << endl;
		cardStack.pop();
	}
}

//Gets pointer to a card object by name
Card* getCardByName(string cardName) {
	Card* pickedCard = NULL;
	for( int i = 0; i < board.size(); ++i) {
		if(board.at(i)->getName() == cardName) {
			pickedCard = board[i]; //find the card .
		};
	}
	return pickedCard; 
}

