#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include "deck.h"


// write tests here
void test_add_card_to() {
  deck_t * testDeck = malloc(sizeof(deck_t));
  testDeck->n_cards = 0;
  testDeck->cards = NULL;
  card_t c;
  c.suit = 1;
  c.value = 1;
  add_card_to(testDeck, c);
  printf("test_add_card_to: run success\n");
  free_deck(testDeck);
}


int main() {
  test_add_card_to();

  return EXIT_SUCCESS;
}
