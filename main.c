#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int text(char text1[], int delka);
int main(void)
{
    int delka;
    char tmp = '\0';
    int return_val = 0;
    if (scanf("%d", &delka) != 1)
    {
        fprintf(stderr, "Error: Chybny vstup!");
        return 100;
    }
    char radek1[delka];
    //char radek2[delka]; /*tuto promennou nepotrebujeme*/

    // nastavi nacteny radek do promenne return_val
    return_val = text(radek1, delka); 
    
    if (return_val == 100)
    {
        return return_val;
    }
    else if (return_val == 101)
    {
        return return_val;
    }
    // kontroluje delku vstupu
    scanf("%c", &tmp);
    if (tmp != 10)
    {

        return 100;
    }
    return 0;
}

// nacitani znaku do pole
int text(char text1[], int delka)
{
    char vstupni_char = 0;
    for (int i = 0; i < delka; i++)
    {
        scanf("%c", &vstupni_char);
        if (vstupni_char == 10 && i < delka - 1)
        {
            fprintf(stderr, "Error: Chybna delka vstupu!");
            return 101;
        }
        if ((vstupni_char >= 'A' && vstupni_char <= 'Z') || (vstupni_char >= 'a' && vstupni_char <= 'z'))
        {
            text1[i] = vstupni_char;
        }
        else
        {
            fprintf(stderr, "Error: Chybny vstup!");
            return 100;
        }
    }
    return *text1; /*funkce vraci nacteny 1 radek*/
}
