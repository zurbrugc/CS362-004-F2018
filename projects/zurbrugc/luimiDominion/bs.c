/* Author: Collin Zurbrugg, based on a template provided by Professor Jaki Sharief Shaik
** Date: 11/10/2018
** Description: Conducts random tests of the smithy card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main() {
		struct gameState *beforeGame = newGame();
		beforeGame->discardCount = 0;
		beforeGame->deckCount = 0;
		beforeGame->handCount = 1;
		beforeGame->hand[0][0] = adventurer;
		beforeGame->whoseTurn = 0;
		beforeGame->numPlayers = 3;
		beforeGame->hand[activePlayer][0] = smithy;
		cardEffect(adventurer, 0, 0, 0, beforeGame, playPos, 0);
		free(beforeGame);

	return 0;
}
