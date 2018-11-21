/* Author: Collin Zurbrugg, based on a template provided by Professor Jaki Sharief Shaik
** Date: 10/19/2018
** Description: A function to test the isGameOver function in dominion. */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int i;
	//int seed = 555;
	int numPlayer = 2;
	//int maxBonus = 10;
	//int p, r, handCount;
	//int bonus;
	int k[10] = { adventurer, council_room, feast, gardens, remodel
			   , smithy, village, baron, great_hall, treasure_map };
	struct gameState *G1 = newGame();	//province is empty
	struct gameState *G2 = newGame();	//3 piles are empty
	struct gameState *G3 = newGame();	//province and three piles are empty
	struct gameState *G4 = newGame();	//2 piles are empty
	struct gameState *G5 = newGame();	//4 piles are empty
	struct gameState *G6 = newGame();	//0 piles are empty
	struct gameState *G7 = newGame();	//3 piles are empty, testing bounds
	//int maxHandCount = 5;
	// arrays of all coppers, silvers, and golds
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];
	for (i = 0; i < MAX_HAND; i++)
	{
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}


	//initialize game states

	//G1: province is empty
	initializeGame(numPlayer, k, 555, G1);
	G1->supplyCount[province] = 0;

	//G2: exactly 3 piles are empty
	initializeGame(numPlayer, k, 555, G2);
	G2->supplyCount[smithy] = 0;
	G2->supplyCount[adventurer] = 0;
	G2->supplyCount[baron] = 0;

	//G3: 3 piles are empty including province
	initializeGame(numPlayer, k, 555, G3);
	G3->supplyCount[gardens] = 0;
	G3->supplyCount[village] = 0;
	G3->supplyCount[province] = 0;

	//G4: less than 3 piles are empty
	initializeGame(numPlayer, k, 555, G4);
	G4->supplyCount[great_hall] = 0;

	//G5: more than 3 piles are empty
	initializeGame(numPlayer, k, 555, G5);
	G5->supplyCount[copper] = 0;
	G5->supplyCount[gold] = 0;
	G5->supplyCount[feast] = 0;
	G5->supplyCount[silver] = 0;
	G5->supplyCount[council_room] = 0;

	//G6: no piles are empty
	initializeGame(numPlayer, k, 555, G6);

	//G7: testing bounds, 3 piles empty
	initializeGame(numPlayer, k, 555, G7);
	G7->supplyCount[treasure_map] = 0;
	G7->supplyCount[baron] = 0;
	G7->supplyCount[village] = 0;

	//run the function: isGameOver()
	int test1 = isGameOver(G1);
	int test2 = isGameOver(G2);
	int test3 = isGameOver(G3);
	int test4 = isGameOver(G4);
	int test5 = isGameOver(G5);
	int test6 = isGameOver(G6);
	int test7 = isGameOver(G7);

	//compare game state to expected
	printf("Test 1: ");
	if (test1 == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 1, test1);

	printf("Test 2: ");
	if (test2 == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 1, test2);

	printf("Test 3: ");
	if (test3 == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 1, test3);

	printf("Test 4: ");
	if (test4 == 0)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 0, test4);

	printf("Test 5: ");
	if (test5 == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 1, test5);

	printf("Test 6: ");
	if (test6 == 0)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 0, test6);

	printf("Test 7: ");
	if (test7 == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 1, test7);

	return 0;
}