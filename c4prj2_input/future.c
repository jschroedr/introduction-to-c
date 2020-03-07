#include <stdio.h>
#include "future.h"



/**
 * Adds ptr into the future cards for the given index
 * (that is, which ?n it is).
 *
 * I.e. if this is a future card for ?3, then index
 * will be 3. 
 * 
 * ptr will point at an existing placeholder card
 * (it wil point into a hand at a card which was added with
 * add_empty_card)
 */
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  // note, you may have ?3 and then ?4, or ?3 before ?2
  // reallocate the array to be large enough to handle the specified index
  // and just having empty decks for the indicies that have not had
  // add_future_card called on them yet
  if(index >= fc->n_decks) {
    // alloc the missing indicies with empty decks
    for(int i = index; i < (index + 1); i++) {
      deck_t emptyDeck;
      emptyDeck.n_cards = 0;
      emptyDeck.cards = NULL;
      fc->decks = realloc(fc->decks, sizeof(*fc->decks) * (i + 1));
      fc->decks[i] = emptyDeck;
    }
    fc->n_decks = (index + 1);
  }
  fc->decks[index].n_cards ++;
  fc->decks[index].cards = realloc(fc->decks[index].cards, sizeof(fc->decks[index].cards) * fc->decks[index].n_cards);
  fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
  return;
}


/**
 * Takes a deck (which has been shuffled), and a future_cards_t
 * (which has been filled in with all the pointers to placeholders)
 * 
 * Draws cards from the deck and assignes their values and suits
 * to the placeholders pointed to in fc
 *
 * If the deck is As Kh 8c ...
 * And the fc was created from the input 3c 4c ?0 ?1 ?2
 * Then As would be ?0 (which you can find with the pointers in fc)
 * Kh would be ?1 and so on.
 * 
 */
void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  // note: think about a case where this function would print an error message
  
  // draw cards from the deck and assign their values and suits to the placeholders
  for(int i = 0; i < fc->n_decks; i ++) {
    // draw card from deck
    card_t * c = deck->cards[i];
    // for each card in the deck at i, assign c
    for(int j = 0; j < fc->decks[i].n_cards; j++) {
      fc->decks[i].cards[j] = c;
    }
  }
}



