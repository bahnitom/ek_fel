#include <stdio.h>

#define CNUM_SIZE (16u)

// structure
typedef struct Complex_t
{
    double re, im;
    double abs; // vector lenght
    double phi; // vector angle
} Complex_t, *pComplex_t;

/* typedef <jakytyp> <alias> */
typedef int cislo;
typedef unsigned char bool;
typedef unsigned char bul;
typedef char chachar;

// functions
void complex_add(double *out, double *c0, double *c1);
void complex_add_struct(Complex_t *out, pComplex_t c0, pComplex_t c1);

int main(void)
{
    double real[CNUM_SIZE];
    double im[CNUM_SIZE];

    /* [0][x] realne slozky */
    /* [1][x] imaginarni slozky */

    double complexnums[2][CNUM_SIZE]; /* zbytecny */
    // double complexnums[CNUM_SIZE][2]; /* better, typ easy*/

    /* c_2 = c_0 + c_1 */
    complexnums[0][0] = 3;
    complexnums[0][1] = -1;
    complexnums[1][0] = 4;
    complexnums[1][1] = 6;
    complex_add(&complexnums[0][2], &complexnums[0][0], &complexnums[0][1]);

    printf("%f +i%f + %f +i%f = %f +i%f\n",
           complexnums[0][0], complexnums[1][0],
           complexnums[0][1], complexnums[1][1],
           complexnums[0][2], complexnums[1][2]);

    struct Complex_t c0;
    Complex_t c1, c2;
    Complex_t complexstructs[CNUM_SIZE];
    c0.re = 3;
    c0.im = 4;
    c1.re = -1;
    c1.im = 6;
    complex_add_struct(&c2, &c1, &c0);
    printf("-----------------------------------------------------------------\n");
    printf("%f +i%f + %f +i%f = %f +i%f\n",
           c0.re, c0.im, c1.re, c1.im, c2.re, c2.im);
    return 0;
}

void complex_add(double *out, double *c0, double *c1)
{
    out[0] = c0[0] + c1[0];
    out[CNUM_SIZE] = c0[CNUM_SIZE] + c1[CNUM_SIZE];
}

void complex_add_struct(Complex_t *out, pComplex_t c0, pComplex_t c1)
{
    out->re = c0->re + c1->re;
    (*out).im = (*c0).im + c1->im;
}
