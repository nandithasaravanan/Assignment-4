
#include <stdio.h>

// Structure declaration
struct account
{
    int number;
    float balance;
};

// Original function: Pass by value
void addInterestByValue(struct account a, float rate)
{
    printf("Address inside pass-by-value function: %p\n",
           (void *)&a);

    a.balance = a.balance + a.balance * rate / 100;

    printf("Local balance: %.2f\n", a.balance);
}

// Corrected function: Pass by pointer
void addInterest(struct account *a, float rate)
{
    printf("Address inside pointer function: %p\n",
           (void *)a);

    a->balance = a->balance + a->balance * rate / 100;
}

int main(void)
{
    struct account list[3] =
    {
        {101, 5000},
        {102, 12000},
        {103, 800}
    };

    struct account *p = list;

    printf("STRUCTURE FORENSICS\n\n");

    // Demonstrate pass by value
    printf("PASS BY VALUE:\n");

    printf("Original address: %p\n", (void *)&list[0]);

    addInterestByValue(list[0], 4);

    printf("Original balance after function: %.2f\n\n",
           list[0].balance);

    // Corrected pointer-based method
    printf("PASS BY POINTER:\n");

    for (int i = 0; i < 3; i++)
    {
        printf("\nAccount: %d\n", p[i].number);

        printf("Address in main: %p\n", (void *)&p[i]);

        addInterest(&p[i], 4);

        printf("Updated balance: %.2f\n", p[i].balance);
    }

    // Display final account details
    printf("\nFINAL ACCOUNT DETAILS\n");

    for (int i = 0; i < 3; i++)
    {
        printf("%d %.2f\n", p[i].number, p[i].balance);
    }

    printf("\nSize of structure: %zu bytes\n",
           sizeof(struct account));

    return 0;
}
