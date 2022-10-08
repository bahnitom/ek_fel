#include <stdio.h>
#include <math.h>

// define borders
enum
{
  BORDER_LEFT = -999,
  BORDER_RIGHT = 999
};

/* The main program */
int main()
{
  int a, b, c;
  int dis = 0;
  float root_1, root_2, img_part, real_part;
  
  // load input
  scanf("%d %d %d", &a, &b, &c);

  // count discriminant
  dis = (b * b) - (4 * a * c);

  // check borders
  if (dis < BORDER_LEFT || dis > BORDER_RIGHT)
  {
    printf("Diskriminant mimo povoleny interval!\n");
    return 0;
  }
  // condition for real and different roots
  if (dis >= 0)
  {
    root_1 = (-b + sqrt(dis)) / (2 * a);
    root_2 = (-b - sqrt(dis)) / (2 * a);
    /* if (root_1 == root_2)
      count = 'Jeden';
    else
      count = 'Dva'; */
  }

  // condition for real and equal roots
  else if (dis == 0)
  {
    root_1 = root_2 = -b / (2 * a);
    printf("root_1 = root_2 = %.2lf;", root_1);
  }

  // if roots are not real
  else
  {
    real_part = -b / (2 * a);
    img_part = sqrt(-dis) / (2 * a);
    printf("root_1 = %.2lf+%.2lfi and root_2 = %.2f-%.2fi", real_part, img_part, real_part, img_part);
  }

  printf("+-----+-----+-----+-----+\n");
  printf("|%4d |%4d |%4d |%4d |\n", a, b, c, dis);
  printf("+-----+-----+-----+-----+\n");
  //printf("|%c %c|", count, type);
  printf("+-----------------------+\n");

  return 0;
}
