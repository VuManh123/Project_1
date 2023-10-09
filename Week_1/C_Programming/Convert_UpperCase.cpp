#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char s[1000];
    while (fgets(s, sizeof(s), stdin) != NULL)
    {
        for (int i = 0; i < strlen(s); i++)
        {
            if (islower(s[i]))
                s[i] = toupper(s[i]);
            printf("%c", s[i]);
        }
    }
    return 0;
}
