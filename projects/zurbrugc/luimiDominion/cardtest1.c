/* Author: Collin Zurbrugg, based on a template provided by Professor Jaki Sharief Shaik
** Date: 10/19/2018
** Description: A function to test the smithy card in dominion. */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void checkPiles(struct gameState *testGame, struct gameState *originalGame) {
	for (int i = 0; i < 27; i++)
	{
		if (testGame->supplyCount[i] != originalGame->supplyCount[i])
			printf("FAIL: Card pile %d changed\n", i);
	}
}

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
	int numPlayer = 4;
	int k[10] = { adventurer, council_room, feast, gardens, mine
			   , steward, smithy, village, baron, great_hall };
	struct gameState *benchmarkGame1 = newGame();
	struct gameState *benchmarkGame2 = newGame();
	struct gameState *benchmarkGame3 = newGame();
	struct gameState *testGame1 = newGame();
	struct gameState *testGame2 = newGame();
	struct gameState *testGame3 = newGame();
	initializeGame(numPlayer, k, 3333, benchmarkGame1);
	initializeGame(numPlayer, k, 3333, benchmarkGame2);
	initializeGame(numPlayer, k, 3333, benchmarkGame3);
	initializeGame(numPlayer, k, 3333, testGame1);
	initializeGame(numPlayer, k, 3333, testGame2);
	initializeGame(numPlayer, k, 3333, testGame3);
	int test1, test2, test3;
	int *fakeBonus = &numPlayer;

	int maxHandCount = 5;

	//test the smithy card
	//smithy is first card
	printf("Test 1\n");
	testGame1->hand[0][0] = smithy;
	benchmarkGame1->hand[0][0] = smithy;
	test1 = cardEffect(smithy, 0, 0, 0, testGame1, 0, fakeBonus);
	if (test1 == 0)
		printf("PASS: Card executed correctly\n");
	else
		printf("FAIL: Card returned with error of %d\n", test1);
	//test player
	if (testGame1->handCount[0] == benchmarkGame1->handCount[0] + 2)
		printf("PASS: Hand count updated");
	else
		printf("FAIL: Hand count incorrect; expected %d, actual %d\n", benchmarkGame1->handCount[0] + 2, testGame1->handCount[0]);
	if (testGame1->discardCount[0] + testGame1->deckCount[0] == benchmarkGame1->discardCount[0] + benchmarkGame1->deckCount[0] - 2)
		printf("PASS: Discard and deck counts updated\n");
	else
		printf("FAIL: Discard and deck counts wrong; expected %d, actual %d\n", 
			benchmarkGame1->discardCount[0] + benchmarkGame1->deckCount[0] - 2, testGame1->discardCount[0] + testGame1->deckCount[0]);

	//test rest of game
	checkOtherPlayers(testGame1, benchmarkGame1, numPlayer);
	checkPiles(testGame1, benchmarkGame1);

	//smithy is in middle
	printf("Test 2\n");
	testGame2->hand[0][2] = smithy;
	benchmarkGame2->hand[0][2] = smithy;
	test2 = cardEffect(smithy, 0, 0, 0, testGame2, 2, fakeBonus);
	if (test2 == 0)
		printf("PASS: Card executed correctly\n");
	else
		printf("FAIL: Card returned with error of %d\n", test2);
	//test player
	if (testGame2->handCount[0] == benchmarkGame2->handCount[0] + 2)
		printf("PASS: Hand count updated");
	else
		printf("FAIL: Hand count incorrect; expected %d, actual %d\n", benchmarkGame2->handCount[0] + 2, testGame2->handCount[0]);
	if (testGame2->discardCount[0] + testGame2->deckCount[0] == benchmarkGame2->discardCount[0] + benchmarkGame2->deckCount[0] - 2)
		printf("PASS: Discard and deck counts updated");
	else
		printf("FAIL: Discard and deck counts wrong; expected %d, actual %d\n",
			benchmarkGame2->discardCount[0] + benchmarkGame2->deckCount[0] - 2, testGame2->discardCount[0] + testGame2->deckCount[0]);

	//test rest of game
	checkOtherPlayers(testGame2, benchmarkGame2, numPlayer);
	checkPiles(testGame2, benchmarkGame2);

	//smithy is last card
	printf("Test 3\n");
	testGame3->hand[0][testGame3->handCount[0] - 1] = smithy;
	benchmarkGame3->hand[0][testGame3->handCount[0] - 1] = smithy;
	test3 = cardEffect(smithy, 0, 0, 0, testGame3, testGame3->handCount[0] - 1, fakeBonus);
	if (test3 == 0)
		printf("PASS: Card executed correctly\n");
	else
		printf("FAIL: Card returned with error of %d\n", test3);
	//test player
	if (testGame3->handCount[0] == benchmarkGame3->handCount[0] + 2)
		printf("PASS: Hand count updated\n");
	else
		printf("FAIL: Hand count incorrect; expected %d, actual %d\n", benchmarkGame3->handCount[0] + 2, testGame3->handCount[0]);
	if (testGame3->discardCount[0] + testGame3->deckCount[0] == benchmarkGame3->discardCount[0] + benchmarkGame3->deckCount[0] - 2)
		printf("PASS: Discard and deck counts updated\n");
	else
		printf("FAIL: Discard and deck counts wrong; expected %d, actual %d\n",
			benchmarkGame3->discardCount[0] + benchmarkGame3->deckCount[0] - 2, testGame3->discardCount[0] + testGame3->deckCount[0]);

	//test rest of game
	checkOtherPlayers(testGame3, benchmarkGame3, numPlayer);
	checkPiles(testGame3, benchmarkGame3);

	return 0;
}
