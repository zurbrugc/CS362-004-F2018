/* FIXME: comment block*/
/* This code is based on a template provided by Professor Jaki Sharief Shaik*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void checkOtherPlayers(struct gameState *testGame, struct gameState *originalGame, int numPlayer) {
	for (int playercounter = 1; playercounter < numPlayer; playercounter++) {

		printf("Now testing player %d\n", playercounter);
		//for loop for deck
		for (int deckcounter = 0; deckcounter < MAX_DECK; deckcounter++) {
			if (testGame->deck[playercounter][deckcounter] != originalGame->deck[playercounter][deckcounter])
				printf("FAIL: Deck position %d not the same\n", deckcounter);
		}

		if (testGame->deckCount[playercounter] == originalGame->deckCount[playercounter])
			printf("PASS: Deck count updated\n");
		else {
			printf("FAIL: Deck count not updated\n");
			printf("Should be %d, actually %d\n", originalGame->deckCount[playercounter], testGame->deckCount[playercounter]);
		}

		//check player's hand
		for (int handcounter = 0; handcounter < MAX_HAND; handcounter++) {
			if (testGame->hand[playercounter][handcounter] != originalGame->hand[playercounter][handcounter])
				printf("FAIL: Hand position %d not the same\n", handcounter);
		}

		//check player's hand count
		if (testGame->handCount[playercounter] == originalGame->handCount[playercounter])
			printf("PASS: Hand count not updated\n");
		else {
			printf("FAIL: Hand count updated\n");
			printf("Should be %d, actually %d\n", originalGame->handCount[playercounter], testGame->handCount[playercounter]);
		}

		//check player's discard
		for (int discardcounter = 0; discardcounter < MAX_DECK; discardcounter++) {
			if (testGame->discard[playercounter][discardcounter] != originalGame->discard[playercounter][discardcounter])
				printf("FAIL: Discard position %d not the same\n", discardcounter);
		}

		//check player's discard count
		if (testGame->discardCount[playercounter] == originalGame->discardCount[playercounter])
			printf("PASS: Discard count not updated\n");
		else {
			printf("FAIL: Discard count updated\n");
			printf("Should be %d, actually %d\n", originalGame->discardCount[playercounter], testGame->discardCount[playercounter]);
		}
	}
}

int main() {
	int i;
	int numPlayer = 3;
	int k[10] = { adventurer, council_room, feast, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState *G = newGame();
	struct gameState *testGame1 = newGame();
	struct gameState *testGame2 = newGame();
	struct gameState *testGame3 = newGame();
	struct gameState *testGame4 = newGame();

	//initialize game states
	initializeGame(numPlayer, k, 144, G);
	initializeGame(numPlayer, k, 144, testGame1);
	initializeGame(numPlayer, k, 144, testGame2);
	initializeGame(numPlayer, k, 144, testGame3);
	initializeGame(numPlayer, k, 144, testGame4);

	G->supplyCount[smithy] = 0;
	testGame1->supplyCount[smithy] = 0;
	testGame2->supplyCount[smithy] = 0;
	testGame3->supplyCount[smithy] = 0;
	testGame4->supplyCount[smithy] = 0;

	int test1, test2, test3, test4;

	//run the function: gainCard
	//toFlag = 1; card is added to player's deck
	printf("Test 1\n\n");
	test1 = gainCard(baron, testGame1, 1, 0);
	if (test1 == 0)
		printf("PASS: Function was successful\n");
	else
		printf("FAIL: Function was unsuccessful\n");
	printf("Now testing player 0\n");

	//check player's deck & deck count
	if (testGame1->deck[0][testGame1->deckCount[0] - 1 ] == baron)
		printf("PASS: Card added properly\n");
	else
		printf("FAIL: Card not added properly\n");

	//for loop for rest of deck
	for (int deckcounter = 0; deckcounter < MAX_DECK; deckcounter++) {
		if (testGame1->deck[0][deckcounter] != G->deck[0][deckcounter] && deckcounter != testGame1->deckCount[0] - 1)
			printf("FAIL: Deck position %d not the same\n", deckcounter);
	}

	if (testGame1->deckCount[0] == G->deckCount[0] + 1)
		printf("PASS: Deck count updated\n");
	else {
		printf("FAIL: Deck count not updated\n");
		printf("Should be %d, actually %d\n", G->deckCount[0] + 1, testGame1->deckCount[0]);
	}

	//check player's hand
	for (int handcounter = 0; handcounter < MAX_HAND; handcounter++) {
		if (testGame1->hand[0][handcounter] != G->hand[0][handcounter])
			printf("FAIL: Hand position %d not the same\n", handcounter);
	}

	//check player's hand count
	if (testGame1->handCount[0] == G->handCount[0])
		printf("PASS: Hand count not updated\n");
	else {
		printf("FAIL: Hand count updated\n");
		printf("Should be %d, actually %d\n", G->handCount[0], testGame1->handCount[0]);
	}

	//check player's discard
	for (int discardcounter = 0; discardcounter < MAX_DECK; discardcounter++) {
		if (testGame1->discard[0][discardcounter] != G->discard[0][discardcounter])
			printf("FAIL: Discard position %d not the same\n", discardcounter);
	}

	//check player's discard count
	if (testGame1->discardCount[0] == G->discardCount[0])
		printf("PASS: Discard count not updated\n");
	else {
		printf("FAIL: Discard count updated\n");
		printf("Should be %d, actually %d\n", G->discardCount[0], testGame1->discardCount[0]);
	}
	//do all that for the other players
	checkOtherPlayers(testGame1, G, numPlayer);

	//toFlag = 2; card is added to hand
	printf("Test 2\n\n");
	test2 = gainCard(baron, testGame2, 2, 0);
	if (test2 == 0)
		printf("PASS: Function was successful\n");
	else
		printf("FAIL: Function was unsuccessful\n");
	printf("Now testing player 0\n");

	//for loop deck
	for (int deckcounter = 0; deckcounter < MAX_DECK; deckcounter++) {
		if (testGame2->deck[0][deckcounter] != G->deck[0][deckcounter])
			printf("FAIL: Deck position %d not the same\n", deckcounter);
	}

	if (testGame2->deckCount[0] == G->deckCount[0])
		printf("PASS: Deck count not updated\n");
	else {
		printf("FAIL: Deck count updated\n");
		printf("Should be %d, actually %d\n", G->deckCount[0], testGame2->deckCount[0]);
	}

	//check player's hand

	if (testGame2->hand[0][G->handCount[0]] == baron)
		printf("PASS: Card added properly\n");
	else
		printf("FAIL: Card not added properly\n");

	for (int handcounter = 0; handcounter < MAX_HAND; handcounter++) {
		if (testGame2->hand[0][handcounter] != G->hand[0][handcounter])
			printf("FAIL: Hand position %d not the same\n", handcounter);
		if (handcounter == G->handCount[0] - 1) //skip the changed card
			handcounter++;
	}

	//check player's hand count
	if (testGame2->handCount[0] == G->handCount[0] + 1)
		printf("PASS: Hand count updated\n");
	else {
		printf("FAIL: Hand count not updated\n");
		printf("Should be %d, actually %d\n", G->handCount[0] + 1, testGame2->handCount[0]);
	}

	//check player's discard
	for (int discardcounter = 0; discardcounter < MAX_DECK; discardcounter++) {
		if (testGame2->discard[0][discardcounter] != G->discard[0][discardcounter])
			printf("FAIL: Discard position %d not the same\n", discardcounter);
	}

	//check player's discard count
	if (testGame2->discardCount[0] == G->discardCount[0])
		printf("PASS: Discard count not updated\n");
	else {
		printf("FAIL: Discard count updated\n");
		printf("Should be %d, actually %d\n", G->discardCount[0], testGame2->discardCount[0]);
	}
	//do all that for the other players
	checkOtherPlayers(testGame2, G, numPlayer);
	
	
	//toFlag = 0; card is added to player's discard
	printf("Test 3\n\n");
	test3 = gainCard(baron, testGame3, 0, 0);
	if (test3 == 0)
		printf("PASS: Function was successful\n");
	else
		printf("FAIL: Function was unsuccessful\n");
	printf("Now testing player 0\n");

	//for loop deck
	for (int deckcounter = 0; deckcounter < MAX_DECK; deckcounter++) {
		if (testGame3->deck[0][deckcounter] != G->deck[0][deckcounter])
			printf("FAIL: Deck position %d not the same\n", deckcounter);
	}

	if (testGame3->deckCount[0] == G->deckCount[0])
		printf("PASS: Deck count not updated\n");
	else {
		printf("FAIL: Deck count updated\n");
		printf("Should be %d, actually %d\n", G->deckCount[0], testGame3->deckCount[0]);
	}

	//check player's hand
	for (int handcounter = 0; handcounter < MAX_HAND; handcounter++) {
		if (testGame3->hand[0][handcounter] != G->hand[0][handcounter])
			printf("FAIL: Hand position %d not the same\n", handcounter);
	}

	//check player's hand count
	if (testGame3->handCount[0] == G->handCount[0])
		printf("PASS: Hand count not updated\n");
	else {
		printf("FAIL: Hand count updated\n");
		printf("Should be %d, actually %d\n", G->handCount[0], testGame3->handCount[0]);
	}

	//check player's discard
	if (testGame3->discard[0][0] == baron)
		printf("PASS: Card discarded correctly\n");
	else
		printf("FAIL: Card not discarded correctly\n");

	for (int discardcounter = 1; discardcounter < MAX_DECK; discardcounter++) {
		if (testGame3->discard[0][discardcounter] != G->discard[0][discardcounter])
			printf("FAIL: Discard position %d not the same\n", discardcounter);
	}

	//check player's discard count
	if (testGame3->discardCount[0] == G->discardCount[0] + 1)
		printf("PASS: Discard count updated\n");
	else {
		printf("FAIL: Discard count not updated\n");
		printf("Should be %d, actually %d\n", G->discardCount[0] + 1, testGame3->discardCount[0]);
	}
	//do all that for the other players
	checkOtherPlayers(testGame3, G, numPlayer);
	
	
	//supply is empty; card is added nowhere
	printf("Test 4");
	test4 = gainCard(smithy, testGame4, 1, 0);
	if (test4 == -1)
		printf("PASS: Function was unsuccessful\n");
	else
		printf("FAIL: Function was successful\n");
	printf("Now testing player 0\n");

	//for loop deck
	for (int deckcounter = 0; deckcounter < MAX_DECK; deckcounter++) {
		if (testGame4->deck[0][deckcounter] != G->deck[0][deckcounter])
			printf("FAIL: Deck position %d not the same\n", deckcounter);
	}

	if (testGame4->deckCount[0] == G->deckCount[0])
		printf("PASS: Deck count not updated\n");
	else {
		printf("FAIL: Deck count updated\n");
		printf("Should be %d, actually %d\n", G->deckCount[0], testGame4->deckCount[0]);
	}

	//check player's hand
	for (int handcounter = 0; handcounter < MAX_HAND; handcounter++) {
		if (testGame4->hand[0][handcounter] != G->hand[0][handcounter])
			printf("FAIL: Hand position %d not the same\n", handcounter);
	}

	//check player's hand count
	if (testGame4->handCount[0] == G->handCount[0])
		printf("PASS: Hand count not updated\n");
	else {
		printf("FAIL: Hand count updated\n");
		printf("Should be %d, actually %d\n", G->handCount[0], testGame4->handCount[0]);
	}

	//check player's discard
	for (int discardcounter = 0; discardcounter < MAX_DECK; discardcounter++) {
		if (testGame4->discard[0][discardcounter] != G->discard[0][discardcounter])
			printf("FAIL: Discard position %d not the same\n", discardcounter);
	}

	//check player's discard count
	if (testGame4->discardCount[0] == G->discardCount[0])
		printf("PASS: Discard count not updated\n");
	else {
		printf("FAIL: Discard count updated\n");
		printf("Should be %d, actually %d\n", G->discardCount[0], testGame4->discardCount[0]);
	}
	//do all that for the other players
	checkOtherPlayers(testGame4, G, numPlayer);

	return 0;
}