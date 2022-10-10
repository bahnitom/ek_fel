#include <stdio.h>
#include <math.h>

// define borders and root characteristics
enum
{
  BORDER_LEFT = -999,
  BORDER_RIGHT = 999,
  ROOT_1 = 1,
  ROOT_2 = 2,
  ROOT_IMG = 3
};

int main()
{
  int a, b, c;
  int dis = 0;
  int root = 0;

  // load input
  scanf("%d %d %d", &a, &b, &c);

  // root discriminant
  dis = (b * b) - (4 * a * c);

  // check borders
  if (dis < BORDER_LEFT || dis > BORDER_RIGHT)
  {
    printf("Diskriminant mimo povoleny interval!\n");
    return 0;
  }
  // discriminant assort
  if (dis > 0)       /*condition for real and different roots*/
    root = 2;
  else if (dis == 0) /*condition for real and equal roots*/
    root = 1;
  else               /*if roots are not real*/ 
    root = 3;

  printf("+-----+-----+-----+-----+\n");
  printf("|%4d |%4d |%4d |%4d |\n", a, b, c, dis);
  printf("+-----+-----+-----+-----+\n");
  if (root == 1)
    printf("|           Jeden koren |\n");
  else if (root == 2)
    printf("|     Dva realne koreny |\n");
  else
    printf("| Dva imaginarni koreny |\n");
  printf("+-----------------------+\n");
  return 0;
}
