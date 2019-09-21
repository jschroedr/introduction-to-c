#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  // assert() to check that the card passd in has valid values
  // between 2 and VALUE_ACE (inclusive)
  assert((c.value >= 2) || (c.value == 0));  // allow for 10
  assert(c.value <= VALUE_ACE);
  // suit should be between SPADES and CLUBS
  assert(c.suit >= SPADES);
  assert(c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  // convert the hand_ranking_t enumerated value into a string
  // emacs keyboard macros might come in handy (see Drew's lesson)
  assert(r <= 8);
  assert(r >= 0);
  switch(r)
    {
    case 0:
      return "STRAIGHT_FLUSH";
    case 1:
      return "FOUR_OF_A_KIND";
    case 2:
      return "FULL_HOUSE";
    case 3:
      return "FLUSH";
    case 4:
      return "STRAIGHT";
    case 5:
      return "THREE_OF_A_KIND";
    case 6:
      return "TWO_PAIR";
    case 7:
      return "PAIR";
    case 8:
      return "NOTHING";
    default:
      return "";
    }
}

char value_letter(card_t c) {
  // return the character that textually represents the value of the passed-in card
  if (c.value < 10) {
    return c.value + 48;
  } else if (c.value == 10) {
    return 48;
  } else {
    switch(c.value)
      {
      case VALUE_JACK:
	return 74; // J
      case VALUE_QUEEN:
	return 81; // Q
      case VALUE_KING:
	return 75; // K
      case VALUE_ACE:
	return 65; // A
      default:
	return 0;
      }
  }
  // for values 2-9, this should be that digit
  // for 10 it should be 0
  // for jack, queen, king and ace, it should be j, q, k and a
  // remember everything is a number
  // for example, 0 has the decimal value 48
  // and 5 has the value 53
  // so '0' + 5 = '5'
  
}


char suit_letter(card_t c) {
  // return the letter that textually represetns the suit of the card passed in
  // ('s', 'h', 'd', or 'c' for SPADES, HEARTS, DIAMONS or CLUBS
  switch(c.suit)
    {
    case 0:
      return 115; // SPADES
    case 1:
      return 104; // HEARTS
    case 2:
      return 100; // DIAMONDS
    case 3:
      return 99; // CLUBS
    default:
      return 0;
    }
}

void print_card(card_t c) {
  // print out the textual representation of the card
  // hint: use the functions your previously wrote
  // print the value first, then the suit
  // As = Ace of Spades
  // NOTE: do note print any spaces or newlines after the card's text
  int value = value_letter(c);
  int suit = suit_letter(c);
  printf("%c%c",  suit, value);
}

card_t card_from_letters(char value_let, char suit_let) {
  // make and return a cart_t whoe value and suit correspond to the letters passed in
  // if the values passed in are invalid
  // use assert() or print an error message and exit(EXIT_FAILURE)
  card_t temp;
  switch (value_let)
    {
    case 74:
	temp.value = VALUE_JACK;
	break;
    case 81:
	temp.value = VALUE_QUEEN;
	break;
    case 75:
	temp.value = VALUE_KING;
	break;
    case 65:
	temp.value = VALUE_ACE;
	break;
    default:
      temp.value = value_let - 48;
      }
  // get the int value from the letter for suit
  switch(suit_let)
    {
    case 115:
      temp.suit = SPADES;  // SPADES
      break;
    case 104:
      temp.suit = HEARTS; // HEARTS
      break;
    case 100:
      temp.suit = DIAMONDS; // DIAMONDS
      break;
    case 99:
      temp.suit = CLUBS; // CLUBS
      break;
    default:
      temp.suit = -1; // INVALID
      break;
    }
  assert(temp.suit != -1);
  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  // take a number from 0 to 52 (excusive)
  // map the number uniquely to a crd value/suit combination
  // exactly how you map the number to values/suits is up to you
  // but you must guarantee that each valid value/suit combination
  // corresponds to exactly one input value in the range [0, 52]
  // Hint: you may want to use the mod operator % to find the remainder of a number divided by 13
  // in course 3, this function will be used to make a deck of cards by iterating over that range
  // and calling it once for each value -- you just need to learn about arrays first so you
  // have a place to put all those cards
  card_t temp;
  temp.suit  = c / 13;  // integer division to determine suit
  temp.value = c - (13 * temp.suit);
  temp.value = (temp.value + 2);  // lowest card is 2, highest is ace
  return temp;
}
