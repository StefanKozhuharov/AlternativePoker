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
* This file is made to store structures
*
*/
#ifndef STRUCTURES_H
#define STRUCTURES_H
//we want to keep track of a player's hand so we can check their score, their balance so we know what they can bid and if they have busted out, their current bid so we know what other players can bid and their score so we can decide the winner
struct player {

	int hand[3];
	int balance;
	int currentBid;
	int score;

};

#endif
