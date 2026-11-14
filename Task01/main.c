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
