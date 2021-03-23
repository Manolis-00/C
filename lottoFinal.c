#include <stdio.h>
#include <stdlib.h>

#define ZERO 0
#define ONE 1
#define SIX 6
#define SEVEN 7
#define TWENTY_ONE 21
#define FORTY_NINE 49
#define TWO_HUNDRED_SEVENTY_NINE 279
#define SIX_FACTORIAL 720

int defineArraySize(int, int );
void populateArray(int *, int);
int getBoundaries(int, int);
void sortArray(int *, int);
void formPossibleCombinations(int *, int *, int, int, int, int, int);
int checkRound(int *, int, int, int, int, int, int, int, int);
void printMessages(int, int, int);
int checkSum(int *, int, int, int, int, int, int, int, int);
void printCombinations(int *, int, int, int, int, int, int);
void initializeArrayWithZeros(int *, int );
void timesPrinted(int *, int *, int, int, int, int, int, int, int);
void statistics(int *, int *, int);

int main()
{
	//Ορισμός του μεγέθους του πίνακα
	int sizeOfArray =  defineArraySize(SEVEN, FORTY_NINE);
	
	//Δυναμική δέσμευση μνήμης του πίνακα
	int *arrayOfNumbers = (int *)malloc(sizeOfArray * sizeof(int));
	//Δημιουργία helperArray για τον υπολογισμό της συχνότητας κάθε αριθμού
	int *helperArray = (int *)malloc(sizeOfArray * sizeof(int));
	
	//Function για το γέμισμα του πίνακα με αριθμούς οι οποίοι θα δίνονται από τον χρήστη
	populateArray(arrayOfNumbers, sizeOfArray);
	initializeArrayWithZeros(helperArray, sizeOfArray);
	
	
	//Έλεγχος των ορίων των ζυγών αριθμών σε κάθε συνδυασμό
	int roundLowerBound, roundUpperBound;
	printf("Please give the amount of the round numbers in the combination. The values should be between 0 and 6.\n");
	do
	{
		printf("Please give the lesser number : \n");
		roundLowerBound = getBoundaries(ZERO, SIX);
		printf("Please give the greater number : \n");
		roundUpperBound = getBoundaries(ZERO, SIX);
	}
	while(roundLowerBound > roundUpperBound);

	//Έλεγχος των ορίων των αθροισμάτων των στοιχείων κάθε συνδυασμού
	int sumLowerBound, sumUpperBound;
	printf("Please give the sum of the numbers in the combination. The values should be between 21 and 279. \n");
	do 
	{
		printf("Please give the lesser number : \n");
		sumLowerBound = getBoundaries(TWENTY_ONE, TWO_HUNDRED_SEVENTY_NINE);
		printf("Please give the greater number : \n");
		sumUpperBound = getBoundaries(TWENTY_ONE, TWO_HUNDRED_SEVENTY_NINE);
	}
	while(sumLowerBound > sumUpperBound);
	printf("%d %d", sumLowerBound, sumUpperBound);
	
	//Ταξινομεί τον πίνακα σε αύξουσα σειρά
	sortArray(arrayOfNumbers, sizeOfArray);

	//Δημιουγία και εμφάνιση όλων των πιθανών συνδυασμών, λαμβάνοντας υπ'οψιν τους περιορισμούς
	formPossibleCombinations(arrayOfNumbers, helperArray, sizeOfArray, roundLowerBound, roundUpperBound, sumLowerBound, sumUpperBound);
	
	//Αποδέσμευση των δυναμικά δεσμευμένων πινάκων
	free(arrayOfNumbers);
	free(helperArray);
	
	return 0;
}

//Λήψη του μεγέθους του πίνακας, και έλεγχος εγκυρότητας
int defineArraySize(int upperBound, int lowerBound)
{
	int size;
	printf("Please give the total of the numbers that you want. The number should be between 7 and 49. \n");
	do
	{
		scanf("%d", &size);
	}
	while(size < SEVEN || size > FORTY_NINE);
	
	return size;
}

//Γέμισμα του πίνακα, και έλεγχος εγκυρότητας της κάθε τιμής
void populateArray(int *array, int arraySize)
{
	int i;
	
	printf("Please give numbers between 1 and 49 \n");
	
 	for(i = 0; i < arraySize; i++)
 	{
 		do
 		{
 			scanf("%d", &*(array + i));	
		}
		while((*(array + i) < ONE)|| (*(array + i) > FORTY_NINE));
	}
}

//Γέμισμα του helperArray με μηδενικά
void initializeArrayWithZeros(int *array, int arraySize)
{
	int i;
	
	for(i = 0; i < arraySize; i++)
	{
		*(array + i) = ZERO;
	}
}

//Λήψη των ορίων των περιορισμών και έλεγχος εγκυρότητας αυτών
int getBoundaries(int lower, int upper)
{
	int number;
	
	do 
	{
		scanf("%d", &number);
	}
	while(number < lower || number > upper);
	
	return number;
}

//Ταξινόμηση του πίνακα κατ' αύξουσα σειρά
void sortArray(int *array, int arraySize)
{
	int i, j, temp;
	
	for(i = 0; i < arraySize; i++)
	{
		for(j = i + 1; j < arraySize; j++)
		{
			if(*(array + i) > *(array + j))
			{
				temp = *(array + i);
				*(array + i) = *(array + j);
				*(array + j) = temp;
			}
		}
	}
}

//Σύνολο συναρτήσεων που υπολογίζουν τους συνδυασμούς, ελέγχουν τους περιορισμούς και εμφανίζουν τα ζητούμενα
void formPossibleCombinations(int *array, int *helperArray, int arraySize, int roundLower, int roundUpper, int sumLower, int sumUpper)
{
	int i, j, k, l, m, n, roundsInBounds, sumInBound, roundTotal, checkTotalSum, totalCombinations;
	roundsInBounds = ZERO;
	sumInBound = ZERO;
	roundTotal = ZERO;
	checkTotalSum = ZERO;
	totalCombinations = ZERO;
	
	for(i = 0; i <= arraySize-5; i++)
	{
		for(j = i + 1; j <= arraySize-4; j++)
		{
			for(k = j + 1; k <= arraySize-3; k++)
			{
				for(l = k + 1; l <= arraySize-2; l++)
				{
					for(m = l + 1; m <= arraySize-1; m++)
					{
						for(n = m + 1; n < arraySize; n++)
						{
							//Έλεγχος του περιορισμού σχετικά με τους ζυγούς
							roundsInBounds = checkRound(array, i, j, k, l, m, n, roundLower, roundUpper);
							if(roundsInBounds != ZERO)
							{
								//Έλεγχος περιορισμών σχετικά με το άθροισμα των στοιχείων
								sumInBound = checkSum(array, i, j, k, l, m, n, sumLower, sumUpper);
								if(sumInBound == ZERO)
									checkTotalSum ++;
								else
								{
									totalCombinations ++;
									//Υπολογισμός της συχνότητας εμφάνισης κάθε στοιχείου του πίνακα
									timesPrinted(array, helperArray, arraySize, i, j, k, l, m, n);
								}
							}
							else
								roundTotal ++;
						}
					}
				}
			}
		}
	}
	//Εμφάνιση των απαιτούμενων
	printMessages(roundTotal, checkTotalSum, totalCombinations);
	statistics(array, helperArray, arraySize);
}

//Έλεγχος άρτιων σε κάθε συνδυασμό
int checkRound(int *array, int i, int j, int k, int l, int m, int n, int roundLowerBound, int roundUpperBound)
{
	int counter, temp;
	counter = ZERO;
	temp = ZERO;
	
	if(*(array + i) % 2 == ZERO)
		counter += 1;
	if(*(array + j) % 2 == ZERO)
		counter += 1;
	if(*(array + k) % 2 == ZERO)
		counter += 1;
	if(*(array + l) % 2 == ZERO)
		counter += 1;
	if(*(array + m) % 2 == ZERO)
		counter += 1;
	if(*(array + n) % 2 == ZERO)
		counter += 1;
	
	if (counter >= roundLowerBound && counter <= roundUpperBound)
	{
		temp = ONE;	
	}	
	else
		temp = ZERO;
		
	return temp;	
}

//Έλεγχος αθροίσματος κάθε συνδυασμού
int checkSum(int *array, int i, int j, int k, int l, int m, int n, int sumLowerBound, int sumUpperBound)
{
	int counter;
	counter = ZERO;
	
	if( (*(array + i) + *(array + j) + *(array + k) + *(array + l) + *(array + m) + *(array + n) >= sumLowerBound) && (*(array + i) + *(array + j) + *(array + k) + *(array + l) + *(array + m) + *(array + n) <= sumUpperBound))
	{
		counter = 1;
		printCombinations(array, i, j, k, l, m, n);
	}
	else 
		counter = ZERO;
	
	return counter;	
}

//Υπολογισμός των εμφανίσεων κάθε στοιχείου του πίνακα
void timesPrinted(int *array, int *helperArray, int arraySize, int i, int j, int k, int l, int m, int n)
{
	int z;
	
	for(z = 0; z < arraySize; z++)
	{
		if(*(array + z) == *(array + i) ||
			*(array + z) == *(array + j) ||
			*(array + z) == *(array + k) ||
			*(array + z) == *(array + l) ||
			*(array + z) == *(array + m) ||
			*(array + z) == *(array + n))
		{
			*(helperArray + z) += ONE;
		}
	}
}

//Εμφάνιση των μηνυμάτων
void printMessages(int rounds, int sum, int combinationsPrinted)
{
	printf("The sum of the combinations that are out of the bounds of the set for the round numbers is : %d \n", rounds);
	printf("There are %d combinations that are out of the bounds set for the sum of the numbers of each combination. \n", sum);
	printf("The number of combinations printed is : %d \n\n", combinationsPrinted);
}

//Εμφάνιση των συνδυασμών
void printCombinations(int *array, int i, int j, int k, int l, int m, int n)
{
	printf("%d %d %d %d %d %d\n\n", *(array + i), *(array + j), *(array + k), *(array + l), *(array + m), *(array + n));
}

//Εμφάνιση της συχνότητας
void statistics(int *array, int *helperArray, int arraySize)
{
	int i;
	
	for(i = 0; i < arraySize; i++)
	{
		printf("The number %d is printed %d times \n", *(array + i), *(helperArray + i));
	}
}
