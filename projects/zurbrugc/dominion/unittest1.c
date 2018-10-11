/* FIXME: comment block*/
/* This code is based on a template provided by Professor Jaki Sharief Shaik*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int i;
	int seed = 555;
	int numPlayer = 2;
	int maxBonus = 10;
	int p, r, handCount;
	int bonus;
	int k[10] = { adventurer, council_room, feast, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState *G1 = newGame();	//province is empty
	struct gameState *G2 = newGame();	//3 piles are empty
	struct gameState *G3 = newGame();	//province and three piles are empty
	struct gameState *G4 = newGame();	//2 piles are empty
	struct gameState *G5 = newGame();	//4 piles are empty
	struct gameState *G6 = newGame();	//0 piles are empty
	int maxHandCount = 5;
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
	intializeGame(numPlayer, k, 555, G1);
	G1->supplyCount[province] = 0;

	//G2: exactly 3 piles are empty
	intializeGame(numPlayer, k, 555, G2);
	G2->supplyCount[smithy] = 0;
	G2->supplyCount[adventurer] = 0;
	G2->supplyCount[baron] = 0;

	//G3: 3 piles are empty including province
	intializeGame(numPlayer, k, 555, G3);
	G3->supplyCount[gardens] = 0;
	G3->supplyCount[village] = 0;
	G3->supplyCount[province] = 0;

	//G4: less than 3 piles are empty
	intializeGame(numPlayer, k, 555, G4);
	G4->supplyCount[remodel] = 0;
	G4->supplyCount[mine] = 0;

	//G5: more than 3 piles are empty
	intializeGame(numPlayer, k, 555, G5);
	G5->supplyCount[copper] = 0;
	G5->supplyCount[gold] = 0;
	G5->supplyCount[feast] = 0;
	G5->supplyCount[silver] = 0;
	G5->supplyCount[council_room] = 0;

	//G6: no piles are empty
	intializeGame(numPlayer, k, 555, G6);

	//run the function: isGameOver()
	int test1 = isGameOver(G1);
	int test2 = isGameOver(G2);
	int test3 = isGameOver(G3);
	int test4 = isGameOver(G4);
	int test5 = isGameOver(G5);
	int test6 = isGameOver(G6);

	//compare game state to expected
	printf("Test 1: ");
	if (test1 == 1)
		printf("PASSED\n")
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 1, test1);

	printf("Test 2: ");
	if (test1 == 1)
		printf("PASSED\n")
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 1, test1);

	printf("Test 3: ");
	if (test1 == 0)
		printf("PASSED\n")
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 1, test1);

	printf("Test 4: ");
	if (test1 == 1)
		printf("PASSED\n")
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 0, test1);

	printf("Test 5: ");
	if (test1 == 1)
		printf("PASSED\n")
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 1, test1);

	printf("Test 6: ");
	if (test1 == 0)
		printf("PASSED\n")
	else
		printf("FAILED\n");
	printf("Expected: %d; Actual: %d\n", 0, test1);

	return 0;
}