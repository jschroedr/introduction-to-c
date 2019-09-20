#include "cards.h"
#include "stdio.h"
#include "assert.h"

void test_assert_card_valid() {
  card_t validCard;
  validCard.value = 2;
  validCard.suit = SPADES;
  printf("Now testing a valid card\n");
  assert_card_valid(validCard);
  printf("\n----------------------------\n");
  
  /*
  card_t invalidCardSuitH;
  invalidCardSuitH.value = 2;
  invalidCardSuitH.suit = 4;  // max should be 3
  printf("Testing Invalid Card with Suit too High\n");
  assert_card_valid(invalidCardSuitH);
  printf("\n---------------------------------\n");
  */

  /*
  card_t invalidCardSuitL;
  invalidCardSuitL.value = 2;
  invalidCardSuitL.suit = -1;
  printf("Testing invalid card with suit too low\n");
  assert_card_valid(invalidCardSuitL);
  printf("\n-------------------------------\n");
  */
  /*
  card_t invalidCardValueH;
  invalidCardValueH.value = 15;
  invalidCardValueH.suit = 2;
  assert_card_valid(invalidCardValueH);
  */
  /*
  card_t invalidCardValueL;
  invalidCardValueL.value = 1;
  invalidCardValueL.suit = 2;
  assert_card_valid(invalidCardValueL);
  */
}


int main(void) {
  /*
  // test_assert_card_valid();

  // ranking_to_string(STRAIGHT_FLUSH);
  // ranking_to_string(NOTHING);
  // printf("%d", STRAIGHT_FLUSH);
  // printf("%d", NOTHING);

  card_t myCard;
  myCard.value = 13;
  myCard.suit = 1;
  char myLetter = value_letter(myCard);
  printf("\n%d\n", myLetter);
  printf("\n%c\n", myLetter);

  char mySuite = suit_letter(myCard);
  printf("%c\n", mySuite);

  print_card(myCard);
  */
  /*
  char testValue = 'A';
  char testSuit = 's';
  card_t testCardFromL = card_from_letters(testValue, testSuit);
  print_card(testCardFromL);
  */
  unsigned myNum;
  myNum = 51;
  card_t testCardFromN = card_from_num(myNum);
  printf("\n%d", testCardFromN.value);
  printf("\n%d\n\n", testCardFromN.suit);
  print_card(testCardFromN);
}
