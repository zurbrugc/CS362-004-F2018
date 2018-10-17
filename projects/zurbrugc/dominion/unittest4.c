/* FIXME: comment block*/
/* This code is based on a template provided by Professor Jaki Sharief Shaik*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int numPlayer = 3;
	int k[10] = { adventurer, council_room, feast, gardens, mine
			   , remodel, smithy, village, baron, great_hall };
	struct gameState *G = newGame();

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
		printf("PASS: test1\n");
	else
		printf("FAIL: test1\n");
	if (test2 == 2)
		printf("PASS: test2\n");
	else
		printf("FAIL: test2\n");
	if (test3 == 0)
		printf("PASS: test3\n");
	else
		printf("FAIL: test3\n");

	return 0;
}