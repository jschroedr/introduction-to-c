#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

/**
 * print_hand
 * ===============================================
 * Print each card in hand using print_card
 * Print a space after each card
 * Do not print a newline after each hand
 *
 * @param hand: ptr to deck_t struct
 */
void print_hand(deck_t * hand){
  // access the value of a pointer to a struct using ->
  for(int i = 0; i < hand->n_cards; i ++) {
    // dereference the cards ** for index i
    print_card((*hand->cards[i]));
    printf(" ");
  }
}

/**
 * deck_contains
 * ===============================================
 * Check if a deck contains a particular card or
 * not.
 * If the deck does contain the card, this 
 * function should return a 1. Otherwise return 0.
 * 
 */
int deck_contains(deck_t * d, card_t c) {
  for(int i = 0; i < d->n_cards; i ++) {
    card_t thisCard = (*d->cards[i]);
    if((thisCard.suit == c.suit) && (thisCard.value == c.value)) {
      return 1;
    }
  }
  return 0;
}

/**
 * limitedRandom
 * ===============================================
 * Credit: https://stackoverflow.com/questions/
 * 3746814/create-a-random-number-less-than-a-
 * max-given-value
 *
 */
int limitedRandom(int limit) {
  int r = RAND_MAX / limit;
  int d = RAND_MAX / limit;
  limit *= d;
  do {
    r = random();
  } while (r >= limit);
  return r / d;
}


/**
 * shuffle
 * ===============================================
 * Take a deck and shuffles it, randomly permuting
 * the order of the cards.
 * 
 * Use random to generate psuedo-random numbers.
 *
 * Take a small number of cards, and use random
 * numbers to swap their order, pick positions for
 * them or similar principles
 */
void shuffle(deck_t * d){
  for(int i = 0; i < d->n_cards; i ++) {
    int position = limitedRandom(d->n_cards);
    card_t * thisCard = d->cards[i];
    d->cards[i] = d->cards[position];
    d->cards[position] = thisCard;
  }
}

/**
 * assert_full_deck
 * ===============================================
 * Check that the deck contains every valid card
 * exactly once.
 * 
 * If the deck has any problems, this function
 * should fail an assert.
 * 
 * This will be used to check your deck shuffling,
 * we will shuffle a full deck, then call this
 * function so that you can identify problems
 * with the deck.
 *
 * You can print any error messages you want.
 * Hint: you already wrote deck_contains.
 */
void assert_full_deck(deck_t * d) {
  for(int value = 2; value <= VALUE_ACE; value ++) {
    for(int suit = SPADES; suit <= CLUBS; suit ++) {
      card_t checkCard = {
	.suit = suit,
	.value = value
      };
      int found = deck_contains(d, checkCard);
      if(found == 0) {
	printf("Deck does not contain the following card\n");
	print_card(checkCard);
	printf("\nDeck was as follows\n");
	print_hand(d);
      }
      assert(found == 1);
    }
  }
}
