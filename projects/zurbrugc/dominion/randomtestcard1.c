/* Author: Collin Zurbrugg, based on a template provided by Professor Jaki Sharief Shaik
** Date: 11/8/2018
** Description: Conducts random tests of the smithy card
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

void checkOtherPlayers(struct gameState *testGame, struct gameState *originalGame, int numPlayer, int playPos) {
	int errorFlag = 0;
	int globalErrorFlag = 0;
	for (int playercounter = 0; playercounter < numPlayer; playercounter++) {

		//for loop for deck
		for (int deckcounter = 0; deckcounter < originalGame->deckCount[originalGame->whoseTurn]; deckcounter++) {
			if (testGame->deck[playercounter][deckcounter] != originalGame->deck[playercounter][deckcounter]) {
				errorFlag = 1;
			}
		}
		if (errorFlag == 1 && originalGame->discardCount[originalGame->whoseTurn] != 0) {
			printf("FAIL: Deck not the same for player %d\n", playercounter);
			globalErrorFlag = 1;
		}
		errorFlag = 0;

		if (testGame->deckCount[playercounter] != originalGame->deckCount[playercounter]) {
			printf("FAIL: Deck count for player %d updated; ", playercounter);
			printf("Should be %d, actually %d\n", originalGame->deckCount[playercounter], testGame->deckCount[playercounter]);
			globalErrorFlag = 1;
		}

		//check player's hand
		for (int handcounter = 0; handcounter < originalGame->handCount[originalGame->whoseTurn]; handcounter++) {
			if (testGame->hand[playercounter][handcounter] != originalGame->hand[playercounter][handcounter]) {
				errorFlag = 1;
			}
		}
		if (errorFlag == 1 && originalGame->discardCount[originalGame->whoseTurn] != 0) {
			printf("FAIL: Hand not the same for player%d\n", playercounter);
			globalErrorFlag = 1;
		}
		errorFlag = 0;
		//check player's hand count
		if (testGame->handCount[playercounter] != originalGame->handCount[playercounter]) {
			printf("FAIL: Hand count updated for player %d; ", playercounter);
			printf("Should be %d, actually %d\n", originalGame->handCount[playercounter], testGame->handCount[playercounter]);
			globalErrorFlag = 1;
		}

		//check player's discard
		for (int discardcounter = 0; discardcounter < originalGame->discardCount[originalGame->whoseTurn]; discardcounter++) {
			if (testGame->discard[playercounter][discardcounter] != originalGame->discard[playercounter][discardcounter]) {
				errorFlag = 1;
			}
		}
		if (errorFlag == 1) {
			printf("FAIL: Discard not the same for player %d\n", playercounter);
			globalErrorFlag = 1;
		}

		//check player's discard count
		if (testGame->discardCount[playercounter] != originalGame->discardCount[playercounter]) {
			printf("FAIL: Discard count updated for player %d; ", playercounter);
			printf("Should be %d, actually %d\n", originalGame->discardCount[playercounter], testGame->discardCount[playercounter]);
			globalErrorFlag = 1;
		}
	}
	if (globalErrorFlag == 1) {
		outputErrorInfo(testGame, playPos);
	}
}
//main tests
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
	int numPlayers;
	int activePlayer;

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
		k[0] = smithy;
		for (j = 1; j < 10; j++) {
			k[j] = (rand() % 20) + 7;
		}
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
			deckLimit = rand() % MAX_DECK;
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
		deckLimit = rand() % MAX_DECK;
		beforeGame->discardCount[activePlayer] = 0;
		afterGame->discardCount[activePlayer] = 0;
		for (j = 0; j < deckLimit; j++) {
			jj = rand() % 9;
			beforeGame->discard[activePlayer][j] = k[jj];
			afterGame->discard[activePlayer][j] = k[jj];
			beforeGame->discardCount[activePlayer]++;
			afterGame->discardCount[activePlayer]++;
		}
		//randomize hand of whoseTurn
		deckLimit = (rand() % (MAX_HAND - 1)) + 1;
		beforeGame->handCount[activePlayer] = 0;
		afterGame->handCount[activePlayer] = 0;
		for (j = 0; j < deckLimit; j++) {
			jj = rand() % 9;
			beforeGame->hand[activePlayer][j] = k[jj];
			afterGame->hand[activePlayer][j] = k[jj];
			beforeGame->handCount[activePlayer]++;
			afterGame->handCount[activePlayer]++;
		}

		//every 503 instances, make sure the player has less than three cards to draw
		if (i % 503 == 72) {
			beforeGame->deckCount[beforeGame->whoseTurn] = 1;
			beforeGame->discardCount[beforeGame->whoseTurn] = 1;
			afterGame->deckCount[afterGame->whoseTurn] = 1;
			afterGame->discardCount[afterGame->whoseTurn] = 1;
		}

		//set playPos to card
		playPos = (rand() % deckLimit);
		beforeGame->hand[activePlayer][playPos] = smithy;
		afterGame->hand[activePlayer][playPos] = smithy;

		//call cardEffect
		cardEffect(smithy, 0, 0, 0, afterGame, playPos, 0);
		//adjust before state appropriately
		for (j = 0; j < 3; j++) {
			drawCard(beforeGame->whoseTurn, beforeGame);
		}
		discardCard(playPos, beforeGame->whoseTurn, beforeGame, 0);


		//compare the game states
		checkOtherPlayers(afterGame, beforeGame, numPlayers, playPos);
		//check numBuys
		if (beforeGame->numBuys != afterGame->numBuys) {
			printf("FAIL: numBuys different\n");
			printf("Should be %d, actually %d\n", beforeGame->numBuys, afterGame->numBuys);
			outputErrorInfo(afterGame, playPos);
		}
		//check numActions
		if (beforeGame->numActions != afterGame->numActions) {
			printf("FAIL: numActions different\n");
			printf("Should be %d, actually %d\n", beforeGame->numActions, afterGame->numActions);
			outputErrorInfo(afterGame, playPos);
		}
		//check coins
		if (beforeGame->coins != afterGame->coins) {
			printf("FAIL: coins different\n");
			printf("Should be %d, actually %d\n", beforeGame->coins, afterGame->coins);
			outputErrorInfo(afterGame, playPos);
		}
		free(beforeGame);
		free(afterGame);
	}

	return 0;
}
