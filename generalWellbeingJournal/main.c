/*
	==================================================
	GENERAL WELLBEING JOURNAL
	==================================================
	Author : Muhammad Ahmed [4zad]
	Email  : mahmed.4zad@gmail.com
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define LOG_DAYS 3
#define MIN_YEAR 2010
#define MAX_YEAR 2021

int main(void) {

	const int JAN = 1, DEC = 12;
	const double maxRate = 5.0, minRate = 0.0;
	int i, flag, yearNmbr, monthNmbr, dateNmbr = 1;
	double morRate, eveRate, morTotal = 0.0, eveTotal = 0.0;

	printf("General Well-being Log\n");
	printf("======================\n");

	do {
		printf("Set the year and month for the well-being log (YYYY MM): ");
		scanf("%d %d", &yearNmbr, &monthNmbr);

		flag = 0;

		if (!(yearNmbr >= MIN_YEAR && yearNmbr <= MAX_YEAR)) {
			printf("   ERROR: The year must be between %d and %d inclusive\n", MIN_YEAR, MAX_YEAR);
			flag = 1;
		}

		if (!(monthNmbr <= DEC && monthNmbr >= JAN)) {
			printf("   ERROR: Jan.(%d) - Dec.(%d)\n", JAN, DEC);
			flag = 1;
		}

	} while (flag);

	printf("\n*** Log date set! ***\n\n");

	for (i = LOG_DAYS; i > 0; i--, dateNmbr++) {

		switch (monthNmbr) {
		case 1:
			printf("%d-JAN-%02d\n", yearNmbr, dateNmbr);
			break;

		case 2:
			printf("%d-FEB-%02d\n", yearNmbr, dateNmbr);
			break;

		case 3:
			printf("%d-MAR-%02d\n", yearNmbr, dateNmbr);
			break;

		case 4:
			printf("%d-APR-%02d\n", yearNmbr, dateNmbr);
			break;

		case 5:
			printf("%d-MAY-%02d\n", yearNmbr, dateNmbr);
			break;

		case 6:
			printf("%d-JUN-%02d\n", yearNmbr, dateNmbr);
			break;

		case 7:
			printf("%d-JUL-%02d\n", yearNmbr, dateNmbr);
			break;

		case 8:
			printf("%d-AUG-%02d\n", yearNmbr, dateNmbr);
			break;

		case 9:
			printf("%d-SEP-%02d\n", yearNmbr, dateNmbr);
			break;

		case 10:
			printf("%d-OCT-%02d\n", yearNmbr, dateNmbr);
			break;

		case 11:
			printf("%d-NOV-%02d\n", yearNmbr, dateNmbr);
			break;

		case 12:
			printf("%d-DEC-%02d\n", yearNmbr, dateNmbr);
			break;

		}

		do {
			printf("   Morning rating (%.1lf-%.1lf): ", minRate, maxRate);
			scanf("%lf", &morRate);

			flag = 0;

			if (morRate > maxRate || morRate < minRate) {
				printf("        ERROR: Rating must be between %.1lf and %.1lf inclusive!\n", minRate, maxRate);
				flag = 1;
			}

		} while (flag);

		do {
			printf("   Evening rating (%.1lf-%.1lf): ", minRate, maxRate);
			scanf("%lf", &eveRate);

			flag = 0;

			if (eveRate > maxRate || eveRate < minRate) {
				printf("        ERROR: Rating must be between %.1lf and %.1lf inclusive!\n", minRate, maxRate);
				flag = 1;
			}

		} while (flag);

		printf("\n");

		morTotal += morRate;
		eveTotal += eveRate;

		morRate = -1.0;
		eveRate = -1.0;
	}

	printf("Summary\n");
	printf("=======\n");

	printf("Morning total rating: %.3lf\n", morTotal);
	printf("Evening total rating: %.3lf\n", eveTotal);
	printf("----------------------------\n");
	printf("Overall total rating: %.3lf\n\n", eveTotal + morTotal);

	printf("Average morning rating:  %.1lf\n", morTotal / 3);
	printf("Average evening rating:  %.1lf\n", eveTotal / 3);
	printf("----------------------------\n");
	printf("Average overall rating:  %.1lf\n", (eveTotal / 3 + morTotal / 3) / 2);


	return 0;
}


