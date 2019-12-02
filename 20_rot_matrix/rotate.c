// includes here


/**
 * rotate
 * ===================================================
 * Takes a 10 by 10 matrix of characters and rotates
 * it 90 degress clockwise, updating the matrix that
 * was passed in (remember that arrays are pointers,
 * so you will modify the array in the frame where it 
 * was created).
 */
void rotate(char matrix[10][10]) {
  // an empty matrix of equal dimensions to store rotation
  char rotatedMatrix[10][10];
  int maxDimension = 10;  // require square
  int trueMaxDimension = (maxDimension - 1);  // account for zero indexing
  // utility values for making the transformation
  char value;
  int newX = 0;
  int newY = 0;
  for(int x = 0; x < maxDimension; x ++) {
    for(int y = 0; y < maxDimension; y ++) {
      value = matrix[x][y];
      // y becomes x
      newX = y;
      // trueMax - old x
      newY = trueMaxDimension - x;
      rotatedMatrix[newX][newY] = value;
    }
  }

  // now write the transformation to the given matrix
  for(int x = 0; x < maxDimension; x++) {
    for(int y = 0; y < maxDimension; y++) {
      matrix[x][y] = rotatedMatrix[x][y];
    }
  }
  
}
