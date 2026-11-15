
#include <stdio.h>

// Access global variable from another file
extern int global_counter;

int next_global_token(void);

// Static local variable
int next_token(void)
{
    static int token = 1000;
    return ++token;
}

// Automatic local variable
int auto_token(void)
{
    int token = 1000;
    return ++token;
}

// Pointer-based independent counter
int next_token_for(int *counter)
{
    return ++(*counter);
}

int main(void)
{
    int s[3], a[3], g[3];

    // Static counter
    for (int i = 0; i < 3; i++)
    {
        s[i] = next_token();
    }

    // Automatic counter
    for (int i = 0; i < 3; i++)
    {
        a[i] = auto_token();
    }

    // Global counter
    for (int i = 0; i < 3; i++)
    {
        g[i] = next_global_token();
    }

    printf("STORAGE CLASS COMPARISON\n\n");

    printf("Static : ");
    for (register int i = 0; i < 3; i++)
    {
        printf("%d ", s[i]);
    }

    printf("\nAuto   : ");
    for (register int i = 0; i < 3; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\nGlobal : ");
    for (register int i = 0; i < 3; i++)
    {
        printf("%d ", g[i]);
    }

    printf("\n");

    // Two independent counters
    int veg = 1000;
    int nonveg = 1000;

    int v[3], nv[3];

    for (register int i = 0; i < 3; i++)
    {
        v[i] = next_token_for(&veg);
        nv[i] = next_token_for(&nonveg);
    }

    printf("\nTWO INDEPENDENT COUNTERS\n");

    printf("Veg    : ");
    for (register int i = 0; i < 3; i++)
    {
        printf("%d ", v[i]);
    }

    printf("\nNonveg : ");
    for (register int i = 0; i < 3; i++)
    {
        printf("%d ", nv[i]);
    }

    printf("\n\nGlobal counter final value: %d\n",
           global_counter);

    printf("\nRegister loop variable demonstration: ");

    for (register int i = 1; i <= 3; i++)
    {
        printf("%d ", i);
    }

    printf("\n");

    return 0;
}

