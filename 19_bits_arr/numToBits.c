#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Helper function that retrieves numbers 'bit' value
 * ie: 1's 31st bit is 1
 */
int getNthBit(uint32_t number, int bit) {
  if (bit <0 || bit >= 32) {
    printf("Bit %d is invalid\n", bit);
    exit (EXIT_FAILURE);
  }
  return (number & (1<<bit)) != 0;
}

/**
 * checkBitsRequired
 * ======================================================
 * Each num should have 32 places in bits. 
 * 
 * Given this information, ensure the proper number of 
 * bits have been provisioned.
 */
int checkBitsRequired(int totalBits, int nNums, int nBits) {
  int bitsRequired = (nNums * totalBits);
  if(nBits >= bitsRequired) {
    return 1;
  } else {
    return 0;
  }
}


/*
 *
 * This function takes in two arrays: nums (of length nNums), and
 * bits (of length nBits). This function should:
 *
 * - Check that there is enough space in bits to hold all the bits
 *   of "nums".  Note that each number in "nums" will results in 32
 *   bits in "bits".  If this is not true, your function should
 *   print a message with the format:
 *	"Invalid call to numToBits! nBits is %d, nNums is %d\n",
 *   (where the first %d is nBits, and the second %d is nNums)
 *   then return without doing anything else.
 *
 * - Put the individual bits of each number into the "bits" array.
 *   The bits put into this array should be ordered so that the first
 *   32 bits represent nums[0], the next 32 bits are nums[1], and so
 *   on.  Within each number, the most significant bit (bit 31) should
 *   come first, and the least significant bit (bit 0) should come last.
 *   That is, bits[0] should be bit 31 of nums[0], bits[1] should
 *   be bit 30 of nums[0], and so on.
 */
void numToBits(uint32_t * nums, int nNums, int * bits, int nBits) {
  // check that there is enough space in bits to hold all the bits of nums
  // note that each number in nums will result in 32 bits in bits
  int totalBits = 32;
  int nBitsValid = checkBitsRequired(totalBits, nNums, nBits);
  
  // if this is not true, print a message with the format
  if(nBitsValid != 1) {
    printf("Invalid call to numToBits! nBits is %d, nNums is %d\n", nBits, nNums);
  }

  // put the individual bits of each number into the "bits" array.
  // order them so that the first 32 bits represent nums[0], next 32 are nums[1] and so on...
  // bitIndex: tracks which index number in bits we are working on loading
  int bitIndex = 0;
  // i tracks which num we are on, based on nNums
  for(int i = 0; i < nNums; i ++) {
    // bitCount: tracks which bit of the num (i) we are on, based on totalBits
    for(int bitCount = (totalBits - 1); bitCount >= 0; bitCount --) {
      // pull out the target num, and get its Nth bit based on bitCount
      uint32_t targetNum = nums[i]; 
      int bitValue = getNthBit(targetNum, bitCount);
      // set the next value in bits (using bitIndex) to the returned bitValue
      bits[bitIndex] = bitValue;
      bitIndex ++;
    }
  }
  
  // Within each number, the most significant bit (bit 31) should ocme first
  // and the least significant bit (bit 0) should come last.
  // bits[0] should be bit 31 of nums[0], bits[1] should be bit 30 of nums[0], and so on
  
}

void doTest(uint32_t * nums, int n) {
  int bits[n *32];
  numToBits(nums, n, bits, n*32);
  for (int i =0; i < n; i++) {
    printf(" %9d (%8X) => ", nums[i], nums[i]);
    for (int j = 0; j < 32; j++) {
      printf("%d", bits[i*32 + j]);
    }
    printf("\n");
  }
}

int main(void) {
  uint32_t array1[] = { 1, 2, 3, 4, 5, 15, 109};
  uint32_t array2[] = { 123456789, 987654321 };
  int bits[7*32-1];
  doTest (array1, 7);
  doTest (array2, 2);
  numToBits(array1,7, bits , 7*32-1);
  return EXIT_SUCCESS;
}
