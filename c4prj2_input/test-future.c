#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "deck.h"
#include "future.h"
#include "input.h"


int main(int argc, char ** argv) {
  FILE * f = fopen("test2.txt", "r");
  future_cards_t * fc = malloc(sizeof(*fc));
  size_t n_hands = 0;
  deck_t ** hands = read_input(f, &n_hands, fc);
  for(int i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
    for(int j = 0; j < hands[i]->n_cards; j++) {
      free(hands[i]->cards[j]);
    }
    free(hands[i]->cards);
    free(hands[i]);
  }
  free(hands);
  for(int i = 0; i < fc->n_decks; i ++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
  fclose(f);
  EXIT_SUCCESS;
}
