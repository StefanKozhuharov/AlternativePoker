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
* This file is made to merge functions needed in other files from deck.cpp
*
*/
#ifndef DECK_H
#define DECK_H

void shuffleDeck(int* deck);
int getCardType(int card);
int getCardColour(int card);
void vizualizeCard(int card);
void vizualizePlayerHand(int hand[3], int currentPlayer);

#endif
