/*
	==================================================
	CAT FOOD COST CALCULATOR
	==================================================
	Author : Muhammad Ahmed [4zad]
	Email  : mahmed.4zad@gmail.com
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "w6p2.h"

// 1. Get user input of int type and validate for a positive non-zero number
int getIntPositive(int* intPointer) {

	int intInput, positiveValue = 0;

	do {
		scanf("%d", &intInput);

		if (intInput > 0) {
			positiveValue = 1;

		} else {
			printf("ERROR: Enter a positive value: ");

		}

	} while (!positiveValue);

	if (intPointer != NULL)
		*intPointer = intInput;

	return intInput;
}

// 2. Get user input of double type and validate for a positive non-zero number
double getDoublePositive(double* doublePointer) {

	int positiveValue = 0;
	double doubleInput;

	do {
		scanf("%lf", &doubleInput);

		if (doubleInput > 0) {
			positiveValue = 1;

		} else {
			printf("ERROR: Enter a positive value: ");

		}

	} while (!positiveValue);

	if (doublePointer != NULL)
		*doublePointer = doubleInput;

	return doubleInput;
}

// 3. Opening Message (include the number of products that need entering)
void openingMessage(const int prodQuantity) {

	printf("Cat Food Cost Analysis\n");
	printf("======================\n\n");

	printf("Enter the details for %d dry food bags of product data for analysis.\n", prodQuantity);
	printf("NOTE: A 'serving' is %dg\n\n", GRAM_SUGGESTED);

}

// 4. Gets user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(const int prodSequenceNmbr) {

	struct CatFoodInfo catFoodInfo;

	printf("Cat Food Product #%d\n", prodSequenceNmbr + 1);
	printf("--------------------\n");

	printf("SKU           : ");
	catFoodInfo.skuNmbr = getIntPositive(NULL);

	printf("PRICE         : $");
	catFoodInfo.prodPrice = getDoublePositive(NULL);

	printf("WEIGHT (LBS)  : ");
	catFoodInfo.prodWeight = getDoublePositive(NULL);

	printf("CALORIES/SERV.: ");
	catFoodInfo.calPerServing = getIntPositive(NULL);

	printf("\n");

	return catFoodInfo;
}

// 5. Displays the formatted table header
void displayCatFoodHeader(void) {
	printf("SKU         $Price    Bag-lbs Cal/Serv\n");
	printf("------- ---------- ---------- --------\n");
}

// 6. Displays a formatted record of cat food data
void displayCatFoodData(const int skuNmbr, const int calPerServing, const double* prodPrice, const double* prodWeight) {

	printf("%07d %10.2lf %10.1lf %8d\n", skuNmbr, *prodPrice, *prodWeight, calPerServing);

}



// ----------------------------------------------------------------------------
// PART-2

// 8. convert lbs: kg (divide by 2.20462)
double convertLbsKg(const double* weightLbs, double* weightKg) {

	double tempWeightKg = *weightLbs / KG_LBS_CONVERSION;

		if (weightKg != NULL)
			*weightKg = tempWeightKg;

	return tempWeightKg;
}

// 9. convert lbs: g (call convertKG, then * 1000)
int convertLbsG(const double* weightLbs, int* weightG) {

	int tempWeightG = convertLbsKg(weightLbs, NULL) * 1000;

	if (weightG != NULL) 
		*weightG = tempWeightG;
		 
	return tempWeightG;
}

// 10. convert lbs: kg and g
void convertLbs(const double* weightLbs, double* weightKg, int* weightG) {

	*weightKg = convertLbsKg(weightLbs, weightKg);
	*weightG = convertLbsG(weightLbs, weightG);

}

// 11. calculate: servings based on gPerServ
double calculateServings(const int gramPerServing, const int gramTotal, double* productServingTotal) {

	if (productServingTotal != NULL)
		*productServingTotal = (double)gramTotal / (double)gramPerServing;

	return (double)gramTotal / (double)gramPerServing;
}

// 12. calculate: cost per serving
double calculateCostPerServing(const double* productPrice, const double* productServingTotal, double* productCostPerServing) {

	if (productCostPerServing != NULL)
		*productCostPerServing = *productPrice / *productServingTotal;

	return *productPrice / *productServingTotal;
}

// 13. calculate: cost per calorie
double calculateCostPerCal(const double* productPrice, const double* productCalorieTotal, double* productCostPerCalorie) {

	if (productCostPerCalorie != NULL)
		*productCostPerCalorie = *productPrice / *productCalorieTotal;

	return *productPrice / *productCalorieTotal;
}

// 14. Derive a reporting detail record based on the cat food product data
struct ReportData calculateReportData(const struct CatFoodInfo catFoodInfoTemp) {

	struct ReportData reportData;
	double totalCal;

	reportData.skuNmbr = catFoodInfoTemp.skuNmbr;

	reportData.calPerServing = catFoodInfoTemp.calPerServing;

	reportData.prodWeightG = convertLbsG(&catFoodInfoTemp.prodWeight, &reportData.prodWeightG);

	reportData.prodPrice = catFoodInfoTemp.prodPrice;

	reportData.prodWeightLbs = catFoodInfoTemp.prodWeight;

	reportData.prodWeightKg = convertLbsKg(&catFoodInfoTemp.prodWeight, &reportData.prodWeightKg);

	reportData.servingTotal = calculateServings(GRAM_SUGGESTED, reportData.prodWeightG, &reportData.servingTotal);

	reportData.costPerServing = calculateCostPerServing(&reportData.prodPrice, &reportData.servingTotal, &reportData.costPerServing);

	totalCal = reportData.servingTotal * reportData.calPerServing;

	reportData.costPerCalorie = calculateCostPerCal(&reportData.prodPrice, &totalCal, &reportData.costPerCalorie);


	return reportData;
}


// 15. Display the formatted table header for the analysis results
void displayReportHeader(void) {
	printf("\nAnalysis Report (Note: Serving = %dg)\n", GRAM_SUGGESTED);
	printf("---------------\n");
	printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
	printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
}

// 16. Display the formatted data row in the analysis table
void displayReportData(const struct ReportData reportData, const int cheapest) {

	printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf", reportData.skuNmbr, reportData.prodPrice, reportData.prodWeightLbs, reportData.prodWeightKg, reportData.prodWeightG, reportData.calPerServing, reportData.servingTotal, reportData.costPerServing, reportData.costPerCalorie);

	if (cheapest)
		printf(" ***");

	printf("\n");
}

// 17. Display the findings (cheapest)
void displayFinalAnalysis(const struct CatFoodInfo catFoodInfo) {

	printf("\nFinal Analysis\n");
	printf("--------------\n");

	printf("Based on the comparison data, the PURRR-fect economical option is:\n");
	printf("SKU:%07d ", catFoodInfo.skuNmbr);
	printf("Price: $%.2lf\n\n", catFoodInfo.prodPrice);

	printf("Happy shopping!\n");

}

// 7. Logic entry point
void start(void) {

	struct CatFoodInfo catFoodInfo[MAX_PRODUCT] = { { 0 } };
	struct ReportData reportData[MAX_PRODUCT] = { { 0 } };
	int i, cheapestPrice, cheapest = 0;

	openingMessage(MAX_PRODUCT);

	for (i = 0; i < MAX_PRODUCT; i++) {

		catFoodInfo[i] = getCatFoodInfo(i);

		reportData[i] = calculateReportData(catFoodInfo[i]);

	}

	displayCatFoodHeader();

	for (i = 0; i < MAX_PRODUCT; i++) {

		displayCatFoodData(catFoodInfo[i].skuNmbr, catFoodInfo[i].calPerServing, &catFoodInfo[i].prodPrice, &catFoodInfo[i].prodWeight);

	}

	cheapestPrice = reportData[0].costPerServing;

	for (i = 0; i < MAX_PRODUCT; i++) {

		if (reportData[i].costPerServing < cheapestPrice) {

			cheapestPrice = reportData[i].costPerServing;
			cheapest = i;

		}
	}

	displayReportHeader();

	for (i = 0; i < MAX_PRODUCT; i++) {

		if (cheapest == i) {
			displayReportData(reportData[i], 1);

		} else {
			displayReportData(reportData[i], 0);

		}
	}

	displayFinalAnalysis(catFoodInfo[cheapest]);

}



