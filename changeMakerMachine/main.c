/*
	==================================================
	CHANGE MAKER MACHINE
	==================================================
	Author : Muhammad Ahmed [4zad]
	Email  : mahmed.4zad@gmail.com
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {

	double amount, fee;
	int nmbrToonies, nmbrLoonies, nmbrQuarters, nmbrDimes, nmbrNickels, nmbrPennies;

	printf("Change Maker Machine\n====================\n");
	printf("Enter dollars and cents amount to convert to coins: $");
	scanf("%lf", &amount);

	fee = amount * 0.05;			//fee calulation
	printf("Service fee (5.0 percent): %.2lf\n", fee);

	amount = amount - fee;			//calculation of amount remaining to dispense
	printf("Balance to dispense: $%.2lf\n\n", amount);

	amount = (amount + 0.005) * 100;			//rounding up, then truncation when casting to int type will ensure the values are accurately rounded


	//calculations for how many of the individual coins are to be dispensed start here

		nmbrToonies = (int)amount / 200;
		amount = (int)amount % 200;

		printf("$2.00 Toonies  X %d (remaining: $%.2lf)\n", nmbrToonies, amount/100);

		nmbrLoonies = (int)amount / 100;
		amount = (int)amount % 100;
		
		printf("$1.00 Loonies  X %d (remaining: $%.2lf)\n", nmbrLoonies, amount/100);

		nmbrQuarters = (int)amount / 25;
		amount = (int)amount % 25;

		printf("$0.25 Quarters X %d (remaining: $%.2lf)\n", nmbrQuarters, amount/100);

		nmbrDimes = (int)amount / 10;
		amount = (int)amount % 10;

		printf("$0.10 Dimes    X %d (remaining: $%.2lf)\n", nmbrDimes, amount/100);

		nmbrNickels = (int)amount / 5;
		amount = (int)amount % 5;

		printf("$0.05 Nickels  X %d (remaining: $%.2lf)\n", nmbrNickels, amount/100);

		nmbrPennies = (int)amount;
		amount = (int)amount % 1;

		printf("$0.01 Pennies  X %d (remaining: $%.2lf)\n\n", nmbrPennies, amount/100);


	printf("All coins dispensed!\n");			//all coins have been dispensed

	return 0;			//end
}

