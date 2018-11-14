/* Author: Collin Zurbrugg, based on a template provided by Professor Jaki Sharief Shaik
** Date: 11/8/2018
** Description:
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

void outputErrorInfo(struct gameState *buggyGame, int handPos) {
	printf("numPlayers: %d\n", buggyGame->numPlayers);
	printf("Active player: %d\n", buggyGame->whoseTurn);
	printf("Card played from hand position %d\n", handPos);

	printf("Deck counts: ");
	for (int i = 0; i < buggyGame->numPlayers; i++) {
		printf("%d ", buggyGame->deckCount[i]);
	}
	printf("\nHand counts: ");
	for (int i = 0; i < buggyGame->numPlayers; i++) {
		printf("%d ", buggyGame->handCount[i]);
	}
	printf("\nDiscard counts: ");
	for (int i = 0; i < buggyGame->numPlayers; i++) {
		printf("%d ", buggyGame->discardCount[i]);
	}
	printf("\n");
	//other relevant variables
}

int treasureCountHand(struct gameState *G, int player) {
	//counts how much treasure is in player 0's hand
	int count = 0;
	for (int i = 0; i < G->handCount[player]; i++) {
		if (G->hand[player][i] == copper || G->hand[player][i] == silver || G->hand[player][i] == gold)
			count++;
	}
	return count;
}

int treasureCountD(struct gameState *G, int player) {
	//counts how much treasure is in player 0's deck and discard
	int count = 0;
	for (int i = 0; i < G->deckCount[player]; i++) {
		if (G->deck[player][i] == copper || G->deck[player][i] == silver || G->deck[player][i] == gold)
			count++;
	}
	for (int j = 0; j < G->discardCount[player]; j++) {
		if (G->discard[player][j] == copper || G->discard[player][j] == silver || G->discard[player][j] == gold)
			count++;
	}
	return count;
}

void checkOtherPlayers(struct gameState *testGame, struct gameState *originalGame, int numPlayer, int playPos) {
	int errorFlag = 0;
	int globalErrorFlag = 0;
	for (int playercounter = 0; playercounter < numPlayer; playercounter++) {

		//check player's deck and discard count
		if (testGame->deckCount[playercounter] + testGame->discardCount[playercounter] != originalGame->deckCount[playercounter] + originalGame->discardCount[playercounter]) {
			printf("FAIL: Deck and discard count for player %d updated; ", playercounter);
			printf("Should be %d, actually %d\n", originalGame->deckCount[playercounter] + originalGame->discardCount[playercounter], testGame->deckCount[playercounter] + testGame->discardCount[playercounter]);
			globalErrorFlag = 1;
		}

		//check player's hand count
		if (testGame->handCount[playercounter] != originalGame->handCount[playercounter]) {
			printf("FAIL: Hand count updated for player %d; ", playercounter);
			printf("Should be %d, actually %d\n", originalGame->handCount[playercounter], testGame->handCount[playercounter]);
			globalErrorFlag = 1;
		}
	}
	if (globalErrorFlag == 1) {
		outputErrorInfo(testGame, playPos);
	}
}

int main() {
	//int k[10] = { adventurer, council_room, feast, gardens, remodel,
		   //smithy, village, baron, great_hall, treasure_map };
	int j;
	int jj;
	int jjj;
	int seed;
	int k[10];
	int playPos;
	int deckLimit;
	int handLimit;
	int notHandCount;
	int discardLimit;
	int numPlayers;
	int activePlayer;
	int handTreasure;
	int treasureHolder;
	int availableTreasure;

	for (int i = 0; i < 5555; i++) {
		printf("------------\n");
		struct gameState *beforeGame = newGame();
		struct gameState *afterGame = newGame();
		//randomize seed
		seed = rand();
		//randomize numPlayers [2, 4]
		numPlayers = (rand() % 3) + 2;
		beforeGame->numPlayers = numPlayers;
		afterGame->numPlayers = numPlayers;
		//randomize k
		k[0] = adventurer;
		for (j = 1; j < 10; j++) {
			k[j] = (rand() % 20) + 7;
		}
		//initialize game states
		//initializeGame(numPlayers, k, seed, beforeGame);
		//initializeGame(numPlayers, k, seed, afterGame);

		//randomly choose active player
		activePlayer = (rand() % numPlayers);
		beforeGame->whoseTurn = activePlayer;
		afterGame->whoseTurn = activePlayer;

		//reset hands and discards
		for (j = 0; j < numPlayers; j++) {
			beforeGame->handCount[j] = 0;
			afterGame->handCount[j] = 0;
			beforeGame->discardCount[j] = 0;
			afterGame->discardCount[j] = 0;
			for (jj = 0; jj < MAX_DECK; jj++) {
				beforeGame->hand[j][jj] = 0;
				afterGame->hand[j][jj] = 0;
			}
			for (jj = 0; jj < MAX_DECK; jj++) {
				beforeGame->deck[j][jj] = 0;
				afterGame->deck[j][jj] = 0;
				beforeGame->discard[j][jj] = 0;
				afterGame->discard[j][jj] = 0;
			}
		}

		//populate each player's deck
		for (j = 0; j < numPlayers; j++) {
			deckLimit = (rand() % (MAX_DECK - 1)) + 1;
			beforeGame->deckCount[j] = 0;
			afterGame->deckCount[j] = 0;
			for (jj = 0; jj < deckLimit; jj++) {
				jjj = rand() % 9;
				beforeGame->deck[j][jj] = k[jjj];
				afterGame->deck[j][jj] = k[jjj];
				beforeGame->deckCount[j]++;
				afterGame->deckCount[j]++;
			}
		}
		//randomize discard of whoseTurn
		discardLimit = MAX_DECK - beforeGame->deckCount[activePlayer];
		if (discardLimit == 0) discardLimit++;
		discardLimit = rand() % discardLimit;
		if (discardLimit == 0) discardLimit++;
		beforeGame->discardCount[activePlayer] = 0;
		afterGame->discardCount[activePlayer] = 0;
		for (j = 0; j < discardLimit; j++) {
			jj = rand() % 9;
			beforeGame->discard[activePlayer][j] = k[jj];
			afterGame->discard[activePlayer][j] = k[jj];
			beforeGame->discardCount[activePlayer]++;
			afterGame->discardCount[activePlayer]++;
		}
		//randomize hand of whoseTurn
		handLimit = (rand() % (MAX_HAND - 1)) + 1;
		beforeGame->handCount[activePlayer] = 0;
		afterGame->handCount[activePlayer] = 0;
		for (j = 0; j < handLimit; j++) {
			jj = rand() % 9;
			beforeGame->hand[activePlayer][j] = k[jj];
			afterGame->hand[activePlayer][j] = k[jj];
			beforeGame->handCount[activePlayer]++;
			afterGame->handCount[activePlayer]++;
		}
		deckLimit = beforeGame->deckCount[activePlayer];

		//anything else to randomize?
		j = rand() % 9;
		if (j < 5) {
			//populate treasure like normal 5/10 times
			if (deckLimit > 0) {
				for (jj = (rand() % deckLimit) + 1; jj > 0; jj--) {
	jjj = rand() % deckLimit;
	beforeGame->deck[activePlayer][jjj] = silver;
	afterGame->deck[activePlayer][jjj] = silver;
				}
			}
			if (discardLimit > 0) {
				for (jj = (rand() % discardLimit) + 1; jj > 0; jj--) {
		jjj = rand() % discardLimit;
		beforeGame->deck[activePlayer][jjj] = copper;
		afterGame->deck[activePlayer][jjj] = copper;
				}
			}
		}
		else if (j < 8) {
			//ensure shuffle 3/10 times
			if (discardLimit > 0) {
				for (jj = (rand() % discardLimit) + 1; jj > 0; jj--) {
		jjj = rand() % discardLimit;
		beforeGame->discard[activePlayer][jjj] = gold;
		afterGame->discard[activePlayer][jjj] = gold;
				}
			}
		}
		else if (j == 8) {
			//one treasure 1/10 times
			if (discardLimit > 0) {
				jjj = rand() % discardLimit;
				beforeGame->discard[activePlayer][jjj] = gold;
				afterGame->discard[activePlayer][jjj] = gold;
			}
		}
		//if j is 9, add no treasure
		//this causes a segmentation fault, so we're not running it

		//set playPos to card
		playPos = (rand() % handLimit);
		beforeGame->hand[activePlayer][playPos] = adventurer;
		afterGame->hand[activePlayer][playPos] = adventurer;

 		//call cardEffect
		cardEffect(adventurer, 0, 0, 0, afterGame, playPos, 0);
		//cardEffect(adventurer, 0, 0, 0, beforeGame, playPos, 0);

		//adjust before state appropriately
		availableTreasure = treasureCountD(beforeGame, beforeGame->whoseTurn);
		handTreasure = treasureCountHand(beforeGame, beforeGame->whoseTurn);
		notHandCount = beforeGame->deckCount[beforeGame->whoseTurn] + beforeGame->discardCount[beforeGame->whoseTurn];
		if (availableTreasure == 1) {
			handTreasure++;
			availableTreasure--;
			notHandCount--;
			beforeGame->handCount[beforeGame->whoseTurn]++;
		}
		else if (availableTreasure > 1) {
			handTreasure = handTreasure + 2;
			availableTreasure = availableTreasure - 2;
			beforeGame->handCount[beforeGame->whoseTurn] = beforeGame->handCount[beforeGame->whoseTurn] + 2;
			notHandCount = notHandCount + 2;
		}

		//compare the game states
		checkOtherPlayers(afterGame, beforeGame, numPlayers, playPos);

		//check treasure
		for (j = 0; j < numPlayers; j++) {
			if (j == activePlayer) {
				treasureHolder = treasureCountHand(afterGame, j);
				if (handTreasure != treasureHolder) {
					printf("FAIL: Player %d has %d treasure in hand\n", j, treasureHolder);
					printf("Expected %d\n", handTreasure);
				}
				treasureHolder = treasureCountD(afterGame, j);
				if (availableTreasure != treasureHolder) {
					printf("FAIL: Player %d has %d treasure in deck and discard\n", j, treasureHolder);
					printf("Expected %d\n", availableTreasure);
				}
			}
			else {
				treasureHolder = treasureCountHand(afterGame, j);
				if (treasureCountHand(beforeGame, j) != treasureHolder) {
					printf("FAIL: Player %d has %d treasure in hand\n", j, treasureHolder);
					printf("Expected %d\n", handTreasure);
				}
				treasureHolder = treasureCountD(afterGame, j);
				if (treasureCountD(beforeGame, j) != treasureHolder) {
					printf("FAIL: Player %d has %d treasure in deck and discard\n", j, treasureHolder);
					printf("Expected %d\n", availableTreasure);
				}
			}
		}
		free(beforeGame);
		free(afterGame);
	}

	return 0;
}
