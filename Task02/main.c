
#include <stdio.h>
#include <string.h>

#define MAX 100

// Date structure
typedef struct date
{
    int day;
    int month;
    int year;
} Date;

// Address structure
typedef struct address
{
    char city[20];
    int pincode;
} Address;

// Service type
typedef enum
{
    NORMAL,
    EXPRESS
} ServiceType;

// Parcel structure
typedef struct parcel
{
    int id;
    float weight;

    char senderName[30];
    Address from;

    char receiverName[30];
    Address to;

    Date booked;
    ServiceType service;
    float charge;

} Parcel;

// Function to print parcel details
void print_parcel(const Parcel *p)
{
    // TODO 1: Print using the arrow operator
    printf("%d %.1f kg %s-%d %02d/%02d/%04d\n",
           p->id,
           p->weight,
           p->to.city,
           p->to.pincode,
           p->booked.day,
           p->booked.month,
           p->booked.year);
}

// Selection sort by ascending weight
void sort_by_weight(Parcel p[], int n)
{
    int i, j, min;
    Parcel temp;

    // TODO 2: Find the lightest parcel and swap
    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
        {
            if (p[j].weight < p[min].weight)
            {
                min = j;
            }
        }

        if (min != i)
        {
            temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

// Function to list parcels for a given receiver city
void list_by_city(Parcel p[], int n, const char city[])
{
    int i;

    printf("\nParcels received in %s:\n", city);

    for (i = 0; i < n; i++)
    {
        if (strcmp(p[i].to.city, city) == 0)
        {
            print_parcel(&p[i]);
        }
    }
}

int main(void)
{
    Parcel list[3] =
    {
        {
            501, 4.5,
            "Arun", {"Chennai", 600077},
            "Priya", {"Madurai", 625001},
            {12, 10, 2026}, NORMAL, 150.0
        },

        {
            502, 1.2,
            "Rahul", {"Coimbatore", 641001},
            "Anu", {"Chennai", 600077},
            {12, 10, 2026}, EXPRESS, 200.0
        },

        {
            503, 2.8,
            "Kumar", {"Madurai", 625001},
            "Ravi", {"Coimbatore", 641001},
            {13, 10, 2026}, NORMAL, 120.0
        }
    };

    int n = 3;
    int i;

    // Sort parcels by weight
    sort_by_weight(list, n);

    printf("PARCELS SORTED BY WEIGHT\n\n");

    for (i = 0; i < n; i++)
    {
        print_parcel(&list[i]);
    }

    // Access receiver PIN using array and dot operator
    printf("\nReceiver PIN of third parcel: %d\n",
           list[2].to.pincode);

    // Access receiver PIN using pointer and arrow operator
    Parcel *p = &list[2];

    printf("Using pointer: %d\n", p->to.pincode);

    // Size of one parcel structure
    printf("\nSize of one parcel: %zu bytes\n",
           sizeof(struct parcel));

    // Optional city-wise listing
    // Uncomment the following line to test Chennai parcels.
    // list_by_city(list, n, "Chennai");

    return 0;
}
