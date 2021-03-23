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
	
	//������ ����������
	int *numberOfMines, *numberOfRows, *numberOfColumns, mines, rows, columns;
	
	//������� ����� �� ����������
	numberOfMines = &mines;
	numberOfRows = &rows;
	numberOfColumns = &columns;
	
	//����� ����������
	intializeTableAndMines(numberOfMines, numberOfRows, numberOfColumns);
	
	//�������� �������� ������ ��� ��� ���������� ������
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
	
	//������� ��� ������
	initiateArray(table, rows, columns);

	//�������� ������
	minesInArray(table, mines, rows, columns);
	
	//����������� ��� ������� ��� ���������� ��� ������
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
	
	//������� ��� ���������� ��� ��� ������
	userInput(table, helperTable, mines, rows, columns, squares);
	
	//����������� ��� ������ ��� ���������� ��������
	free(table);
	free(helperTable);
	
	return 0;
}

//��������� ��� ����������� ��� ������ ��� ��� ������ ��� �������� �� �����
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

//������� ��� ����� ��� �������� ��� ��� ������
int checkPositivity(int input)
{
	do
	{
		scanf("%d", &input);
	} 
	while (input < ZERO);
	
	return input;
}

//������� ��� ������ �� ����
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

//�������� ��� ������ ���� ������
void minesInArray(char **table, int mines, int rows, int columns)
{
	int i, x, y;
	int *horizontalLine, *verticalLine;
	
	horizontalLine = &x;
	verticalLine = &y;
	
	for(i = 0; i < mines; i++)
	{
		//������ ���������� ��� ������
		positionOfMines(table, rows, columns, horizontalLine, verticalLine);
		table[x][y] = MINE;
	}
}

//���������� ��� ������ �� ������ �������� ������ ��� ������
void positionOfMines(char **table, int rows, int columns, int *horizontalLine, int *verticalLine)
{
	do
	{
		*horizontalLine = rand() % rows;
		*verticalLine = rand() % columns;
	}
	while (table[*horizontalLine][*verticalLine] == MINE);
}

//����������� ��� ������� ��� ���������� ��� ������
int calculateSquares(int rows, int columns)
{
	int number;
	
	number = rows * columns;
	
	return number;
}

//������� ������������� ���������� ��� ��� ������
void userInput(char **table, char **helperTable, int mines, int rows, int columns, int squares)
{
	int emptySquares, x, y;
	
	//����������� ������� ���������� ����� ������
	emptySquares = squares - mines;
	printf("Lets's Play!!! \n\n\n");

	//�������� ����� ������ ������� �� ��� ���������� ��� �������
	printEmptyArray(helperTable, rows, columns);
	printf("\n\n\n");
	
	do 
	{
		printf("Please give the coordinates for the square that you want to pick. Starting from zero, up to one less of the length of each dimension.\n");

	//������� ��� �� ������� ��� �������� ��� ��� ������ ����� ����� ��� ����� ��� ����������
		x = checkNumber(rows);
		y = checkNumber(columns);
		
		//�������� ��� ������ ����� � ������� ������ ������������ ��� �������� ��� ������
		printModifiedArray(table, helperTable, rows, columns, x, y);
		
		if(table[x][y] != MINE)
			emptySquares--;
	}
	while(emptySquares != ZERO && table[x][y] != MINE);
	
	if(emptySquares == ZERO)
	{
		printf("Congratulations!!! You won!!!");
		//���������� ��� �������	
		makeFile(helperTable, rows, columns);
	}
	else if(table[x][y] == MINE)
	{
		printf("You lost the game.");
		//���������� ��� �������
		makeFile(helperTable, rows, columns);
	}
}

//�������� ����� ������
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


//'������� ��� ������� ��� �������� ��� ��� ������
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

//�������� ��� ������ ���� ��� �������� ��� ���������� ���� ������
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
					//����������� ��� ������ ��� ������� ���������
					helperTable[i][j] = mineCounter(table, rows, columns, x, y) + '0';
				}
			}
			printf("%c|", helperTable[i][j]);
		}
		printf("\n");
	}
}

//�������� ������ ��� ������� ���������
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

//������� �������, ���� � ������� ��� ���������� �� ����� ����� ����� ��� ����� ��� ������
int checkTableLimits(int x, int y, int rows, int columns)
{
    return ((y >= ZERO && y < rows) && (x >= ZERO && x < columns));
}
		
//���������� ������� ������ .txt ��� ����� ����������� � ������ ����� ��� ����������		
void makeFile(char **helperTable, int rows, int columns)
{
	//���������� �������
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
	
	//�������� �������
	fclose(textFile);
}
	

