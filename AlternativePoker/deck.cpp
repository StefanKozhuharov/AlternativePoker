/**
*
* Solution to course project #10
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Stefan Kozhuharov
* @idnumber 9MI0600529
* @compiler VC
*
* This file is made to run functions related to the deck
*
*/
#include <iostream>
#include "constants.h"
using namespace std;
//shuffles the deck by selecting two random cards and swapping them around a set number of times
void shuffleDeck(int* deck) {

	srand(time(NULL));
	for (int i = 0; i < timesToShuffle; i++) {
		int firstCard = rand() % 32;
		int secondCard = rand() % 32;
		int temp = deck[firstCard];
		deck[firstCard] = deck[secondCard];
		deck[secondCard] = temp;
	}

}
//returns the type of card we are looking at by checking it's remainder when dividing by 8 (our first card is a 7 so a 1 would actually be a 7, our second card is 8 so a 2 would be 8 etc.
int getCardType(int card) {

	return card % 8;

}
//returns the colour of a card by dividing by 8, we remove 1 beforehand because when we reach the ace of spades which would be a 32 we would get a 4 when every other spade is a 3 and since this -1 doesn't effect any other case it completely removes our only problem
int getCardColour(int card) {

	return (card-1) / 8;

}
//vizualizes the cards depending on the value given (1 - SEVEN, 2 - EIGHT, 3 - NINE, 4 - TEN, 5 - JACK, 6 - QUEEN, 7 - KING, 0 - ACE; 0 - CLUBS, 1 - DIAMONDS, 2 - HEARTS, 3 - SPADES) 
void vizualizeCard(int card) {

	switch (getCardType(card)) {

	case ACE:
		cout << "Ace ";
		break;
	case SEVEN:
		cout << "Seven ";
		break;
	case EIGHT:
		cout << "Eight ";
		break;
	case NINE:
		cout << "Nine ";
		break;
	case TEN:
		cout << "Ten ";
		break;
	case JACK:
		cout << "Jack ";
		break;
	case QUEEN:
		cout << "Queen ";
		break;
	case KING:
		cout << "King ";
		break;
	default:
		cout << "Something went wrong!";

	}

	cout << "of ";

	switch (getCardColour(card)) {

	case CLUB:
		cout << "Clubs";
		break;
	case DIAMOND:
		cout << "Diamonds";
		break;
	case HEART:
		cout << "Hearts";
		break;
	case SPADE:
		cout << "Spades";
		break;
	default:
		cout << "Something went wrong!";

	}

}

void vizualizePlayerHand(int hand[3], int currentPlayer){

	for (int i = 0; i < 3; i++) {

		vizualizeCard(hand[i]);
		cout << endl;

	}

}