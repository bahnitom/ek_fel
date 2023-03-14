#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define NO_ERROR 0
#define ERROR_WRONG_INPUT 100
#define ERROR_HOUSE_DIM_OUT_OF_RANGE 101
#define ERROR_HOUSE_WITH_IS_NOT_ODD 102
#define ERROR_FENCE_WIDTH_INVALID 103
// std error outputs
#define CHYBNY_VSTUP "Error: Chybny vstup!\n"
#define VSTUP_MIMO_INTERVAL "Error: Vstup mimo interval!\n"
#define SIRKA_NENI_LICHE_CISLO "Error: Sirka neni liche cislo!\n"
#define NEPLATNA_VELIKOST_PLOTU "Error: Neplatna velikost plotu!\n"
const int house_dim_min = 3;
const int house_dim_max = 69;

enum
{
  HOUSE,
  ROOF,
  FENCE
};

int test_house_dim(int w, int h,int f_w, int switcher);
int test_fence_dim(int h, int f_w);

int print_roof(int w, int h);
int print_house(int w, int h, int f_w, int switcher);
int fill_house(int w, int h, int f_w, int i, int j);
int print_fence(int w, int h, int f_w, int i, int j);

int read_input(int *w, int *h, int *f_w, int *switcher);

int main(int argc, char *argv[])
{
  int ret = NO_ERROR;
  int w, h, f_w;
  int switcher = 0; // 0 = neutral, 1 = house, 2 = house + roof, 3 = house + roof + fence
  ret = read_input(&w, &h, &f_w, &switcher);
  switch (ret)
  {
  case ERROR_WRONG_INPUT:
    fprintf(stderr, CHYBNY_VSTUP);
    // prints if the input is not a number
    break;
  case ERROR_HOUSE_DIM_OUT_OF_RANGE:
    fprintf(stderr, VSTUP_MIMO_INTERVAL);
    // print if input is out of range
    break;
  case ERROR_HOUSE_WITH_IS_NOT_ODD:
    fprintf(stderr, SIRKA_NENI_LICHE_CISLO);
    // print if width is not odd number
    break;
  case ERROR_FENCE_WIDTH_INVALID:
    fprintf(stderr, NEPLATNA_VELIKOST_PLOTU);
    // print if fence width is not smaller then house width
    break;
    // end switch

  case HOUSE: // occurs if input has 1 numbers
    ret = print_house(w, h, f_w, switcher);
    break;
  case ROOF: // occurs if input has 2 numbers
    print_roof(w, h);
    ret = print_house(w, h, f_w, switcher);
    break;
  case FENCE: // occurs if input has 3 numbers
    print_roof(w, h);
    ret = print_house(w, h, f_w, switcher);
    break;
  // Just for sure
  default:
    printf("Default case");
    break;
  } // end switch
  return ret;
}

/*
 * Validate input before plotting anything
 */
int read_input(int *w, int *h, int *f_w, int *switcher)
{
  int ret = ERROR_WRONG_INPUT;
  int test_dims_code = NO_ERROR;
  int test_readed_val;
  /*WIDTH*/
  if (scanf("%d", w) == 1) // read width
  {
    *h = *w;
    *switcher = 1;
    test_dims_code = test_house_dim(*w, *h,*f_w, *switcher);
    if (test_dims_code != NO_ERROR)
    {
      return test_dims_code;
    }
    // width is OK
    ret = HOUSE;
  }
  /*HEIGHT*/
  test_readed_val = scanf("%d", h);                   // read height
  if (test_readed_val != 1 && test_readed_val != EOF) // check if value isn't another type than int && no end of file
  {
    ret = ERROR_WRONG_INPUT;
  }
  else if (test_readed_val == 1)
  {
    *switcher = 2;
    test_dims_code = test_house_dim(*w, *h,*f_w, *switcher);
    if (test_dims_code != NO_ERROR)
    {
      return test_dims_code;
    }
    // height is OK
    ret = ROOF;
  }
  /*FENCE*/
  test_readed_val = scanf("%d", f_w);                 // read fence
  if (test_readed_val != 1 && test_readed_val != EOF) // check if value isn't another type than int && no end of file
  {
    ret = ERROR_WRONG_INPUT;
  }
  else if (test_readed_val == 1)
  {
    *switcher = 3;
    test_dims_code = test_fence_dim(*h, *f_w);
    if (test_dims_code != NO_ERROR)
    {
      return test_dims_code;
    }
    // fence is OK
    ret = FENCE;
  }
  return ret;
}

/*
 * Only printing, no validity checks
 */
int print_roof(int w, int h)
{
  int roof_height = (w - 1) / 2; // height of roof
  for (int i = 0; i < roof_height; ++i)
  {
    for (int j = 0; j < roof_height + i + 1; ++j)
    {
      if ((j == roof_height + i) || ((j == roof_height - i)))
        printf("X");
      else
        printf(" ");
    }
    printf("\n");
  }
  return NO_ERROR;
}

/*
 * Only printing, no validity checks
 */
int print_house(int w, int h, int f_w, int switcher)
{
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      if ((i == 0) || (i == h - 1))
        printf("X");
      if (((j == 0) || (j == w - 1)) && (i >= 1) && (i < h - 1))
        printf("X");
      if ((w > 3) && w == h && switcher != 1)
        fill_house(w, h, f_w, i, j);
      else
      {
        if ((j < w - 2) && (i >= 1) && (i < h - 1))
          printf(" ");
      }
      if (switcher == 3 && (i > (h - f_w - 1)) && (j == w - 1))
      {
        print_fence(w, h, f_w, i, j);
      }
    }
    printf("\n");
  }
  return NO_ERROR;
}

/*
 * Only printing, no validity checks
 */
int fill_house(int w, int h, int f_w, int i, int j)
{
  if ((j < w - 2) && (i >= 1) && (i < h - 1))
  {
    if ((i % 2 != 0) && (j % 2 == 0))
      printf("o");
    else if ((i % 2 == 0) && ((j + 1) % 2 == 0))
      printf("o");
    else
      printf("*");
  }
  return NO_ERROR;
}

/*
 * Only printing, no validity checks
 */
int print_fence(int w, int h, int f_w, int i, int j)
{
  int max_fence = h - f_w;
  int min_fence = h - 1;
  int len_fence = w + f_w / 2 + 1;
  for (j = w + 1; j < (len_fence); ++j)
  {
    if ((i == max_fence) || (i == min_fence))
    {
      if ((f_w % 2 != 0) && (j == w + 1))
      {
        printf("|");
      }
      printf("-|");
    }
    else
    {
      if ((f_w % 2 != 0) && (j == w + 1))
      {
        printf("|");
      }
      printf(" |");
    }
  }
  return NO_ERROR;
}

// testing if input is in range
// testing if first input is odd number
int test_house_dim(int w, int h, int f_w, int switcher)
{
  int ret = NO_ERROR;
  bool dim_ok = ((house_dim_min <= w) && (w <= house_dim_max)) && 
                ((house_dim_min <= h) && (h <= house_dim_max));
  if (!dim_ok)
  {
    ret = ERROR_HOUSE_DIM_OUT_OF_RANGE;
    // test on invalid dimension goes before test of width
    return ret;
  }
  if (switcher != 1 && w % 2 == 0)
  {
    ret = ERROR_HOUSE_WITH_IS_NOT_ODD;
    return ret;
  }
  return ret;
}

// testing if third input is smaller than high of house
int test_fence_dim(int h, int f_w)
{
  int ret = NO_ERROR;
  bool fence_ok = ((house_dim_min <= f_w) && (f_w <= house_dim_max));
  if (!fence_ok)
  {
    ret = ERROR_HOUSE_DIM_OUT_OF_RANGE;
    return ret;
  }

  if (f_w > 0 && f_w < h)
    return NO_ERROR;
  else
    return ERROR_FENCE_WIDTH_INVALID;
}
