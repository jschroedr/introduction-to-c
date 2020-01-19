#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void performFrequencyCounting(int * letterCounts, FILE * inputFile) {
  int c;
  while((c = fgetc(inputFile)) != EOF) {
    if(isalpha(c)) {
      c = tolower(c);  // lowercase the letter
      int cIndex = (c - 'a');  // get its index
      letterCounts[cIndex] += 1;  // add a count to the roster at letterIndex
    }
  }
} 

void performFrequencyCalculations(float * letterFrequencies, int * letterCounts, int totalLetters) {
  for (int i = 0; i < 26; i ++) {
    letterFrequencies[i] = ((float)letterCounts[i] / (float)totalLetters);
  }
}

// TESTING FUNCTIONS
void printLetters(int * letterCounts) {
   char letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
   for(int i = 0; i <= 25; i ++) {
     printf("\n%c: %d", letters[i], letterCounts[i]);
   }
}
  

void printLetterFrequencies(float * letterFrequencies) {
  char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  for(int i = 0; i < 26; i ++) {
    printf("\n%c: %f", letters[i], letterFrequencies[i]);
  }
}


// GETTER FUNCTIONS
int getTotalLetters(int * letterCounts) {
  int totalLetters = 0;
  for(int i = 0; i < 26; i++) {
    totalLetters += letterCounts[i];
  }
  return totalLetters;
}

int getMaxFrequency(float * letterFrequencies) {
  float maxFrequency = 0.0;
  int maxFrequencyIndex = -1;
  for (int i = 0; i < 26; i ++) {
    if(letterFrequencies[i] > maxFrequency) {
      maxFrequency = letterFrequencies[i];
      maxFrequencyIndex = i;
    }
  }
  return maxFrequencyIndex;
}


int main(int argc, char ** argv) {
  // printf("\nProgram Started");
  // take one command line argument - the name of a file to read as input
  if(argc != 2) {
    fprintf(stderr, "Usage: Expecing 1 argument, inputFileName");
    return EXIT_FAILURE;
  }
  // printf("\nPASS: counted and asserted arguments");
  
  FILE * inputFile = fopen(argv[1], "r");
  if(inputFile == NULL) {
    perror("Could not open file.");
    return EXIT_FAILURE;
  }
  // printf("\nPASS: read inputFile");

  // perform frequency counting on the letters in that text file
  // ignore all non-letter characters
  int letterCounts[26] = {0};
  // printf("PASS: initialized letterCounts");
  
  performFrequencyCounting(letterCounts, inputFile);
  // printf("\nPASS: frequency counted letterCounts");
  
  // TEST: use a test file and print the counts to stdout
  // printLetters(letterCounts);  

  // use the frequency count information to determine which letter is 'e'
  // and solve for the key
  int totalLetters = getTotalLetters(letterCounts);
  // printf("\ntotalLetters = %d", totalLetters);

  float letterFrequencies[26] = {0};
  performFrequencyCalculations(letterFrequencies, letterCounts, totalLetters);

  // TEST: print frequencies to stdout
  // printLetterFrequencies(letterFrequencies);

  // get the max frequency, this is 'e'
  int maxFrequencyIndex = getMaxFrequency(letterFrequencies);
  // printf("maxFrequencyIndex: %d", maxFrequencyIndex);
  
  // find the shift between this and 'e' ('e' is index 5)
  // note: we make maxFrequencyIndex on a non-zero index for human-readable purposes
  int shift = (maxFrequencyIndex + 1) - 5;
  
  // on success, print a single line of output to stdout, which should contain:
  // - one decimal
  // this number should be the encryption key used on the text
  // it should be in the range 0, 26
  // the number you print should obey (0 <= answer <= 26)
  if(shift < 0) {
    shift += 26;
    shift %= 26;
  }
  
  printf("%d", shift);
  
  // on failure, your program should print an appropriate error message
  // to stderr, then exit with EXIT_FAILURE
  if(fclose(inputFile) != 0) {
    perror("Failed to close inputFile!");
    return EXIT_FAILURE;
  }

  
  // provide a makefile which complies your program into a binary called "breaker"
  return EXIT_SUCCESS;
}
