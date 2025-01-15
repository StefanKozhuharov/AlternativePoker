#ifndef DECK_H
#define DECK_H

extern int cards[32];

int* shuffleDeck(int* deck);
int getCardType(int card);
int getCardColour(int card);

#endif
