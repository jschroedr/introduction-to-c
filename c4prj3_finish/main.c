#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
#include <string.h>


int checkCmdArgs(int argc, char ** argv) {
  // check argc at least one for the input file
  if (argc < 2) {
    perror("Expecting at least one argument");
    return -1;
  }
  
  // check argv[1]
  // check that the file can be opened and closed
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    perror("Cannot open input file");
    return -1;
  }
  if(fclose(f) == EOF) {
    perror("Cannot close input file");
    return -1;
  }

  // check argv[2] (optional, based on argc)
  if(argc > 2) {
    return 2;  // num_trials was provided
  } else {
    return 1;  // use default num trials
  }
}


int trialsFromString(char * str) {
  int len = strlen(str);
  if(len == 0) {
    perror("Invalid trials provided");
    return -1;
  }
  len --;  // zero index the length
  int value = 0;
  int iCount = 0;
  for(int i = len; i >= 0; i --) {
    int iValue = str[i] - '0';
    if(iCount == 0) {
      value += iValue;
    } else {
      value += (iValue * toPower(10, iCount));
    }
    iCount ++;
  }
  return value;
}




int main(int argc, char ** argv) {

  // Check command line arguments / report errors
  int cmdCheck = checkCmdArgs(argc, argv);
  if(cmdCheck == -1) {
    perror("Invalid command line arguments provided");
    return EXIT_FAILURE;
  }
  int num_trials = -1;
  if(cmdCheck == 1) {
    // no 'times' argument provided, use default of 10,000
    num_trials = 10000;
  } else if (cmdCheck == 2) {
    // argument provided, use accordingly
    // TODO: convert times into an integer values and test
    num_trials = trialsFromString(argv[2]); 
    if(num_trials == -1) {
      perror("Could not read num_trials from stdin");
      return EXIT_FAILURE;
    }
  } else {
    perror("Unexpected return from checkCmdArgs.");
    return EXIT_FAILURE;
  }
  
  // Open the input file and read the hands in it
  FILE * f = fopen(argv[1], "r");
  size_t * n_hands = malloc(sizeof(*n_hands));
  future_cards_t * fc = malloc(sizeof(*fc));
  deck_t ** hands = read_input(f, n_hands, fc);

  // Create a deck with the remaining cards
  deck_t * rem_deck = build_remaining_deck(hands, *n_hands);
  printf("\n%zu", rem_deck->n_cards);
  
  // Create an array to count how many times each hand wins (plus one for ties)
  int total_hands = (int)(*n_hands + 1);
  int * win_array = malloc(sizeof(*win_array) * total_hands);
  for(int i = 0; i < total_hands; i++) {
    win_array[i] = 0;
  }
  printf("\n%d", win_array[0]);
  printf("\n total_hands: %d \n", total_hands);
  
  // Do each Monte Carlo trial (repeat num_trials times)

  // Shuffle the deck of remaining cards (wrote shuffle in course 3)

  // Assign unknown cards from the shuffled deck (future_cards_From_deck)

  // compare_hands to fiture out which hand won
  // NOTE: with more than two hands, this is much like finding the max of an array
  // but using compare_hands instead of > (qsort?)

  // Increment the win count for the winning hand
  // (or for the ties element of the array if there was a tie)


  // After you do all your trials, you just need to:

  // Print your results
  // For each hand, you should:
  // printf("Hand %zu won %u / %u times (%.2f%%)\n");
  // where:
  // %zu is the hand number (for size_t)
  // %u is the number of wins for the hand
  // %u is the total number of trials
  // %.2f is the percentages that this win/trials ratio gives

  // Then you should printf one more line for the ties:
  // "And there were %u ties\n"
  // Where %u is just a count of how many ties there were
  
  // Free any memory allocated

  // Close any open files

  
  // Makefile should create a program called poker when we run "make"
  // USe test cases in provided-tests, along with the expected probabilities
  // in provided-tests/answers.txt
  // probabilities do not have to e exact and do not have to always add to 100%
  // due to ties

  // things are built for debugging by default, to build for performance run
  // make clean
  // make OTHERFLAGS=-O3
  
  return EXIT_SUCCESS;
}
