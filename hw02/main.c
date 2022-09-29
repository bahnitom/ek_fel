#include <stdio.h>
#include <stdlib.h>

enum { BORDER_LEFT = -10000, BORDER_RIGHT = 10000 };

/* The main program */
int main(int argc, char *argv[]) {
  int x, y;
  // load input
  scanf("%d %d", &x, &y);
  float avg = (x + y) / 2.0;

  // check borders
  if (x < BORDER_LEFT || x > BORDER_RIGHT) {
    printf("Vstup je mimo interval!\n");
    return 0;
  }
  if (y < BORDER_LEFT || y > BORDER_RIGHT) {
    printf("Vstup je mimo interval!\n");
    return 0;
  }
  // printing rows
  printf("Desitkova soustava: %d %d\n", x, y);
  printf("Sesnactkova soustava: %x %x\n", x, y);
  printf("Soucet: %d + %d = %d\n", x, y, x + y);
  printf("Rozdil: %d - %d = %d\n", x, y, x - y);
  printf("Soucin: %d * %d = %d\n", x, y, x * y);
  if (y == 0) {
    printf("Nedefinovany vysledek!\n");
  } else
    printf("Podil: %d / %d = %d\n", x, y, x / y);
  printf("Prumer: %.1f\n", avg);
  return 0;
}
