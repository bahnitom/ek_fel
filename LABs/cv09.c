#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*char text[] = "Everybody likes PRPA";
    text[25] = '?';
    printf("\"%s\", %lu, %lu\n", text, sizeof(text), strlen(text));
    //strlen(text); // nacita do '\0'
    //strnlen(text, 16); // nacita do '\0' nebo do maximalniho prvku
*/

#define TEXLEN (32u)

int main(void)
{
    char *text;
    text = malloc(TEXLEN);
    if (text == NULL)
    {
        fprintf(stderr, "ERROR MALLOC\n");
        return 1;
    }
    unsigned int len = TEXLEN, loaded = 0;
    while (scanf("%c", &text[loaded]) == 1) // nacita pokud je na vztupu znak a ukladada ho na pozici loaded
    {
        loaded++;
        if (loaded >= len)
        {
            char *tmp;
            tmp = realloc(text, 2 * len);
            if (text == NULL)
            {
                fprintf(stderr, "ERROR REALLOC\n");
                free(text);
                return 2;
            }
            text = tmp;
            len = len * 2;
        }
    }
    if (loaded < len)
    {
        text[loaded] = 0;
    }
    else
    {
        text[len - 1] = 0;
    }

    /* " " ---> "\n" */
    /* projit pole a nahradit mezery novym radkem */
    /* substring - slova oddelena mezerou */

    /*char *token;
    token = strtok(text, "\n\t"); // rozdeluje stringy podle ukazatelu | pokud se nepovede, tak vraci nulu (NULL)
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, "\n\t");
    }
    */

    // substring strstr(), najdeme index mezeri pmoci strchr()

    char *token, *cursor, znak;
    int len_str;
    cursor = text;
    printf("\n");
    while ((token = strchr(cursor, ' ')) != NULL)
    {
        znak = *token;
        *token = 0;
        len_str = strlen(cursor);
        for (int i = 0; i < len_str; ++i)
        {
            /*POZNAMKA - musite se ujistit jestli se jedna o pismeno [A-Z a-z] */
            cursor[i] = cursor[i] ^ 0x20;
        }
        printf("%s %d", cursor, len_str);

        /*string compare*/
        if (strncmp(cursor, "AND", 3) == 0) /*stringy jsou si rovne*/
        {
            printf(" <--");
        }
        printf("\n");

        *token = znak;
        cursor = token + 1;
        if (cursor >= text + loaded)
        {
            break;
        }
    }

    free(text);
    return 0;
}
/*DU 2.priklad z webu cv09*/
