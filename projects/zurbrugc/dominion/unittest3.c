/* Author: Collin Zurbrugg, based on a template provided by Professor Jaki Sharief Shaik
** Date: 10/19/2018
** Description: A function to test the supplyCount function in dominion. */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int numPlayer = 2;
	int k[10] = { adventurer, council_room, feast, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState *G = newGame();

	//initialize game state
	initializeGame(numPlayer, k, 3333, G);

	//run the function
	int test1, test2, test3, test4, test5, test6;
	test1 = supplyCount(smithy, G);
	test2 = supplyCount(estate, G);
	test3 = supplyCount(gold, G);
	test4 = supplyCount(steward, G);
	test5 = supplyCount(steward, G); //make sure the number doesn't change
	test6 = supplyCount(smithy, G);

	//compare game state to expected
	if (test1 == 10)
		printf("PASS: smithy\n");
	else
		printf("FAIL: Expected 10, actually %d\n", test1);
	if (test2 == 8)
		printf("PASS: estate\n");
	else
		printf("FAIL: Expected 8, actually %d\n", test2);
	if (test3 == 30)
		printf("PASS: gold\n");
	else
		printf("FAIL: Expected 30, actually %d\n", test3);
	if (test4 == -1)
		printf("PASS: steward\n");
	else
		printf("FAIL: Expected -1, actually %d\n", test4);
	if (test5 == -1)
		printf("PASS: steward again\n");
	else
		printf("FAIL: Expected -1, actually %d\n", test5);
	if (test6 == 10)
		printf("PASS: smithy again\n");
	else
		printf("FAIL: Expected 10, actually %d\n", test6);

	return 0;
}