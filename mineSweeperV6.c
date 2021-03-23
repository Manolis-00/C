#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define EMPTY ' '
#define MINE '*'
#define ZERO 0

void intializeTableAndMines(int *, int *, int *);
int checkPositivity(int);
void initiateArray(char **, int, int);
void minesInArray(char **, int, int, int);
void positionOfMines(char **, int, int, int *, int *);
void printEmptyArray(char **, int, int);
void userInput(char **, char **, int, int, int, int);
int checkNumber(int);
int calculateSquares(int, int);
void printModifiedArray(char **, char **, int , int, int, int);
int mineCounter(char **, int, int, int, int);
int checkTableLimits(int, int, int, int);
void makeFile(char**, int, int);

int main(int argc, char **argv)
{
	srand(time(NULL));
	
	//Δήλωση μεταβλητών
	int *numberOfMines, *numberOfRows, *numberOfColumns, mines, rows, columns;
	
	//Ανάθεση τιμής σε μεταβλητές
	numberOfMines = &mines;
	numberOfRows = &rows;
	numberOfColumns = &columns;
	
	//κλήση συνάρτησης
	intializeTableAndMines(numberOfMines, numberOfRows, numberOfColumns);
	
	//Δυναμική δέσμευση μνήμης για την δημιουργία πίνακα
	char **table = (char **)malloc(rows *sizeof(char *));
	if(table == NULL)
		printf("Error in memory allocation");
		
	int i;
	
	for(i = 0; i < rows; i++)
	{
		table[i] = (char*)malloc(columns *sizeof(char));
		if(table[i] == NULL)
			printf("Error in memory allocation");
	}
	
	//Γέμισμα του πίνακα
	initiateArray(table, rows, columns);

	//Προσθήκη ναρκών
	minesInArray(table, mines, rows, columns);
	
	//Υπολογισμός του πλήθους των τετραγώνων του πίνακα
	int squares = calculateSquares(rows, columns);
	
	char **helperTable = (char **)malloc(rows *sizeof(char *));
	if(helperTable == NULL)
		printf("Error in memory allocation");
	
	for(i = 0; i < rows; i++)
	{
		helperTable[i] = (char*)malloc(columns *sizeof(char));
		if(helperTable[i] == NULL)
			printf("Error in memory allocation");
	}
	
	//Επιλογή του τετραγώνου από τον χρήστη
	userInput(table, helperTable, mines, rows, columns, squares);
	
	//Αποδέσμευση της μνήμης που δεσμεύθηκε δυναμικά
	free(table);
	free(helperTable);
	
	return 0;
}

//Συνάρτηση που αρχικοποιεί τον πίνακα και τις νάρκες που υπάρχουν σε αυτόν
void intializeTableAndMines(int *mines, int *rows, int *columns)
{
	int number;
	
	do
	{
		printf("Please give the number of the bombs : \n");
		*mines = checkPositivity(number);
		printf("Please give the number of the rows : \n");
		*rows = checkPositivity(number);
		printf("Please give the number of the columns : \n");
		*columns = checkPositivity(number);
	} 
	while((*mines) > (*rows) * (*columns));
}

//Έλεγχος των τιμών που δίνονται από τον χρήστη
int checkPositivity(int input)
{
	do
	{
		scanf("%d", &input);
	} 
	while (input < ZERO);
	
	return input;
}

//Γέμισμα του πίνακα με ΚΕΝΑ
void initiateArray(char **table, int rows, int columns)
{
	int i, j, sum;

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			table[i][j] = EMPTY;	
		}
	}
}

//Προσθήκη των νάρκων στον πίνακα
void minesInArray(char **table, int mines, int rows, int columns)
{
	int i, x, y;
	int *horizontalLine, *verticalLine;
	
	horizontalLine = &x;
	verticalLine = &y;
	
	for(i = 0; i < mines; i++)
	{
		//Τυχαία τοποθέτηση των ναρκών
		positionOfMines(table, rows, columns, horizontalLine, verticalLine);
		table[x][y] = MINE;
	}
}

//Τοποθέτηση των ναρκών σε τυχαία μοναδικά σημεία του πίνακα
void positionOfMines(char **table, int rows, int columns, int *horizontalLine, int *verticalLine)
{
	do
	{
		*horizontalLine = rand() % rows;
		*verticalLine = rand() % columns;
	}
	while (table[*horizontalLine][*verticalLine] == MINE);
}

//Υπολογισμός του πλήθους των τετραγώνων του πίνακα
int calculateSquares(int rows, int columns)
{
	int number;
	
	number = rows * columns;
	
	return number;
}

//Επιλογή συντεταγμένων τετραγώνου από τον χρήστη
void userInput(char **table, char **helperTable, int mines, int rows, int columns, int squares)
{
	int emptySquares, x, y;
	
	//Υπολογισμός πλήθους τετραγώνων χωρίς βόμβες
	emptySquares = squares - mines;
	printf("Lets's Play!!! \n\n\n");

	//Εμφάνιση κενού πίνακα σύμφωνα με τις διαστάσεις που δόθηκαν
	printEmptyArray(helperTable, rows, columns);
	printf("\n\n\n");
	
	do 
	{
		printf("Please give the coordinates for the square that you want to pick. Starting from zero, up to one less of the length of each dimension.\n");

	//Έλεγχος ότι οι αριθμοί που δίνονται από τον χρήστη είναι εντός των ορίων των διαστάσεων
		x = checkNumber(rows);
		y = checkNumber(columns);
		
		//Εμφάνιση του πίνακα καθώς ο χρήστης παίζει εμφανίζοντας τις επιλογές του χρήστη
		printModifiedArray(table, helperTable, rows, columns, x, y);
		
		if(table[x][y] != MINE)
			emptySquares--;
	}
	while(emptySquares != ZERO && table[x][y] != MINE);
	
	if(emptySquares == ZERO)
	{
		printf("Congratulations!!! You won!!!");
		//Δημιουργία του αρχείου	
		makeFile(helperTable, rows, columns);
	}
	else if(table[x][y] == MINE)
	{
		printf("You lost the game.");
		//Δημιουργία του αρχείου
		makeFile(helperTable, rows, columns);
	}
}

//Εμφάνιση κενού πίνακα
void printEmptyArray(char **helperTable, int rows, int columns)
{
	int i, j;
	
	for(i = 0; i < rows; i++)
	{
		printf("|");
		for(j = 0; j < columns; j++)
		{
			helperTable[i][j] = EMPTY;
			printf("%c|", helperTable[i][j]);
		}
		printf("\n");
	}
}


//'Ελεγχος των αριθμών που δίνονται από τον χρήστη
int checkNumber(int dimension)
{
	int number;
	do
	{
		printf("Please give the number of the desired dimension \n");
		scanf("%d", &number);
	}
	while(number < 0 && number >= dimension);

	return number;
}

//Εμφάνιση του πίνακα μετά τις επιλογές των τετραγώνων στον πίνακα
void printModifiedArray(char **table, char **helperTable, int rows, int columns, int x, int y)
{
	int i, j;
	
	for(i = 0; i < rows; i++)
	{
		printf("|");
		for(j = 0; j < columns; j++)
		{
			if(i == x && j == y)
			{
				if (table[i][j] == MINE)
				{
					helperTable[i][j] = MINE;
				}
				else
				{
					//Καταμέτρηση των ναρκών στα κοντινά τετράγωνα
					helperTable[i][j] = mineCounter(table, rows, columns, x, y) + '0';
				}
			}
			printf("%c|", helperTable[i][j]);
		}
		printf("\n");
	}
}

//Μετρητής ναρκών στα κοντινά τετράγωνα
int mineCounter(char **table, int rows, int columns, int x, int y)
{
		int adjacentMines = ZERO;

        if (checkTableLimits(x, y+1, rows, columns) && table[x][y+1] == MINE)
                adjacentMines++;
        if (checkTableLimits(x, y-1, rows, columns) && table[x][y-1] == MINE)
                adjacentMines++;
        if (checkTableLimits(x+1, y, rows, columns) && table[x+1][y] == MINE)
                adjacentMines++;
        if (checkTableLimits(x-1, y, rows, columns) && table[x-1][y] == MINE)
                adjacentMines++;
        if (checkTableLimits(x-1, y-1, rows, columns) && table[x-1][y-1] == MINE)
                adjacentMines++;
        if (checkTableLimits(x-1, y+1, rows, columns) && table[x-1][y+1] == MINE)
                adjacentMines++;
        if (checkTableLimits(x+1, y-1, rows, columns) && table[x+1][y-1] == MINE)
                adjacentMines++;
        if (checkTableLimits(x+1, y+1, rows, columns) && table[x+1][y+1] == MINE)
                adjacentMines++;
                
        return adjacentMines;
}

//Συνθήκη ελέγχου, ώστε ο έλεγχος των τετραγώνων να είναι πάντα εντός των ορίων του πίνακα
int checkTableLimits(int x, int y, int rows, int columns)
{
    return ((y >= ZERO && y < rows) && (x >= ZERO && x < columns));
}
		
//Δημιουργία αρχείου μορφής .txt στο οποίο εμφανίζεται η τελική μορφή του παιχνιδιού		
void makeFile(char **helperTable, int rows, int columns)
{
	//δημιουργία αρχείου
	FILE *textFile;
	int i, j;
	
	textFile = fopen("D:\\Department of Computer Engineering and Computer Science\\Computer Programming\\Lab\\6\\mineSweeperV6.txt", "w");
	
	for(i = 0; i < rows; i++)
	{
		fprintf(textFile, "|");
		for(j = 0; j < columns; j++)
		{
			fprintf(textFile, "%c|", helperTable[i][j]);
		}
		fprintf(textFile, "\n");
	}
	
	//Κλείσιμο αρχείου
	fclose(textFile);
}
	

