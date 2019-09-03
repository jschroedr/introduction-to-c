#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min (int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max (int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
struct rectangle_t {
  int x;
  int y;
  int width;
  int height;

};
typedef struct rectangle_t rectangle;

rectangle canonicalize(rectangle r) {
  if(r.width < 0){
    r.x = r.x + r.width;
    r.width = r.width - (r.width * 2);
  }
  if(r.height < 0){
    r.y = r.y + r.height;
    r.height = r.height - (r.height * 2);
  }
  return r;
}

int checkForIntersection(rectangle r1, rectangle r2){
  int check;
  int hCheck = 0;
  int vCheck = 0;

  int minR = min((r1.x + r1.width), (r2.x + r2.width));
  int maxL = max(r1.x, r2.x);
  if((minR - maxL) <= 0){
    hCheck = 1;  // FAIL
  }
  int minT = min((r1.y + r1.height), (r2.y + r2.height));
  int maxB = max(r1.y, r2.y);
  if((minT - maxB) <= 0){
    vCheck = 1;
  }

  if(!hCheck && !vCheck){
    check = 0;
  } else if(!hCheck && vCheck){
    check = 2;  // share horizontal edge
  } else if(hCheck && !vCheck){
    check = 3;  // share vertical edge
  } else {
    check = 1;  // no overlap
  }
  return check;
}

rectangle intersection(rectangle r1, rectangle r2) {
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);

  int interCheck = checkForIntersection(r1, r2);
  rectangle inter;
  inter.x = max(r1.x, r2.x);
  inter.y = max(r1.y, r2.y);
  if(interCheck == 0){
    inter.width = min(r1.width, r2.width);
    inter.height = min(r1.height, r2.height);
  } else if(interCheck == 1){
    inter.width = 0;  // no such rectangle
    inter.height = 0;
  } else if(interCheck == 2){
    inter.width = min(r1.width, r2.width);
    inter.height = 0;  // no v overlap
  } else {
    // interCheck == 3
    inter.width = 0;
    inter.height = min(r1.height, r2.height);
  }
  return inter;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, 
	                           r.x + r.width, r.y + r.height);
  }
}

int main (void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);
  
  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);
  
  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);
  
  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);
  
  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);
  
  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);


  return EXIT_SUCCESS;

}
