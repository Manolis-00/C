#include <stdio.h>
#include <math.h>

int menuFunction(int a);
double raiseToPower(int base, int exponent);
int calculateFactorial(int a);
int totalCombinations(int a, int b);
void print_menu();
int checkIndicator(int a);

#define RAISE_TO_POWER 1
#define CALCULATE_FACTORIAL 2
#define COMBINATIONS 3
#define EXIT 0
	
int main()
{
	print_menu();
}

void print_menu()
{
	int indicator;
	
	do
	{
		printf("If you want to raise the first number to the power of the second, press 1  \n");
		printf("If you want to calculate the factorial of the numbers, press 2  \n");
		printf("If you want to calculate the combination of the two numbers, press 3  \n");
		printf("If you want to exit the program, press 0  \n");
		scanf("%i", &indicator);
		checkIndicator(indicator);
	} while (indicator != 0);
	
	printf("The number that the user gave a correct choice is %i : ", checkIndicator(indicator)+1);
}

int checkIndicator(int a)
{
	int placeholder,counter;
	if (a == RAISE_TO_POWER
	   || a == CALCULATE_FACTORIAL
	   || a == COMBINATIONS)
		{
			placeholder = menuFunction(a);
			counter = iterations(counter);
		}
		return counter;
}


int menuFunction(int a)
{
	int firstChoice, secondChoice;
	printf("Please enter the first number : \n");
	scanf("%i", &firstChoice);
	printf("Please enter the second number : \n");
	scanf("%i", &secondChoice);
	
	system("cls");
	
	switch(a)
	{
		case RAISE_TO_POWER:
				raiseToPower(firstChoice, secondChoice);
			break;
		case CALCULATE_FACTORIAL:
			{
				if (firstChoice < 0)
					printf("The factorial of a negative can't be calulated\n\n");
				else
					printf("The factorial of %i is :  %i\n", firstChoice, calculateFactorial(firstChoice));
				if (secondChoice < 0)
					printf("The factorial of a negative can't be calulated\n\n");
				else
					printf("The factorial of %i is : %i\n\n", secondChoice, calculateFactorial(secondChoice));
			}
		    break;
		case COMBINATIONS:
				totalCombinations(firstChoice, secondChoice);
		    break;
		case EXIT:
			break;
	}
}

double raiseToPower(int base, int exponent)
{
	printf("The power of the two numbers is %f : \n\n", pow(base, exponent));
}

int calculateFactorial(int a)
{
	int i, factorial;
	factorial = 1;
	for (i = 1; i <= a; i++)
	{
		factorial *= i;
	}
	return factorial;
}

int totalCombinations(int a, int b)
{
	int combinations;
	if (a < 0 || b < 0)
		printf("The function cannot work with negative numbers \n\n");
	else if (a >= b)
	{
		combinations = (calculateFactorial(a)/(calculateFactorial(b) * calculateFactorial(a-b)));
		printf("The number of combinations is %i \n\n", combinations);
	}
	else
		printf("The first number must be greater than the second in order for the function to work  \n\n");
}

int iterations(int a)
{
	a += 1;
	return a;
}
