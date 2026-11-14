
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Date
{
    int day;
    int month;
    int year;
};

struct BloodPressure
{
    int systolic;
    int diastolic;
};

struct Patient
{
    char name[20];
    int age;
    char phone[11];

    struct BloodPressure bp;
    struct Date visitDate;
};

// Function to add patient details using structure pointer
void addPatient(struct Patient *p, const char name[],
                int age, const char phone[],
                int systolic, int diastolic,
                struct Date date)
{
    snprintf(p->name, sizeof(p->name), "%s", name);
    p->age = age;

    snprintf(p->phone, sizeof(p->phone), "%s", phone);

    p->bp.systolic = systolic;
    p->bp.diastolic = diastolic;

    p->visitDate = date;
}

// Function to sort patients by age
void sortPatients(struct Patient p[], int n)
{
    int i, j;
    struct Patient temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].age > p[j + 1].age)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to display patient details
void displayPatients(struct Patient p[], int n)
{
    int i;

    printf("\nPATIENT HEALTH REGISTER\n");
    printf("------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("\nPatient Name : %s", p[i].name);
        printf("\nAge          : %d", p[i].age);
        printf("\nPhone        : %s", p[i].phone);

        printf("\nBlood Pressure : %d/%d",
               p[i].bp.systolic,
               p[i].bp.diastolic);

        printf("\nVisit Date   : %02d/%02d/%04d\n",
               p[i].visitDate.day,
               p[i].visitDate.month,
               p[i].visitDate.year);
    }
}

int main(void)
{
    struct Patient patients[MAX];
    int count = 0;

    struct Date d1 = {10, 11, 2026};
    struct Date d2 = {12, 11, 2026};
    struct Date d3 = {14, 11, 2026};

    // Adding patient records
    if (count < MAX)
        addPatient(&patients[count++], "Arun", 35,
                   "9876543210", 120, 80, d1);

    if (count < MAX)
        addPatient(&patients[count++], "Priya", 25,
                   "9876543211", 110, 70, d2);

    if (count < MAX)
        addPatient(&patients[count++], "Rahul", 45,
                   "9876543212", 130, 85, d3);

    printf("Before Sorting:");
    displayPatients(patients, count);

    // Sorting patients by age
    sortPatients(patients, count);

    printf("\n\nAfter Sorting by Age:");
    displayPatients(patients, count);

    return 0;
}
