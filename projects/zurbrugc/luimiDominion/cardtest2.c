/* Author: Collin Zurbrugg, based on a template provided by Professor Jaki Sharief Shaik
** Date: 10/20/2018
** Description: A function to test the adventurer card in dominion. */

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

int treasureCountHand(struct gameState *G) {
	//counts how much treasure is in player 0's hand
	int count = 0;
	for (int i = 0; i < G->handCount[0]; i++) {
		if (G->hand[0][i] == copper || G->hand[0][i] == silver || G->hand[0][i] == gold)
			count++;
	}
	return count;
}

int treasureCountD(struct gameState *G) {
	//counts how much treasure is in player 0's deck and discard
	int count = 0;
	for (int i = 0; i < G->deckCount[0]; i++) {
		if (G->deck[0][i] == copper || G->deck[0][i] == silver || G->deck[0][i] == gold)
			count++;
	}
	for (int j = 0; j < G->discardCount[0]; j++) {
		if (G->discard[0][j] == copper || G->discard[0][j] == silver || G->discard[0][j] == gold)
			count++;
	}
	return count;
}

int main() {
	int seed = 8888;
	int numPlayer = 3;
	int *fakeBonus = &seed; //this value isn't actually used, so I gave it a placeholder
	int k[10] = { adventurer, council_room, feast, gardens, mine
			   , steward, smithy, village, baron, great_hall };
	struct gameState *benchmarkGame1 = newGame();
	struct gameState *benchmarkGame2 = newGame();
	struct gameState *benchmarkGame3 = newGame();
	struct gameState *testGame1 = newGame();
	struct gameState *testGame2 = newGame();
	struct gameState *testGame3 = newGame();
	initializeGame(numPlayer, k, seed, benchmarkGame1);
	initializeGame(numPlayer, k, seed, benchmarkGame2);
	initializeGame(numPlayer, k, seed, benchmarkGame3);
	initializeGame(numPlayer, k, seed, testGame1);
	initializeGame(numPlayer, k, seed, testGame2);
	initializeGame(numPlayer, k, seed, testGame3);
	int test1, test2, test3;

	//create game states
	//test without shuffle
	testGame1->deck[0][0] = copper;
	benchmarkGame1->deck[0][0] = copper;
	testGame1->deck[0][1] = copper;
	benchmarkGame1->deck[0][1] = copper;
	testGame1->deck[0][2] = adventurer;
	benchmarkGame1->deck[0][2] = adventurer;

	//test
	printf("Test 1: No shuffle\n");
	test1 = cardEffect(adventurer, 0, 0, 0, testGame1, 2, fakeBonus);
	//test return value
	if (test1 == 0)
		printf("PASS: Function executed correctly\n");
	else
		printf("FAIL: Function return with error of %d\n", test1);
	//test hand
	if (treasureCountHand(testGame1) == treasureCountHand(benchmarkGame1) + 2)
		printf("PASS: Treasure added to hand\n");
	else
		printf("FAIL: Treasure added to hand incorrectly\n");
	//test hand count +2 treasure, -1 for the adventurer
	if (testGame1->handCount[0] == benchmarkGame1->handCount[0] + 1)
		printf("PASS: Hand count updated\n");
	else
		printf("FAIL: Hand count incorrect, expected %d, actually %d\n", benchmarkGame1->handCount[0] + 1, testGame1->handCount[0]);
	//test deck and discard
	if (treasureCountD(testGame1) == treasureCountD(benchmarkGame1) - 2)
		printf("PASS: Treasure removed from discard and deck correctly\n");
	else
		printf("FAIL: Treasure removed from discard and deck incorrectly\n");
	//test deck and discard count; -2 for treasures, +1 for the adventurer
	if (testGame1->deckCount[0] + testGame1->discardCount[0] == benchmarkGame1->deckCount[0] + benchmarkGame1->discardCount[0] - 1)
		printf("PASS: Cards discarded correctly\n");
	else {
		printf("FAIL: Cards not discarded correctly\n");
		printf("Discard count plus deck count should be %d, actually %d\n", 
				benchmarkGame1->deckCount[0] + benchmarkGame1->discardCount[0] - 1, testGame1->deckCount[0] + testGame1->discardCount[0]);
	}
	//check rest of game
	checkPiles(testGame1, benchmarkGame1);
	checkOtherPlayers(testGame1, benchmarkGame1, numPlayer);

	//test with shuffle
	//no treasure in the deck
	for (int c = 0; c < benchmarkGame2->deckCount[0]; c++) {
		testGame2->deck[0][c] = baron;
		benchmarkGame2->deck[0][c] = baron;
	}
	//add treasure to the discard
	benchmarkGame2->discard[0][0] = silver;
	testGame2->discard[0][0] = silver;
	benchmarkGame2->discard[0][1] = silver;
	testGame2->discard[0][1] = silver;
	benchmarkGame2->discardCount[0] = benchmarkGame2->discardCount[0] + 2;
	testGame2->discardCount[0] = testGame2->discardCount[0] + 2;
	testGame2->deck[0][2] = adventurer;
	benchmarkGame2->deck[0][2] = adventurer;

	//test
	printf("Test 2: with shuffle\n");
	test2 = cardEffect(adventurer, 0, 0, 0, testGame2, 2, fakeBonus);
	//test return value
	if (test2 == 0)
		printf("PASS: Function executed correctly\n");
	else
		printf("FAIL: Function return with error of %d\n", test2);
	//test hand
	if (treasureCountHand(testGame2) == treasureCountHand(benchmarkGame2) + 2)
		printf("PASS: Treasure added to hand\n");
	else
		printf("FAIL: Treasure added to hand incorrectly\n");
	//test hand count +2 treasure, -1 for the adventurer
	if (testGame2->handCount[0] == benchmarkGame2->handCount[0] + 1)
		printf("PASS: Hand count updated\n");
	else
		printf("FAIL: Hand count incorrect, expected %d, actually %d\n", benchmarkGame2->handCount[0] + 1, testGame2->handCount[0]);
	//test deck and discard
	if (treasureCountD(testGame2) == treasureCountD(benchmarkGame2) - 2)
		printf("PASS: Treasure removed from discard and deck correctly\n");
	else
		printf("FAIL: Treasure removed from discard and deck incorrectly\n");
	//test deck and discard count; -2 for treasures, +1 for the adventurer
	if (testGame2->deckCount[0] + testGame2->discardCount[0] == benchmarkGame2->deckCount[0] + benchmarkGame2->discardCount[0] - 1)
		printf("PASS: Cards discarded correctly\n");
	else {
		printf("FAIL: Cards not discarded correctly\n");
		printf("Discard count plus deck count should be %d, actually %d\n",
			benchmarkGame2->deckCount[0] + benchmarkGame2->discardCount[0] - 1, testGame2->deckCount[0] + testGame2->discardCount[0]);
	}
	//check rest of game
	checkPiles(testGame2, benchmarkGame2);
	checkOtherPlayers(testGame2, benchmarkGame2, numPlayer);

	//test not enough treasure
	//no treasure in the deck
	printf("Test 3: Insufficient treasure\n");
	for (int d = 0; d < benchmarkGame3->deckCount[0]; d++) {
		testGame3->deck[0][d] = baron;
		benchmarkGame3->deck[0][d] = baron;
	}
	//add one treasure to the discard
	benchmarkGame3->discard[0][0] = gold;
	testGame3->discard[0][0] = gold;
	benchmarkGame3->discardCount[0]++;
	testGame3->discardCount[0]++;
	testGame3->deck[0][2] = adventurer;
	benchmarkGame3->deck[0][2] = adventurer;

	//test
	test3 = cardEffect(adventurer, 0, 0, 0, testGame3, 2, fakeBonus);
	//test return value
	if (test3 == 0)
		printf("PASS: Function executed correctly\n");
	else
		printf("FAIL: Function return with error of %d\n", test3);
	//test hand
	//there should only be one more treasure, since there is only one treasure in the deck
	if (treasureCountHand(testGame3) == treasureCountHand(benchmarkGame3) + 1)
		printf("PASS: Treasure added to hand\n");
	else
		printf("FAIL: Treasure added to hand incorrectly\n");
	//test hand count +1 treasure, -1 for the adventurer
	if (testGame3->handCount[0] == benchmarkGame3->handCount[0])
		printf("PASS: Hand count updated\n");
	else
		printf("FAIL: Hand count incorrect, expected %d, actually %d\n", benchmarkGame3->handCount[0], testGame3->handCount[0]);
	//test deck and discard
	if (treasureCountD(testGame3) == treasureCountD(benchmarkGame3) - 1)
		printf("PASS: Treasure removed from discard and deck correctly\n");
	else
		printf("FAIL: Treasure removed from discard and deck incorrectly\n");
	//test deck and discard count; -1 for treasures, +1 for the adventurer
	if (testGame3->deckCount[0] + testGame3->discardCount[0] == benchmarkGame3->deckCount[0] + benchmarkGame3->discardCount[0])
		printf("PASS: Cards discarded correctly\n");
	else {
		printf("FAIL: Cards not discarded correctly\n");
		printf("Discard count plus deck count should be %d, actually %d\n",
			benchmarkGame3->deckCount[0] + benchmarkGame3->discardCount[0], testGame3->deckCount[0] + testGame3->discardCount[0]);
	}
	//check rest of game
	checkPiles(testGame3, benchmarkGame3);
	checkOtherPlayers(testGame3, benchmarkGame3, numPlayer);

	return 0;
}