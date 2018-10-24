/* Author: Collin Zurbrugg, based on a template provided by Professor Jaki Sharief Shaik
** Date: 10/20/2018
** Description: A function to test the salvager card in dominion. */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int cardCountHand(struct gameState *G, int card) {
	//counts how much treasure is in player 0's hand
	int count = 0;
	for (int i = 0; i < G->handCount[0]; i++) {
		if (G->hand[0][i] == card)
			count++;
	}
	return count;
}

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
	int seed = 8888;
	int numPlayer = 4;
	int *bonus = &seed;
	int k[10] = { adventurer, council_room, feast, gardens, mine
			   , steward, smithy, village, baron, great_hall };
	struct gameState *benchmarkGame1 = newGame();
	struct gameState *benchmarkGame2 = newGame();
	struct gameState *benchmarkGame3 = newGame();
	struct gameState *benchmarkGame4 = newGame();
	struct gameState *testGame1 = newGame();
	struct gameState *testGame2 = newGame();
	struct gameState *testGame3 = newGame();
	struct gameState *testGame4 = newGame();
	initializeGame(numPlayer, k, seed, benchmarkGame1);
	initializeGame(numPlayer, k, seed, benchmarkGame2);
	initializeGame(numPlayer, k, seed, benchmarkGame3);
	initializeGame(numPlayer, k, seed, benchmarkGame4);
	initializeGame(numPlayer, k, seed, testGame1);
	initializeGame(numPlayer, k, seed, testGame2);
	initializeGame(numPlayer, k, seed, testGame3);
	initializeGame(numPlayer, k, seed, testGame4);
	int test1, test2, test3, test4;
	int deckcounter;

	//test trashing a copper from beginning
	testGame1->hand[0][0] = copper;
	benchmarkGame1->hand[0][0] = copper;
	testGame1->hand[0][1] = salvager;
	benchmarkGame1->hand[0][1] = salvager;
	test1 = cardEffect(salvager, 0, -99, -99, testGame1, 1, bonus);
	//test return value
	if (test1 == 0)
		printf("PASS: Function returned correctly\n");
	else
		printf("FAIL: Function returned error of %d\n", test1);
	//test buy change
	if (testGame1->numBuys == benchmarkGame1->numBuys + 1)
		printf("PASS: Buys updated correctly\n");
	else
		printf("FAIL: Expected %d buys, actual: %d buys\n", benchmarkGame1->numBuys + 1, testGame1->numBuys);
	//test gold change
	if (testGame1->coins == benchmarkGame1->coins)
		printf("PASS: Coins updated correctly\n");
	else
		printf("FAIL: Expected %d coins, actual: %d coins\n", benchmarkGame1->coins, testGame1->coins);
	//test that card is removed
	if (cardCountHand(testGame1, copper) == cardCountHand(benchmarkGame1, copper) - 1)
		printf("PASS: Card removed\n");
	else
		printf("FAIL: Expected %d coppers; actual: %d coppers\n", cardCountHand(benchmarkGame1, copper) - 1, cardCountHand(testGame1, copper));
	//test hand count (two less for salvager and trashed card
	if (testGame1->handCount[0] == benchmarkGame1->handCount[0] - 2)
		printf("PASS: Hand count correct\n");
	else
		printf("FAIL: Expected hand count to be %d, actual: %d\n", benchmarkGame1->handCount[0] - 2, testGame1->handCount[0]);
	//test discard count (salvager is discarded)
	if (testGame1->discardCount[0] == benchmarkGame1->discardCount[0])
		printf("PASS: Discard count correct\n");
	else
		printf("FAIL: Expected discard count to be %d, actual: %d\n", benchmarkGame1->discardCount[0], testGame1->discardCount[0]);
	//test that deck is same
	for (deckcounter = 0; deckcounter < MAX_DECK; deckcounter++) {
		if (testGame1->deck[0][deckcounter] != benchmarkGame1->deck[0][deckcounter])
			printf("FAIL: Deck position %d not the same\n", deckcounter);
	}
	//test deck count
	if (testGame1->deckCount[0] == benchmarkGame1->deckCount[0])
		printf("PASS: Deck count correct\n");
	else
		printf("FAIL: Expected deck count to be %d, actual: %d\n", benchmarkGame1->deckCount[0], testGame1->deckCount[0]);
	checkOtherPlayers(testGame1, benchmarkGame1, numPlayer);
	checkPiles(testGame1, benchmarkGame1);

	//test trashing a feast from middle
	testGame2->hand[0][3] = feast;
	benchmarkGame2->hand[0][3] = feast;
	testGame2->hand[0][0] = salvager;
	benchmarkGame2->hand[0][0] = salvager;
	test2 = cardEffect(salvager, 3, -99, -99, testGame2, 0, bonus);
	//test return value
	if (test2 == 0)
		printf("PASS: Function returned correctly\n");
	else
		printf("FAIL: Function returned error of %d\n", test2);
	//test buy change
	if (testGame2->numBuys == benchmarkGame2->numBuys + 1)
		printf("PASS: Buys updated correctly\n");
	else
		printf("FAIL: Expected %d buys, actual: %d buys\n", benchmarkGame2->numBuys + 1, testGame2->numBuys);
	//test gold change
	if (testGame2->coins == benchmarkGame2->coins + 4)
		printf("PASS: Coins updated correctly\n");
	else
		printf("FAIL: Expected %d coins, actual: %d coins\n", benchmarkGame2->coins + 4, testGame2->coins);
	//test that card is removed
	if (cardCountHand(testGame2, feast) == cardCountHand(benchmarkGame2, feast) - 1)
		printf("PASS: Card removed\n");
	else
		printf("FAIL: Expected %d coppers; actual: %d coppers\n", cardCountHand(benchmarkGame2, feast) - 1, cardCountHand(testGame2, feast));
	//test hand count (two less for salvager and trashed card
	if (testGame2->handCount[0] == benchmarkGame2->handCount[0] - 2)
		printf("PASS: Hand count correct\n");
	else
		printf("FAIL: Expected hand count to be %d, actual: %d\n", benchmarkGame2->handCount[0] - 2, testGame2->handCount[0]);
	//test discard count
	if (testGame2->discardCount[0] == benchmarkGame2->discardCount[0])
		printf("PASS: Discard count correct\n");
	else
		printf("FAIL: Expected discard count to be %d, actual: %d\n", benchmarkGame2->discardCount[0], testGame2->discardCount[0]);
	//test that deck is same
	for (deckcounter = 0; deckcounter < MAX_DECK; deckcounter++) {
		if (testGame2->deck[0][deckcounter] != benchmarkGame2->deck[0][deckcounter])
			printf("FAIL: Deck position %d not the same\n", deckcounter);
	}
	//test deck count
	if (testGame2->deckCount[0] == benchmarkGame2->deckCount[0])
		printf("PASS: Deck count correct\n");
	else
		printf("FAIL: Expected deck count to be %d, actual: %d\n", benchmarkGame2->deckCount[0], testGame2->deckCount[0]);
	checkOtherPlayers(testGame2, benchmarkGame2, numPlayer);
	checkPiles(testGame2, benchmarkGame2);

	//test trashing a province from the end
	testGame3->hand[0][testGame3->handCount[0] - 1] = province;
	benchmarkGame3->hand[0][benchmarkGame3->handCount[0] - 1] = province;
	testGame3->hand[0][1] = salvager;
	benchmarkGame3->hand[0][1] = salvager;
	test3 = cardEffect(salvager, testGame3->handCount[0] - 1, -99, -99, testGame3, 1, bonus);
	//test return value
	if (test3 == 0)
		printf("PASS: Function returned correctly\n");
	else
		printf("FAIL: Function returned error of %d\n", test3);
	//test buy change
	if (testGame3->numBuys == benchmarkGame3->numBuys + 1)
		printf("PASS: Buys updated correctly\n");
	else
		printf("FAIL: Expected %d buys, actual: %d buys\n", benchmarkGame3->numBuys + 1, testGame3->numBuys);
	//test gold change
	if (testGame3->coins == benchmarkGame3->coins + 8)
		printf("PASS: Coins updated correctly\n");
	else
		printf("FAIL: Expected %d coins, actual: %d coins\n", benchmarkGame3->coins + 8, testGame3->coins);
	//test that card is removed
	if (cardCountHand(testGame3, province) == cardCountHand(benchmarkGame3, province) - 1)
		printf("PASS: Card removed\n");
	else
		printf("FAIL: Expected %d coppers; actual: %d coppers\n", cardCountHand(benchmarkGame3, province) - 1, cardCountHand(testGame3, province));
	//test hand count (two less for salvager and trashed card
	if (testGame3->handCount[0] == benchmarkGame3->handCount[0] - 2)
		printf("PASS: Hand count correct\n");
	else
		printf("FAIL: Expected hand count to be %d, actual: %d\n", benchmarkGame3->handCount[0] - 2, testGame3->handCount[0]);
	//test discard count
	if (testGame3->discardCount[0] == benchmarkGame3->discardCount[0])
		printf("PASS: Discard count correct\n");
	else
		printf("FAIL: Expected discard count to be %d, actual: %d\n", benchmarkGame3->discardCount[0], testGame3->discardCount[0]);
	//test that deck is same
	for (deckcounter = 0; deckcounter < MAX_DECK; deckcounter++) {
		if (testGame3->deck[0][deckcounter] != benchmarkGame3->deck[0][deckcounter])
			printf("FAIL: Deck position %d not the same\n", deckcounter);
	}
	//test deck count
	if (testGame3->deckCount[0] == benchmarkGame3->deckCount[0])
		printf("PASS: Deck count correct\n");
	else
		printf("FAIL: Expected deck count to be %d, actual: %d\n", benchmarkGame3->deckCount[0], testGame3->deckCount[0]);
	checkOtherPlayers(testGame3, benchmarkGame3, numPlayer);
	checkPiles(testGame3, benchmarkGame3);
	
	//test no trash
	//there doesn't seem to be any way to not trash a card in the code
	//according to the rules, you should be able to play salvager as the
	//last card in your hand; you still get the buy but can't trash anything.
	//This is an oversight, but not something you can test for.

	return 0;
}