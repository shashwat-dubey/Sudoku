#include <stdio.h>
#include <stdlib.h>

#define ROWS 9
#define COLS 9
int matrix[ROWS][COLS];

#define notEmpty(X) (X==0)?0:1
#define    Empty(X) (X==0)?1:0

typedef struct candidate
{
	int count;
	int pos[10];
}Candidates;
Candidates cand[9][9];

typedef struct Sudoku_Handle
{
	FILE *inputFile;
	char *inputFileName;
}Sudoku;

int init_Sudoku(Sudoku **handle)
{
	Sudoku *hdl = NULL;
	hdl = malloc(sizeof(Sudoku));
	hdl->inputFileName = "input.txt";
	*handle = hdl;
	return 0;
}

int generateDB(Sudoku *handle)
{
	int i = 0;
	int j = 0;
	int k = 0;
	/* Initialize DB */
	for(i=0; i<ROWS; i++)
		for(j=0; j<COLS; j++)
		{
			cand[i][j].count = 0;
			for(k=0; k<10; k++)
				cand[i][j].pos[k] = 1;
		}
	/* Iterate through matrix to generate DB */
	for(i=0; i<ROWS; i++)
		for(j=0; j<COLS; j++)
		{
			int val = matrix[i][j];
			if(Empty(matrix[i][j]))
			{
				/* Update database */
				//Row-wise
				for(k=0; k<ROWS; k++)
					if(notEmpty(matrix[i][k]))
						cand[i][j].pos[matrix[i][k]] = 0;
				//Col-wise
				for(k=0; k<ROWS; k++)
					if(notEmpty(matrix[k][j]))
						cand[i][j].pos[matrix[k][j]] = 0;
				//Block-Wise
				{
					int rPos = i%3;
					int cPos = j%3;
					switch(rPos)
					{
						case 0: switch(cPos)
							{
							case 0: if(notEmpty(matrix[i+1][j+1]))	cand[i][j].pos[matrix[i+1][j+1]] = 0;	
								if(notEmpty(matrix[i+1][j+2]))	cand[i][j].pos[matrix[i+1][j+2]] = 0;
								if(notEmpty(matrix[i+2][j+1]))	cand[i][j].pos[matrix[i+2][j+1]] = 0;
								if(notEmpty(matrix[i+2][j+2]))	cand[i][j].pos[matrix[i+2][j+2]] = 0;
								break;
							case 1: if(notEmpty(matrix[i+1][j-1]))	cand[i][j].pos[matrix[i+1][j-1]] = 0;
								if(notEmpty(matrix[i+1][j+1]))	cand[i][j].pos[matrix[i+1][j+1]] = 0;
								if(notEmpty(matrix[i+2][j-1]))	cand[i][j].pos[matrix[i+2][j-1]] = 0;
								if(notEmpty(matrix[i+2][j+1]))	cand[i][j].pos[matrix[i+2][j+1]] = 0;
								break;
							case 2: if(notEmpty(matrix[i+1][j-2]))	cand[i][j].pos[matrix[i+1][j-2]] = 0;
								if(notEmpty(matrix[i+1][j-1]))	cand[i][j].pos[matrix[i+1][j-1]] = 0;
								if(notEmpty(matrix[i+2][j-2]))	cand[i][j].pos[matrix[i+2][j-2]] = 0;
								if(notEmpty(matrix[i+2][j-1]))	cand[i][j].pos[matrix[i+2][j-1]] = 0;
								break;
							}
							break;
						case 1: switch(cPos)
						        {
							case 0: if(notEmpty(matrix[i-1][j+1]))	cand[i][j].pos[matrix[i-1][j+1]] = 0;
								if(notEmpty(matrix[i-1][j+2]))	cand[i][j].pos[matrix[i-1][j+2]] = 0;
								if(notEmpty(matrix[i+1][j+1]))	cand[i][j].pos[matrix[i+1][j+1]] = 0;
								if(notEmpty(matrix[i+1][j+2]))	cand[i][j].pos[matrix[i+1][j+2]] = 0;
								break;
							case 1: if(notEmpty(matrix[i-1][j-1]))	cand[i][j].pos[matrix[i-1][j-1]] = 0;
								if(notEmpty(matrix[i-1][j+1]))	cand[i][j].pos[matrix[i-1][j+1]] = 0;
								if(notEmpty(matrix[i+1][j-1]))	cand[i][j].pos[matrix[i+1][j-1]] = 0;
								if(notEmpty(matrix[i+1][j+1]))	cand[i][j].pos[matrix[i+1][j+1]] = 0;
								break;
							case 2: if(notEmpty(matrix[i-1][j-2]))	cand[i][j].pos[matrix[i-1][j-2]] = 0;
								if(notEmpty(matrix[i-1][j-1]))	cand[i][j].pos[matrix[i-1][j-1]] = 0;
								if(notEmpty(matrix[i+1][j-2]))	cand[i][j].pos[matrix[i+1][j-2]] = 0;
								if(notEmpty(matrix[i+1][j-1]))	cand[i][j].pos[matrix[i+1][j-1]] = 0;
								break;
						       }
						       break;
						case 2: switch(cPos)
							{
							case 0: if(notEmpty(matrix[i-2][j+1]))	cand[i][j].pos[matrix[i-2][j+1]] = 0;
								if(notEmpty(matrix[i-2][j+2]))	cand[i][j].pos[matrix[i-2][j+2]] = 0;
								if(notEmpty(matrix[i-1][j+1]))	cand[i][j].pos[matrix[i-1][j+1]] = 0;
								if(notEmpty(matrix[i-1][j+2]))	cand[i][j].pos[matrix[i-1][j+2]] = 0;
								break;
							case 1: if(notEmpty(matrix[i-2][j-1]))	cand[i][j].pos[matrix[i-2][j-1]] = 0;
								if(notEmpty(matrix[i-2][j+1]))	cand[i][j].pos[matrix[i-2][j+1]] = 0;
								if(notEmpty(matrix[i-1][j-1]))	cand[i][j].pos[matrix[i-1][j-1]] = 0;
								if(notEmpty(matrix[i-1][j+1]))	cand[i][j].pos[matrix[i-1][j+1]] = 0;
								break;
							case 2: if(notEmpty(matrix[i-2][j-2]))	cand[i][j].pos[matrix[i-2][j-2]] = 0;
								if(notEmpty(matrix[i-2][j-1]))	cand[i][j].pos[matrix[i-2][j-1]] = 0;
								if(notEmpty(matrix[i-1][j-2]))	cand[i][j].pos[matrix[i-1][j-2]] = 0;
								if(notEmpty(matrix[i-1][j-1]))	cand[i][j].pos[matrix[i-1][j-1]] = 0;
								break;
							}
							break;
					}
				}
				//Calculate Count
				for(k=1; k<10; k++)
					if(notEmpty(cand[i][j].pos[k]))	cand[i][j].count++;
			}	
		}
	return 0;
}

void display()
{
	int i = 0;
	int j = 0;

	printf("------------------------------------\n");
	for(i=0; i<ROWS; i++)
	{
		for(j=0; j<COLS; j++)
		{
			printf(" %d |", matrix[i][j]);
		}
		printf("\n------------------------------------\n");
	}
	return;	
}

void displayDB()
{
	int i = 0;
	int j = 0;
	int k = 0;
	for(i=0; i<ROWS; i++)
	{
		for(j=0; j<COLS; j++)
		{
			if(Empty(matrix[i][j]))
			{
				printf("Location[%d][%d]: ", i, j);
				printf("Count: %d :: ", cand[i][j].count);
				for(k=1; k<10; k++)
				{
					if(cand[i][j].pos[k] != 0)
						printf(" %d", k);
				}
				printf("\n");
			}
		}
	}
	return;
}

void input_data(Sudoku *handle)
{
	int i = 0;
	int j = 0;
	
	handle->inputFile = fopen(handle->inputFileName, "r");	
	for(i=0; i<ROWS; i++)
		for(j=0; j<COLS; j++)
		{
			fscanf(handle->inputFile, "%d", &matrix[i][j]);
		}
	fclose(handle->inputFile);
	return;
}

int validateCell(int row, int col)
{
	int i = 0;
	int prow = row%3;
	int pcol = col%3;
	int val = matrix[row][col];
	/* Validate Row */
	for(i=0; i<ROWS; i++)
		if((matrix[row][col] == matrix[row][i]) && (i != col))
		{
			printf("Row Check: Element Matching at (%d, %d) and (%d, %d) location.\n", row, col, row, i);
			return -1;
		}

	/* Validate Column */
	for(i=0; i<COLS; i++)
		if(matrix[row][col] == matrix[i][col] && (i != row))
		{
			printf("Col Check: Element Matching at (%d, %d) and (%d, %d) location.\n", row, col, i, col);
			return -1;
		}

	/* Validate Block */

	switch(prow)
	{
	case 0: switch(pcol)
		{
		case 0: if((val==matrix[row][col+1])||(val==matrix[row][col+2])||(val==matrix[row+1][col])||(val==matrix[row+1][col+1])||(val==matrix[row+1][col+2])\
				||(val==matrix[row+2][col])||(val==matrix[row+2][col+1])||(val==matrix[row+2][col+2]))	return -1;
				break;
		case 1: if((val==matrix[row][col-1])||(val==matrix[row][col+1])||(val==matrix[row+1][col])||(val==matrix[row+1][col+1])||(val==matrix[row+1][col-1])\
				||(val==matrix[row+2][col])||(val==matrix[row+2][col+1])||(val==matrix[row+2][col-1]))	return -1;
				break;
		case 2: if((val==matrix[row][col-2])||(val==matrix[row][col-1])||(val==matrix[row+1][col-2])||(val==matrix[row+1][col-1])||(val==matrix[row+1][col])\
				||(val==matrix[row+2][col-2])||(val==matrix[row+2][col-1])||(val==matrix[row+2][col]))	return -1;
				break;
		}
		break;
	case 1: switch(pcol)
		{
		case 0: if((val==matrix[row][col+1])||(val==matrix[row][col+2])||(val==matrix[row+1][col])||(val==matrix[row+1][col+1])||(val==matrix[row+1][col+2])\
				||(val==matrix[row-1][col])||(val==matrix[row-1][col+1])||(val==matrix[row-1][col+2]))	return -1;
				break;
		case 1: if((val==matrix[row][col-1])||(val==matrix[row][col+1])||(val==matrix[row+1][col-1])||(val==matrix[row+1][col+1])||(val==matrix[row+1][col])\
				||(val==matrix[row-1][col-1])||(val==matrix[row-1][col])||(val==matrix[row-1][col+1]))	return -1;
				break;
		case 2: if((val==matrix[row][col-2])||(val==matrix[row][col-1])||(val==matrix[row+1][col-2])||(val==matrix[row+1][col-1])||(val==matrix[row+1][col])\
				||(val==matrix[row-1][col-2])||(val==matrix[row-1][col-1])||(val==matrix[row-1][col]))	return -1;
				break;
		}
		break;
	case 2: switch(pcol)
		{
		case 0: if((val==matrix[row][col+1])||(val==matrix[row][col+2])||(val==matrix[row-2][col])||(val==matrix[row-2][col+1])||(val==matrix[row-2][col+2])\
			||(val==matrix[row-1][col])||(val==matrix[row-1][col+1])||(val==matrix[row-1][col+2]))	return -1;
			break;
		case 1: if((val==matrix[row][col-1])||(val==matrix[row][col+1])||(val==matrix[row-2][col-1])||(val==matrix[row-2][col])||(val==matrix[row-2][col+1])\
			||(val==matrix[row-1][col-1])||(val==matrix[row-1][col])||(val==matrix[row-1][col+1]))	return -1;
			break;
			case 2: if((val==matrix[row][col-1])||(val==matrix[row][col-2])||(val==matrix[row-2][col-2])||(val==matrix[row-2][col-1])||(val==matrix[row-2][col])\
				||(val==matrix[row-1][col-2])||(val==matrix[row-1][col-1])||(val==matrix[row-1][col]))	return -1;
				break;
		}
		break;
	}
	return 0;
}

int validate_matrix(Sudoku *handle)
{
	int ret = -1;
	int i = 0;
	int j = 0;
	
	for(i=0; i<ROWS; i++)
		for(j=0;j<COLS; j++)
		{
			if(notEmpty(matrix[i][j]))
			{
				ret = validateCell(i, j);
				if(ret != 0)
					return ret;
			}
		}
	return ret;
}

int updateUniqueCandidates()
{
	int i = 0;
	int j = 0;
	int k = 0;
	int value = 0;
	for(i=0; i<ROWS; i++)
		for(j=0;j<COLS; j++)
		{
			if(cand[i][j].count == 1)
			{
				for(k=1; k<10; k++)
					if(cand[i][j].pos[k] != 0)
					{
						value = k;
						matrix[i][j] = value;
						cand[i][j].count = 0;
						cand[i][j].pos[k] = 0;
						printf("Updated location(%d, %d) with digit %d.\n", i+1, j+1, value);
						return 1;
					}
			}
		}
	return 0;
	
}

int main()
{
	int status = 0;
	int unqCandLeft = 1;
	Sudoku *handle = NULL;
	init_Sudoku(&handle);
	input_data(handle);
	status = validate_matrix(handle);
	display();
	if(status != 0)
	{
		printf("Invalid input\n");
		return -1;
	}
	generateDB(handle);
	while(unqCandLeft)
	{
		unqCandLeft = updateUniqueCandidates();
		generateDB(handle);
		display();
		displayDB();
		validate_matrix(handle);
		getchar();
	}
	
	return 0;
}
