#include<stdio.h>
#include<stdlib.h>
#include "input.h"



/**
 * Reads the input from f
 * 
 * File has one hand per line (deck_t)
 * 
 * Allocates a deck_t for each hand and places it 
 * into an array of pointers to deck_ts, the return value
 */
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** hands = malloc(sizeof(hands));
  fc->decks = NULL;
  fc->n_decks = 0;
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while((len = getline(&line, &sz, f)) >= 0) {
    (*n_hands) ++;
    deck_t * hand = malloc(sizeof(*hand));  // allocate deck for each hand
    hand->n_cards = 0;
    hand->cards = NULL;
    char charArray[2];  // hold two characters for each card
    int charIndex = -1;
    for(int i = 0; i < len; i ++) {
      if(line[i] == '\n') {
	break;
      }
      if(line[i] != ' ') {
	char ch = line[i];
	// -1 = new card
	if(charIndex == -1) {
	  charIndex = 0;
	}
	charArray[charIndex] = ch;
	charIndex ++;
	// 2 = card complete, time for new card
	if(charIndex == 2) {
	  charIndex = -1;
	  if(charArray[0] == '?') {
	    card_t * ptr = add_empty_card(hand);
	    int idx = charArray[1] - 48;
	    add_future_card(fc, idx, ptr);
	  } else {
	    card_t c = card_from_letters(charArray[0], charArray[1]);
	    hand->cards = realloc(hand->cards, sizeof(hand->cards) * (hand->n_cards +1));
	    card_t * cPtr = malloc(sizeof(*cPtr));
	    cPtr->suit = c.suit;
	    cPtr->value = c.value;
	    hand->cards[hand->n_cards] = cPtr; 
	    hand->n_cards ++;
	  }
      	}
      }
    }
    if(hand->n_cards < 5) {
      perror("Poker hand should have at least 5 cards");
      EXIT_FAILURE;
    }
    hands = realloc(hands, sizeof(hands) * (*n_hands));
    hands[(*n_hands) - 1] = hand;
  }
  free(line);
  return hands;
}
