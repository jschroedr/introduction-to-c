#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void rotate(char matrix[10][10]) {
  char rotatedMatrix[10][10];
  int maxDimension = 10;
  int trueMaxDimension = (maxDimension - 1);
  char value;
  int newX = 0;
  int newY = 0;
  for(int x = 0; x < maxDimension; x ++) {
    for(int y = 0; y < maxDimension; y ++) {
      value = matrix[x][y];
      newX = y;
      newY = trueMaxDimension - x;
      rotatedMatrix[newX][newY] = value;
    }
  }
  for (int x = 0; x < maxDimension; x ++) {
    for(int y = 0; y < maxDimension; y ++) {
      matrix[x][y] = rotatedMatrix[x][y];
    }
  }
}


int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("Incorrect number of arguments supplied. Expecting 2");
    return EXIT_FAILURE;
  }
  FILE * targetFile = fopen(argv[1], "r");
  if (targetFile == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  int c;
  int rowCount = 0;
  int columnCount = 0;
  char matrix[10][10];
  // while we have not reached the end of the file
  while ((c = fgetc(targetFile)) != EOF) {
    // ensure our length does not exceed 10 chars
    if (columnCount > 10) {
      perror("Line too long. Invalid length");
      return EXIT_FAILURE;
    }
    if (rowCount > 10) {
      perror("Too many rows. Expecting 10");
      return EXIT_FAILURE;
    }
    
    // matrix value assignment
    matrix[rowCount][columnCount] = c;
    columnCount ++;
    
    // if a carriage return or line feed, ensure we are at 11
    if(c == 13 || c == 10) {
      if(columnCount != 11) {
	printf("\n%d | %c\nColumn: %d\nRow: %d\n", c, c, columnCount, rowCount);
	perror("Carriage return not at position 10");
	return EXIT_FAILURE;
      } else {
	// valid carriage return at position 10
	columnCount = 0;
	rowCount ++;
      }
    }
    
    // if we are at 11 raise an error - this should be a carriage return
    if(columnCount == 11) {
      if(c != 13 || c != 11) {
	perror("File too long. Expecting 10 characters in length left-to-right");
	return EXIT_FAILURE;
      }
    }

  }
  // ensure the process completed as expected, starting on row 11
  if(rowCount != 10 || columnCount != 0) {
    perror("Matrix not fully formed, please provide valid 10x10 input");
    return EXIT_FAILURE;
  } else {
  // execute rotate function
  rotate(matrix);
  
  // print rotated result on stdout
  for(int y = 0; y < 10; y ++) {
    for(int x = 0; x < 10; x ++) {
	printf("%c", matrix[y][x]);
	if (x == 9) {
	  printf("\n");
	}
      }
    }
  return EXIT_SUCCESS;
  }
}
