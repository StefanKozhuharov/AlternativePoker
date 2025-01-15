#include <iostream>
#include "constants.h"
using namespace std;

int cards[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

int* shuffleDeck(int* deck) {

	srand(time(NULL));
	for (int i = 0; i < timesToShuffle; i++) {
		int firstCard = rand() % 32;
		int secondCard = rand() % 32;
		int temp = deck[firstCard];
		deck[firstCard] = deck[secondCard];
		deck[secondCard] = temp;
	}

	return deck;

}

int getCardType(int card) {

	return card % 8;

}

int getCardColour(int card) {

	return (card-1) / 8;

}
