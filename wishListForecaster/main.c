/*
	==================================================
	WISH LIST FORECASTER
	==================================================
	Author : Muhammad Ahmed [4zad]
	Email  : mahmed.4zad@gmail.com
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_ALLOWED_ITEM 10
#define MIN_ALLOWED_ITEM 1

int main(void) {

	const double MIN_INCOME = 500.00, MAX_INCOME = 400000.00, MIN_COST = 100.00;
	const int MIN_PRIORITY = 1, MAX_PRIORITY = 3;

	char financeOptn[MAX_ALLOWED_ITEM] = { '0' };
	int itemPriority[MAX_ALLOWED_ITEM] = { 0 };
	double itemCost[MAX_ALLOWED_ITEM] = { 0.0 };
	int i, flagTwo = 0, flag = 0, wishItemNmbr = 0, filterChoice, priorityChoice, forecastYear = 0, forecastMonth = 0;
	double netIncome = 0, itemCostSum = 0, filteredCostSum = 0;


	printf("+--------------------------+\n");
	printf("+   Wish List Forecaster   |\n");
	printf("+--------------------------+\n\n");


	do {
		printf("Enter your monthly NET income: $");
		scanf("%lf", &netIncome);

		flag = 0;

		if (netIncome > MAX_INCOME) {
			printf("ERROR: Liar! I'll believe you if you enter a value no more than $%.2lf\n", MAX_INCOME);
			flag = 1;
		}

		if (netIncome < MIN_INCOME) {
			printf("ERROR: You must have a consistent monthly income of at least $%.2lf\n", MIN_INCOME);
			flag = 1;
		}

		printf("\n");

	} while (flag);


	do {
		printf("How many wish list items do you want to forecast?: ");
		scanf("%d", &wishItemNmbr);

		flag = 0;

		if (wishItemNmbr < MIN_ALLOWED_ITEM || wishItemNmbr > MAX_ALLOWED_ITEM) {
			printf("ERROR: List is restricted to between %d and %d items.\n", MIN_ALLOWED_ITEM, MAX_ALLOWED_ITEM);
			flag = 1;
		}

		printf("\n");

	} while (flag);


	for (i = 0; i < wishItemNmbr; i++) {

		printf("Item-%d Details:\n", i + 1);

		do {
			printf("   Item cost: $");
			scanf("%lf", &itemCost[i]);

			flag = 0;

			if (itemCost[i] < MIN_COST) {
				printf("      ERROR: Cost must be at least $100.00\n");
				flag = 1;
			}

		} while (flag);

		do {
			printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
			scanf("%d", &itemPriority[i]);

			flag = 0;

			if (itemPriority[i] < MIN_PRIORITY || itemPriority[i] > MAX_PRIORITY) {
				printf("      ERROR: Value must be between %d and %d\n", MIN_PRIORITY, MAX_PRIORITY);
				flag = 1;
			}

		} while (flag);

		do {
			printf("   Does this item have financing options? [y/n]: ");
			scanf(" %c", &financeOptn[i]);

			flag = 0;

			if (!(financeOptn[i] == 'y' || financeOptn[i] == 'n')) {
				printf("      ERROR: Must be a lowercase 'y' or 'n'\n");
				flag = 1;
			}

		} while (flag);

		printf("\n");
	}

	printf("Item Priority Financed        Cost\n");
	printf("---- -------- -------- -----------\n");

	for (i = 0; i < wishItemNmbr; i++) {

		printf("%3d  %5d    %5c    %11.2lf\n", i + 1, itemPriority[i], financeOptn[i], itemCost[i]);

		itemCostSum += itemCost[i];

	}

	printf("---- -------- -------- -----------\n");
	printf("                      $%11.2lf\n\n", itemCostSum);

	do {
		printf("How do you want to forecast your wish list?\n");
		printf(" 1. All items (no filter)\n");
		printf(" 2. By priority\n");
		printf(" 0. Quit/Exit\n");
		printf("Selection: ");
		scanf("%d", &filterChoice);
		printf("\n");


		if (filterChoice > 2 || filterChoice < 0) {
			printf("ERROR: Invalid menu selection.\n\n");
			flag = 1;


		} else if (filterChoice == 1) {

			printf("====================================================\n");
			printf("Filter:   All items\n");
			printf("Amount:   $%1.2lf\n", itemCostSum);

			forecastYear = (int)((itemCostSum / netIncome) + 1) / 12;
			forecastMonth = (int)((itemCostSum / netIncome) + 1) % 12;

			printf("Forecast: %d years, %d months\n", forecastYear, forecastMonth);

			for (i = 0, flag = 1; flag && i < MAX_ALLOWED_ITEM; i++) {

				switch (financeOptn[i]) {
				case 'y':
					printf("NOTE: Financing options are available on some items.\n ");
					printf("     You can likely reduce the estimated months.\n");
					flag = 0;
					break;
				default:
					break;
				}

			}

			printf("====================================================\n\n");
			
			flag = 1;


		} else if (filterChoice == 2) {

			do {
				printf("What priority do you want to filter by? [1-3]: ");
				scanf("%d", &priorityChoice);
				printf("\n");

				flag = 0;

				if (priorityChoice < 1 || priorityChoice > 3) {
					printf("ERROR: Invalid menu selection.\n\n");
					flag = 1;
				}

			} while (flag); 

			printf("====================================================\n");
			printf("Filter:   by priorty (%d)\n", priorityChoice);

			for (i = 0; i < MAX_ALLOWED_ITEM; i++) {

				if (itemPriority[i] == priorityChoice)
					filteredCostSum += itemCost[i];
				}

			printf("Amount:   $%1.2lf\n", filteredCostSum);

			forecastYear = (int)((filteredCostSum / netIncome) + 1) / 12;
			forecastMonth = (int)((filteredCostSum / netIncome) + 1) % 12;

			printf("Forecast: %d years, %d months\n", forecastYear, forecastMonth);


			for (i = 0, flag = 1; flag && i < MAX_ALLOWED_ITEM; i++) {

				if (itemPriority[i] == priorityChoice) {

					switch (financeOptn[i]) {
					case 'y':
						printf("NOTE: Financing options are available on some items.\n ");
						printf("     You can likely reduce the estimated months.\n");
						flag = 0;
						break;
					default:
						break;
					}

				}

			}

			printf("====================================================\n\n");
			
			filteredCostSum = 0;
			flag = 1;


		} else if (filterChoice == 0) {
			flag = 0;
		}

	} while (flag);


	printf("Best of luck in all your future endeavours!\n");

	return 0;
}


