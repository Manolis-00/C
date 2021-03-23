#include <stdio.h>
#include <math.h>

int getData(int userInput);
float calculateRadians(float degrees);
float calculateSine(float radians);
float calculateCosine(float radians);
int compare(float radians);

#define APOKLISI 0.0000009
#define DIAFORA 0.000006
#define HALFCIRCLE 180
#define AKRIVEIA 10000000

int main()
{
	int inputInDegrees;
	float radians, sine, cosine;
	
	inputInDegrees = getData(inputInDegrees);
	radians = calculateRadians(inputInDegrees);
	sine = calculateSine(radians);
	cosine = calculateCosine(radians);
	if (compare(radians) == 1)
		printf("The sine is %f rad and the cosine is %f rad.", sine, cosine);
	else
		printf("mistake");
}

int getData(int userInput)
{
	printf("Please give an integer from 0 to 360 : ");
	scanf("%i", &userInput);
	while ((userInput < 0) || (userInput > 360))
	{
		printf("Please give an integer from 0 to 360 : ");
		scanf("%i", &userInput);
	}
	return userInput;
}

float calculateRadians(float degrees)
{
	degrees = degrees * (M_PI / HALFCIRCLE);
	return degrees; 
}

float calculateSine(float radians)
{
	double firstDivision, secondDivision, condition, firstDivisor, secondDivisor, sine;
	int numberOfCalculations;
	firstDivision = radians / 1.0;
	secondDivision = 10;
	firstDivisor = 2.0;
	secondDivisor = 3.0;
	numberOfCalculations = 1;
	condition = 1.0;
	sine = firstDivision;
	
	while (condition >= DIAFORA)
	{
		secondDivision = firstDivision * (radians * radians)/(firstDivisor * secondDivisor);
		firstDivisor += 2.0;
		secondDivisor += 2.0;
		condition = fabs(firstDivision - secondDivision);
		if (numberOfCalculations % 2 == 1)
			sine -= secondDivision;
		else 
			sine += secondDivision;
		firstDivision = secondDivision;
		numberOfCalculations += 1;
	}
	sine = floor(AKRIVEIA * sine) / AKRIVEIA;
	return sine;
}

float calculateCosine(float radians)
{
	double firstDivision, secondDivision, condition, firstDivisor, secondDivisor, cosine;
	int numberOfCalculations;
	firstDivision = 1.0;
	secondDivision = 10;
	firstDivisor = 1.0;
	secondDivisor = 2.0;
	numberOfCalculations = 1;
	condition = 1.0;
	cosine = firstDivision;
	
	while (condition >= DIAFORA)
	{
		secondDivision = firstDivision * (radians * radians)/(firstDivisor * secondDivisor);
		firstDivisor += 2.0;
		secondDivisor += 2.0;
		condition = fabs(firstDivision - secondDivision);
		if (numberOfCalculations % 2== 1)
			cosine -= secondDivision;
		else
			cosine += secondDivision;
		firstDivision = secondDivision;
		numberOfCalculations +=1;
	}
	cosine = floor(AKRIVEIA * cosine) / AKRIVEIA;
	return cosine;
}

int compare(float radians)
{
	double sine = sin(radians);
	double cosine = cos(radians);
	if (fabs(sine - calculateSine(radians)) < APOKLISI && fabs(cosine - calculateCosine(radians)) < APOKLISI)
		return 1;
}

