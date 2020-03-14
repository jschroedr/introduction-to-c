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


int * performMonteCarloTrial(
			     int * win_array, deck_t * deck,
			     future_cards_t * fc, deck_t ** hands,
			     size_t * n_hands) {
  // shuffle the deck of remaining cards
  shuffle(deck);
  // assign unknown cards from the shuffled deck
  future_cards_from_deck(deck, fc);
  // compare_hands to figure out which hand won
  int best_hand_index = -1;
  int is_tie = 0;
  for(int i = 0; i < (*n_hands); i ++) {
    // if this is the first iteration, best_hand_index = i
    if(best_hand_index == -1) {
      best_hand_index = i;
    } else {
      int result = compare_hands(hands[i], hands[best_hand_index]);
      if(result == 0) {
	// tie
	is_tie = 1;  // mark that we had a tie at best_hand_index
      } else {
	if(result == 1) {
	  best_hand_index = i;
	  is_tie = 0;  // mark that we not longer had a tie at best_hand_index
	}
	// else do nothing, best_hand_index is still best
      }
    }
  }
  // if we had a tie at the end of it all, then add one to the ties index
  if(is_tie == 1) {
    win_array[*n_hands] ++;
  } else {
    win_array[best_hand_index] ++;
  }
  return win_array;
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
    num_trials = atoi(argv[2]); 
    if(num_trials == 0) {
      perror("Could not read num_trials from stdin with atoi");
      return EXIT_FAILURE;
    }
  } else {
    perror("Unexpected return from checkCmdArgs.");
    return EXIT_FAILURE;
  }
  
  // Open the input file and read the hands in it
  FILE * f = fopen(argv[1], "r");
  size_t * n_hands = malloc(sizeof(*n_hands));
  *n_hands = 0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t ** hands = read_input(f, n_hands, fc);

  // Create a deck with the remaining cards
  deck_t * rem_deck = build_remaining_deck(hands, *n_hands);
  // printf("\n%zu", rem_deck->n_cards);
  
  // Create an array to count how many times each hand wins (plus one for ties)
  int total_hands = (int)(*n_hands + 1);
  int * win_array = malloc(sizeof(*win_array) * total_hands);
  for(int i = 0; i < total_hands; i++) {
    win_array[i] = 0;
  }
  // printf("\n%d", win_array[0]);
  // printf("\n total_hands: %d \n", total_hands);
  
  // Do each Monte Carlo trial (repeat num_trials times)
  for(int i = 0; i < num_trials; i ++) {
    win_array = performMonteCarloTrial(win_array, rem_deck, fc, hands, n_hands);
  }
  
  // After you do all your trials, you just need to:
  // Print your results
  for(int i = 0; i < total_hands; i ++) {
    if(i < (total_hands - 1)) {
      printf("Hand %d won %d / %d times (%.2f%%)\n", i, win_array[i], num_trials, ((float)win_array[i] / (float)num_trials) * 100);
    } else {
      printf("And there were %d ties\n", win_array[i]);
    }
  }
  
  // Free any memory allocated
  for(int d = 0; d < fc->n_decks; d++) {
    free(fc->decks[d].cards);
  }
  free(fc->decks);
  free(fc);
  for(int d = 0; d < (int)(*n_hands); d++) {
    free_deck(hands[d]);
  }
  free(hands);
  free_deck(rem_deck);
  free(n_hands);
  free(win_array);
  
  // Close any open files
  if(fclose(f) == EOF) {
    perror("Could not close file");
    return EXIT_FAILURE;
  }
  
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
