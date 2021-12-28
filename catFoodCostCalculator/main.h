/*
	==================================================
	CAT FOOD COST CALCULATOR
	==================================================
	Author : Muhammad Ahmed [4zad]
	Email  : mahmed.4zad@gmail.com
*/

#define MAX_PRODUCT 3
#define GRAM_SUGGESTED 64
#define KG_LBS_CONVERSION 2.20462

//-----------------------------------
//Structures
struct CatFoodInfo {

	int skuNmbr;
	int calPerServing;
	double prodPrice;
	double prodWeight;

};

struct ReportData {

	int skuNmbr;
	int calPerServing;
	int prodWeightG;
	double prodPrice;
	double prodWeightLbs;
	double prodWeightKg;
	double servingTotal;
	double costPerServing;
	double costPerCalorie;

};


// 1. Get user input of int type and validate for a positive non-zero number
int getIntPositive(int* intPointer);

// 2. Get user input of double type and validate for a positive non-zero number
double getDoublePositive(double* doublePointer);

// 3. Opening Message (include the number of products that need entering)
void openingMessage(const int prodQuantity);

// 4. Get user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(const int prodSequenceNmbr);

// 5. Display the formatted table header
void displayCatFoodHeader(void);

// 6. Display a formatted record of cat food data
void displayCatFoodData(const int skuNmbr, const int calPerServing, const double *prodPrice, const double *prodWeight);

// 8. convert lbs: kg
double convertLbsKg(const double* weightLbs, double* weightKg);

// 9. convert lbs: g
int convertLbsG(const double* weightLbs, int* weightG);

// 10. convert lbs: kg / g
void convertLbs(const double* weightLbs, double* weightKg, int* weightG);

// 11. calculate: servings based on gPerServ
double calculateServings(const int gramPerServing, const int gramTotal, double* productServingTotal);

// 12. calculate: cost per serving
double calculateCostPerServing(const double* productPrice, const double* productServingTotal, double* productCostPerServing);

// 13. calculate: cost per calorie
double calculateCostPerCal(const double* productPrice, const double* productCalorieTotal, double* productCostPerCalorie);


// 14. Derive a reporting detail record based on the cat food product data
struct ReportData calculateReportData(const struct CatFoodInfo catFoodInfo);

// 15. Display the formatted table header for the analysis results
void displayReportHeader(void);

// 16. Display the formatted data row in the analysis table
void displayReportData(const struct ReportData reportData, const int cheapest);

// 17. Display the findings (cheapest)
void displayFinalAnalysis(const struct CatFoodInfo catFoodInfo);

// 7. Logic entry point
void start(void);



