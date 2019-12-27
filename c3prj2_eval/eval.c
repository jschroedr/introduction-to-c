#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/**
 * card_ptr_comp
 * ===============================================
 * Comparison function to pass to quicksort
 * 
 * Supports making quicksort sort in DESC order.
 *
 */
int card_ptr_comp(const void * vp1, const void * vp2) {
  // note that vp1 and vp2 are passed as const void *
  // because that is the type that qsort demands
  // so we need to cast to card_t type
  const card_t * const * card1 = vp1;
  const card_t * const * card2 = vp2;

  // perform comparisons on card value first
  // TODO: am I accessing the value of a ptr.ptr right?
  if ((**card1).value > (**card2).value) {
    return -1;
  } else if ((**card1).value == (**card2).value) {
    // if two cards have the same value, compare them by suit
    // in the same order as enum suit_t
    // club < diamond < heart < spade
    if ((**card1).suit > (**card2).suit) {
      return -1;
    } else if ((**card1).suit == (**card2).suit) {
      return 0;
    } else {
      return 1;  // card1.suit < card2.suit
    }
  } else {  // card1.value < card2.value
    return 1;
  }
}


/**
 * flush_suit
 * ===============================================
 * Look at the hand and determine if it is a flush
 * 
 * If so, return the suit f the cards comprising
 * the flush. If not, it returns NUM_SUITS
 *
 */
suit_t flush_suit(deck_t * hand) {
  int topSuitValue = 0;
  int topSuitType = NUM_SUITS;
  int spades = 0;
  int diamonds = 0;
  int hearts = 0;
  int clubs = 0;
  for(int i = 0; i < hand->n_cards; i ++) {
    int thisCardSuit = hand->cards[i]->suit;
    switch(thisCardSuit) {
    case SPADES:
      spades ++;
      if(spades > topSuitValue) {
	topSuitValue = spades;
	topSuitType = SPADES;
      }
    case DIAMONDS:
      diamonds ++;
      if(diamonds > topSuitValue) {
	topSuitValue = diamonds;
	topSuitType = DIAMONDS;
      }
      break;
    case HEARTS:
      hearts ++;
      if(hearts > topSuitValue) {
	topSuitValue = hearts;
	topSuitType = HEARTS;
      }
    case CLUBS:
      clubs ++;
      if(clubs > topSuitValue) {
	topSuitValue = clubs;
	topSuitType = CLUBS;
      }
    default:
      topSuitValue = 0;
      topSuitType = NUM_SUITS;
    }
  }
  if(topSuitValue >= 5) {
    return topSuitType;
  } else {
    return NUM_SUITS;
  }
}

/**
 * get_largest_element
 * ===============================================
 * Returns the largest element in an array of 
 * unsigned integers.
 *
 * This should be familiar from the videos you've
 * watched.
 */
unsigned get_largest_element(unsigned * arr, size_t n) {
  int largestValue = 0;
  int largestIndex = 0;
  for(int i = 0; i < n; i ++) {
    if(arr[i] > largestValue) {
      largestValue = arr[i];
      largestIndex = i;
    }
  }
  return arr[largestIndex];
}

/**
 * get_match_index
 * ===============================================
 * Return the index in the array who value is 
 * n_of_akind. The array has n elements.
 *
 * The array match_counts may have multile values
 * equal to n_of_akind. 
 * 
 * You should return the LOWEST index whose value
 * is n_of_akind [which also guarantees it 
 * corresponds to the largest valued cards, since
 * they will be sorted].
 *
 */
size_t get_match_index(unsigned * match_counts, size_t n, unsigned n_of_akind){
  int index = -1;
  for (int i = 0; i < n; i ++) {
    if (match_counts[i] == n_of_akind) {
      return index;  // return the lowest index (or first matching element)
    }
  }
  // it is guaranteed that n_of_akind is in match_counts
  // if not, you should abort as this is evidence of an error
  if (index == -1) {
    printf("n_of_akind not found in match_counts");
    abort();
  }
  return index;
}

/**
 * find_secondary_pair
 * ===============================================
 * When you want to see if there is another pair
 * to make a hand into a full house or two pairs.
 *
 * The match counts from before, and the index
 * where the original match (pair or three of a
 * a kind) was found.
 * 
 * It should find the index of a card meeting 
 * the following conditions.
 *  - match count is > 1 [at least a pair]
 *  - the card's value is not the same as the 
 *    value of the card at match_idx
 *  - it is the lowest index meeting the first
 *    two conditions
 * 
 * If no such index can be found, this function
 * returns -1
 */
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  return -1;
  /*
  int previousMatchValue = hand->cards[match_idx]->value;
  for(int i = 0; i < hand->n_cards; i ++) {
    int matchCountValue = match_counts[i];
    printf("%d: %d", i, matchCountValue);
    int thisCardValue = hand->cards[i]->value;
    // if the match count is > 1 (2 [pair] or 3 [three-of-a-kind])
    // AND the value of the card is not the same as the previous match
    // (aka. it is a new pairing)
    if((matchCountValue > 1) && (thisCardValue != previousMatchValue)) {
      // ensure we return the lowest index meeting this criteria
      // which will be the start of that pair, and the highest value pair
      // other than the original match
      return i;
    }
  }
  // if no second pair+ is found, then return -1
  return -1;
  */
}

/**
 * is_straight_at
 * ===============================================
 * Determine if there is a straight starting at 
 * index (and only starting at index) in the given
 * hand.
 *
 * If fs is NUM_SUITS, then it should look for any 
 * straight. Else, it should look for a straight 
 * flush in the speified suit.
 * 
 * The function should return:
 * -1: Ace-low straight at index and index is Ace
 * 0 if no straight was found at the index
 * 1 if any other straight was found at the index
 * 
 * Assume the hand is sorted by value DESC when
 * writing this function
 * 
 * Two things to watch for:
 * - Ace-low straights; ace first, then other
 * cards (possibly) then 2, 3, 4, 5 in any
 * order
 * - You may have multiple cards with the same
 * value, but still have a straight
 * 
 */
// definition of helper functions, below
int isNLengthStraightAt(deck_t * hand, size_t index, suit_t fs, int n);
int isAceLowStraightAt(deck_t * hand, size_t index, suit_t fs);
// main function definition
int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if(isAceLowStraightAt(hand, index, fs) == 1) {
    return 1;
  }
  if(isNLengthStraightAt(hand, index, fs, 5)) {
    return 1;
  }
  return 0;
}

/**
 * isNLengthStraightAt
 * ==================================================
 * Check for a straight of N length at index
 * 
 * IF fs is != NUM_SUIT, be strict about matching 
 * suits for a straight flush
 *
 */
int isNLengthStraightAt(deck_t * hand, size_t index, suit_t fs, int n) {
  int straightValue = 1;  // always starting at one so this can == n
  int thisValue = hand->cards[index]->value;
  for(int i = (index + 1); i < hand->n_cards; i ++) {
    int diff = hand->cards[i]->value - thisValue;
    // if tie or one lower, we continue (valid run still possible)
    if(diff <= 1) {
      // if one lower, we might be on a run
      if(diff == 1) {
	// check for suit value - do we need to check for straight flush only?
	if(fs != NUM_SUITS) {
	  // only a matching suit will do
	  if (hand->cards[i]->suit == fs) {
	    straightValue ++;
	  }
	} else {
	  // any suit will do, we are on a run
	  straightValue ++;
	}
      }
    } else {
      // start over, now with this card as thisValue
      thisValue = hand->cards[i]->value;
      straightValue = 1;
    }
  }
  if(straightValue == n) {
    return 1;
  } else {
    return 0;
  }
}

/**
 * isAceLowStraightAt
 * ===========================================
 * Ensure the card given is an Ace
 *
 * Then, check if we have a "5" anywhere in the hand, 
 * matching the suit of "fs" if need be
 *
 * If both of these are true, check for an N length
 * straight of "fs" at the index for the matching "5"
 */
int isAceLowStraightAt(deck_t * hand, size_t index, suit_t fs) {
  // first, check that index is an ace
  if(hand->cards[index]->value != VALUE_ACE) {
    return 0;
  }
  // then, find the 5 we will need to complete the ace-low straight
  int fiveIndex = -1;
  for (int i = 0; i < hand->n_cards; i ++) {
    if(hand->cards[i]->value == 5) {
      // check the suit to see if this needs to be a straight flush
      if(fs != NUM_SUITS) {
	if(hand->cards[i]->suit == fs) {
	  fiveIndex = i;
	  break;
	}
      } else {
	// any suit will do, get the index of the "5" and break
	fiveIndex = i;
	break;
      }
    }
  }
  // if we found a five, there is a chance for an ace low straight
  if(fiveIndex == -1) {
    return 0;
  } else {
    // find the 5, 4, 3, 2 combo we will need to complete the straight
    return isNLengthStraightAt(hand, fiveIndex, fs, 4);
  }
}


/**
 * build_hand_from_match
 * ===============================================
 * This helper fnction will construct hand_eval_t
 * with the ranking and the 5 cards used for it.
 * 
 * This helper function will handle the n of a
 * kind case.
 * 
 * It should make hand_eval_t and set its 
 * ranking to the passed in "what" value.
 * Then it should copy "n" cards from the hand
 * startign at idx into the first n elements of 
 * the hand_event_t's cards array.
 * 
 * The cards field in hand_eval_t is declard as 
 * card_t * cards[5]
 * 
 * This is an array of pointers, each to a card_t.
 * Draw a picture to be sure you know how to name
 * each card_t "box" before you start writing code.
 */
hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  // maximum of two card types in any poker hand
  card_t * cardTypes[2];
  int cardTypesN = 0;
  
  hand_eval_t ans;
  ans.ranking = what;
  int handCount = 0;
  for(int i = idx; i < n; i ++) {
    int newCardType = 1;  // assume new card type to start
    for(int j = 0; j < cardTypesN; j ++) {
      if(hand->cards[i]->value == cardTypes[j]->value) {
	newCardType = 0; // not a new card type
      }
    }
    if (newCardType == 1) {
      cardTypes[cardTypesN] = hand->cards[i];
      cardTypesN ++;
    }
    ans.cards[handCount] = hand->cards[i];
    handCount ++;
  }
  // fill the reaminder of the "cards" array with the
  // highest-value cards from the hand which were not
  // in the n of a kind
  int remainingSpots = 5 - handCount;
  for(int i = 0; i < remainingSpots; i ++) {
    // as long as the card is not part of the pre-existing collection
    if((i != idx) && (i >= (idx + n))) {
      ans.cards[handCount] = hand->cards[i];
      handCount ++;
    }
  }
  return ans;
}


/**
 * compare_hands
 * ===============================================
 * Start by sorting the cards DESC by value
 *  - useful for finding straights
 *  - N of a kind will be grouped together
 *
 * N of a kind should be abstracted to a function,
 * and used to check for a pair, three of a kind, 
 * etc.
 * 
 * Full house and two pair are just combinations 
 * of N of a kind (full house = three of a kind
 * and pair). Write a function to find a 
 * secondary N of a kind.
 * 
 * Two simplifying assumptions:
 *  - a flush will occur in at most one suit
 *  - if there is an ace-high straight, there 
 *    is not also an ace-low straight
 * These assumptionss hold for all majo poker variants
 * 
 */
int compare_hands(deck_t * hand1, deck_t * hand2) {
  // sort each hand DESC using our comparison function
  qsort(hand1, hand1->n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
  qsort(hand2, hand2->n_cards, sizeof(hand2->cards[0]), card_ptr_comp);

  // evaluate each hand, yielding a ranking for each
  hand_eval_t hand1Ranking = evaluate_hand(hand1);
  hand_eval_t hand2Ranking = evaluate_hand(hand2);

  // check if rankings are the same or different
  if(hand1Ranking.ranking == hand2Ranking.ranking) {
    // tiebreaker
    for(int i = 0; i < 5; i ++) {
      if(hand1Ranking.cards[i] > hand2Ranking.cards[i]) {
	return 1;
      }
      if (hand1Ranking.cards[i] < hand2Ranking.cards[i]) {
	return -1;
      }
    }
  } else {
    if(hand1Ranking.ranking > hand2Ranking.ranking) {
      return 1;
    } else {
      return -1;
    }
  }
  return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
