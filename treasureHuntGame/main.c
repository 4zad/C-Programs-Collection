/*
	==================================================
	TREASURE HUNT GAME
	==================================================
	Author : Muhammad Ahmed [4zad]
	Email  : mahmed.4zad@gmail.com
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_LIVES 10
#define MIN_LIVES 1
#define MAX_PATH_LENGTH 70
#define MIN_PATH_LENGTH 10
#define DIVISOR 5
#define DECA_DIVISOR 10

struct PlayerInfo {

	int nmbrLives;
	char playerSymbol;
	int nmbrTreasureFound;
	int pstnHistory[MAX_PATH_LENGTH];

};

struct GameInfo {

	int nmbrMoves;
	int pathLength;
	int bombLocation[MAX_PATH_LENGTH];
	int treasureLocation[MAX_PATH_LENGTH];

};

int main(void) {

	struct PlayerInfo playerInfo = { 0 };
	struct GameInfo gameInfo = { 0 };
	int i, j, decaCounter, counter, flag = 0, isDivisible = 0, maxMoves = 0, whereToMove = 0;
	char lineTwo[MAX_PATH_LENGTH];


	//Begin program
	printf("================================\n");
	printf("         Treasure Hunt!         \n");
	printf("================================\n\n");

	printf("PLAYER Configuration\n");
	printf("--------------------\n");

	printf("Enter a single character to represent the player: ");
	scanf(" %c", &playerInfo.playerSymbol);

	do {

		printf("Set the number of lives: ");
		scanf("%d", &playerInfo.nmbrLives);

		if (playerInfo.nmbrLives < MIN_LIVES || playerInfo.nmbrLives > MAX_LIVES) {

			flag = 1;
			printf("     Must be between %d and %d!\n", MIN_LIVES, MAX_LIVES);

		} else {

			for (i = 0; i < MAX_PATH_LENGTH; i++) {

				playerInfo.pstnHistory[i] = 0;

			}

			flag = 0;
			printf("Player configuration set-up is complete\n\n");

		}

	} while (flag);


	//Setting game config
	printf("GAME Configuration\n");
	printf("------------------\n");

	do {

		printf("Set the path length (a multiple of %d between %d-%d): ", DIVISOR, MIN_PATH_LENGTH, MAX_PATH_LENGTH);
		scanf("%d", &gameInfo.pathLength);

		isDivisible = gameInfo.pathLength % DIVISOR;

		if (gameInfo.pathLength < MIN_PATH_LENGTH || gameInfo.pathLength > MAX_PATH_LENGTH || isDivisible != 0) {

			flag = 1;
			printf("     Must be a multiple of %d and between %d-%d!!!\n", DIVISOR, MIN_PATH_LENGTH, MAX_PATH_LENGTH);

		} else {

			flag = 0;

		}

	} while (flag);

	flag = 0;
	maxMoves = gameInfo.pathLength * 0.75;

	do {

		printf("Set the limit for number of moves allowed: ");
		scanf("%d", &gameInfo.nmbrMoves);

		if (gameInfo.nmbrMoves < playerInfo.nmbrLives || gameInfo.nmbrMoves > maxMoves) {

			flag = 1;
			printf("    Value must be between %d and %d\n", playerInfo.nmbrLives, maxMoves);

		} else {

			flag = 0;

		}

	} while (flag);


	//Setting bomb config
		printf("\nBOMB Placement\n");
	printf("--------------\n");

	printf("Enter the bomb positions in sets of %d where a value\nof 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n", DIVISOR);
	printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", gameInfo.pathLength);

	for (i = 0; i < (gameInfo.pathLength / DIVISOR); i++) {

		printf("   Positions [%2d-%2d]: ", (i * 5 + 1), (i * 5 + 5));
		scanf("%d %d %d %d %d", &gameInfo.bombLocation[i * 5], &gameInfo.bombLocation[i * 5 + 1], &gameInfo.bombLocation[i * 5 + 2], &gameInfo.bombLocation[i * 5 + 3], &gameInfo.bombLocation[i * 5 + 4]);

	}

	printf("BOMB Placement set\n\n");


	//Setting treasure config
	printf("TREASURE Placement\n");
	printf("------------------\n");

	printf("Enter the treasure placements in sets of %d where a value\nof 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n", DIVISOR);
	printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", gameInfo.pathLength);

	for (i = 0; i < (gameInfo.pathLength / DIVISOR); i++) {

		printf("   Positions [%2d-%2d]: ", (i * 5 + 1), (i * 5 + 5));
		scanf("%d %d %d %d %d", &gameInfo.treasureLocation[i * 5], &gameInfo.treasureLocation[i * 5 + 1], &gameInfo.treasureLocation[i * 5 + 2], &gameInfo.treasureLocation[i * 5 + 3], &gameInfo.treasureLocation[i * 5 + 4]);

	}

	printf("TREASURE Placement set\n\n");

	printf("GAME configuration set-up is complete...\n\n");


	//Display game settings
	printf("------------------------------------\n");
	printf("TREASURE HUNT Configuration Settings\n");
	printf("------------------------------------\n");

	printf("Player:\n");
	printf("   Symbol     : %c\n", playerInfo.playerSymbol);
	printf("   Lives      : %d\n", playerInfo.nmbrLives);
	printf("   Treasure   : [ready for gameplay]\n");
	printf("   History    : [ready for gameplay]\n\n");

	printf("Game:\n");
	printf("   Path Length: %d\n", gameInfo.pathLength);
	printf("   Bombs      : ");

	for (i = 0; i < gameInfo.pathLength; i++) {

		printf("%d", gameInfo.bombLocation[i]);

	}

	printf("\n");
	printf("   Treasure   : ");

	for (i = 0; i < gameInfo.pathLength; i++) {

		printf("%d", gameInfo.treasureLocation[i]);

	}


	//Begin game
	printf("\n\n");
	printf("====================================\n");
	printf("~ Get ready to play TREASURE HUNT! ~\n");
	printf("====================================\n");

	for (i = 0; i < gameInfo.pathLength; i++) {

		lineTwo[i] = '-';

	}

	do {

		printf("  ");

		for (i = 0; i < gameInfo.pathLength; i++) {

			if ((i + 1) == whereToMove) {

				printf("%c", playerInfo.playerSymbol);

			} else {		

				printf(" ");

			}

		}

		printf("\n  ");

		for (i = 0; i < gameInfo.pathLength; i++) {

			printf("%c", lineTwo[i]);

		}

		printf("\n  ");
		
		for (i = 0, decaCounter = 1; i < gameInfo.pathLength; i++) {

			if (((i + 1) % DECA_DIVISOR) == 0 && i != 0) {
				
				printf("%d", decaCounter);
				decaCounter += 1;

			} else {

				printf("|");

			}

		}

		printf("\n  ");

		for (i = 0, counter = 1; i < gameInfo.pathLength; i++) {

			if (((i + 1) % DECA_DIVISOR) == 0 && i != 0) {

				printf("0");
				counter = 1;

			} else {

				printf("%d", counter);
				counter += 1;

			}

		}

		printf("\n+---------------------------------------------------+\n");
		printf("  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d\n", playerInfo.nmbrLives, playerInfo.nmbrTreasureFound, gameInfo.nmbrMoves);
		printf("+---------------------------------------------------+\n");

		do {

			printf("Next Move [1-%d]: ", gameInfo.pathLength);
			scanf("%d", &whereToMove);

			if (whereToMove < 1 || whereToMove > gameInfo.pathLength) {

				flag = 1;
				printf("  Out of Range!!!\n");

			} else {

				flag = 0;

			}

		} while (flag);

		printf("\n");

		if (playerInfo.pstnHistory[whereToMove - 1]) {
		
			printf("===============> Dope! You've been here before!\n");
		
		} else if (gameInfo.bombLocation[whereToMove - 1] && gameInfo.treasureLocation[whereToMove - 1]) {

			printf("===============> [!] !!! BOOOOOM !!! [!]\n");
			printf("===============> [&] $$$ Life Insurance Payout!!! [&]\n");

			gameInfo.nmbrMoves -= 1;
			playerInfo.nmbrLives -= 1;
			playerInfo.nmbrTreasureFound += 1;
			lineTwo[whereToMove - 1] = '&';

		} else if (gameInfo.bombLocation[whereToMove - 1]) {

			printf("===============> [!] !!! BOOOOOM !!! [!]\n");

			gameInfo.nmbrMoves -= 1;
			playerInfo.nmbrLives -= 1;
			lineTwo[whereToMove - 1] = '!';

		} else if (gameInfo.treasureLocation[whereToMove - 1]) {

			printf("===============> [$] $$$ Found Treasure! $$$ [$]\n");

			gameInfo.nmbrMoves -= 1;
			playerInfo.nmbrTreasureFound += 1;
			lineTwo[whereToMove - 1] = '$';

		} else {

			printf("===============> [.] ...Nothing found here... [.]\n");

			gameInfo.nmbrMoves -= 1;
			lineTwo[whereToMove - 1] = '.';

		}

		printf("\n");

		playerInfo.pstnHistory[whereToMove - 1] = 1;

		if (gameInfo.nmbrMoves == 0 || playerInfo.nmbrLives == 0) {

			flag = 0;

			if (playerInfo.nmbrLives == 0)
				printf("No more LIVES remaining!\n");

			if (gameInfo.nmbrMoves == 0)
				printf("No more MOVES remaining!\n");

		} else {

			flag = 1;

		}

	} while (flag);


	//Display ending game stats
	printf("\n  ");

	for (i = 0; i < gameInfo.pathLength; i++) {

		if ((i + 1) == whereToMove) {

			printf("%c", playerInfo.playerSymbol);

		} else {

			printf(" ");

		}

	}

	printf("\n  ");

	for (i = 0; i < gameInfo.pathLength; i++) {

		printf("%c", lineTwo[i]);

	}

	printf("\n  ");

	for (i = 0, decaCounter = 1; i < gameInfo.pathLength; i++) {

		if (((i + 1) % DECA_DIVISOR) == 0 && i != 0) {

			printf("%d", decaCounter);
			decaCounter += 1;

		} else {

			printf("|");

		}

	}

	printf("\n  ");

	for (i = 0, counter = 1; i < gameInfo.pathLength; i++) {

		if (((i + 1) % DECA_DIVISOR) == 0 && i != 0) {

			printf("0");
			counter = 1;

		} else {

			printf("%d", counter);
			counter += 1;

		}

	}

	printf("\n+---------------------------------------------------+\n");
	printf("  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d\n", playerInfo.nmbrLives, playerInfo.nmbrTreasureFound, gameInfo.nmbrMoves);
	printf("+---------------------------------------------------+\n\n");

	printf("##################\n");
	printf("#   Game over!   #\n");
	printf("##################\n\n");

	printf("You should play again and try to beat your score!!\n");

	return 0;
}






