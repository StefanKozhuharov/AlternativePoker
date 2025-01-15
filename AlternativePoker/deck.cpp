#include <iostream>
#include "constants.h"
using namespace std;

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

int getCardType(int card) {

	return card % 8;

}

int getCardColour(int card) {

	return (card-1) / 8;

}

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

	}

}