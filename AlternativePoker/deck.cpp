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