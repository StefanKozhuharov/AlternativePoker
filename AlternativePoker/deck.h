#ifndef DECK_H
#define DECK_H

void shuffleDeck(int* deck);
int getCardType(int card);
int getCardColour(int card);
void vizualizeCard(int card);
void vizualizePlayerHand(int hand[3], int currentPlayer);

#endif
