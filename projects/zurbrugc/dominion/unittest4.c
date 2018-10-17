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
	int seeds[5] = { 5, 314, 12, 67, 999 };
	int numPlayer = 3;
	int maxBonus = 10;
	int p, r, handCount;
	int bonus;
	int k[10] = { adventurer, council_room, feast, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState G;
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

	//initialize game state
	initializeGame(numPlayer, k, 8888, G);
	int test1, test2, test3;

	//run the function
	test1 = whoseTurn(G);
	G->whoseTurn = 2;
	test2 = whoseTurn(G);
	G->whoseTurn = 0;
	test3 = whoseTurn(G);

	//compare game state to expected
	if (test1 == 0)
		printf("PASS: test1");
	else
		printf("FAIL: test1");
	if (test2 == 2)
		printf("PASS: test2");
	else
		printf("FAIL: test2");
	if (test3 == 0)
		printf("PASS: test3");
	else
		printf("FAIL: test4");

	return 0;
}