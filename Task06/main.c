
#include <stdio.h>

// Nested structures
struct Date
{
    int day, month, year;
};

struct Time
{
    int hour, minute;
};

// Item types
enum ItemType
{
    PACKAGED,
    COOKED,
    COMBO
};

// Main item structure
struct Item
{
    int id;
    char name[30];
    float price;
    int stock;
    float revenue;

    enum ItemType type;

    union
    {
        struct Date expiry;
        struct Time prepared;

        struct
        {
            int count;
            int ids[3];
        } combo;

    } details;
};

// Function declarations
int findItem(const struct Item inventory[], int count, int id);

int recordSale(struct Item inventory[], int count,
               int id, int quantity);

void checkExpiry(const struct Item inventory[],
                 int count, struct Date today);

void sortByRevenue(struct Item inventory[], int count);

void printSummary(const struct Item inventory[], int count);

// Check leap year
int isLeapYear(int year)
{
    if (year % 400 == 0)
        return 1;

    if (year % 100 == 0)
        return 0;

    return year % 4 == 0;
}

// Convert date into number of days
int dateToDays(struct Date d)
{
    int days = 0;
    int monthDays[] =
    {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    for (int y = 1; y < d.year; y++)
    {
        days += isLeapYear(y) ? 366 : 365;
    }

    for (int m = 1; m < d.month; m++)
    {
        days += monthDays[m - 1];

        if (m == 2 && isLeapYear(d.year))
            days++;
    }

    days += d.day;

    return days;
}

// Find item using ID
int findItem(const struct Item inventory[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (inventory[i].id == id)
            return i;
    }

    return -1;
}

// Record a sale
int recordSale(struct Item inventory[], int count,
               int id, int quantity)
{
    int index = findItem(inventory, count, id);

    if (index == -1 || quantity <= 0)
    {
        printf("Invalid item or quantity!\n");
        return 0;
    }

    struct Item *item = &inventory[index];

    // Check combo component stock
    if (item->type == COMBO)
    {
        for (int i = 0; i < item->details.combo.count; i++)
        {
            int componentIndex = findItem(
                inventory,
                count,
                item->details.combo.ids[i]
            );

            if (componentIndex == -1 ||
                inventory[componentIndex].type == COMBO ||
                inventory[componentIndex].stock < quantity)
            {
                printf("Insufficient component stock for %s!\n",
                       item->name);
                return 0;
            }
        }

        // Deduct component stock after validation
        for (int i = 0; i < item->details.combo.count; i++)
        {
            int componentIndex = findItem(
                inventory,
                count,
                item->details.combo.ids[i]
            );

            inventory[componentIndex].stock -= quantity;
        }
    }
    else
    {
        if (item->stock < quantity)
        {
            printf("Insufficient stock for %s!\n",
                   item->name);
            return 0;
        }

        item->stock -= quantity;
    }

    // Calculate and update revenue
    float amount = item->price * quantity;

    item->revenue += amount;

    printf("Sale successful: %s, Amount = Rs. %.2f\n",
           item->name, amount);

    return 1;
}

// Check expiry warnings
void checkExpiry(const struct Item inventory[],
                 int count, struct Date today)
{
    printf("\nEXPIRY WARNINGS\n");

    int todayDays = dateToDays(today);

    for (int i = 0; i < count; i++)
    {
        if (inventory[i].type == PACKAGED)
        {
            int expiryDays =
                dateToDays(inventory[i].details.expiry);

            int remaining = expiryDays - todayDays;

            if (remaining >= 0 && remaining <= 2)
            {
                printf("WARNING: %s expires in %d day(s)\n",
                       inventory[i].name, remaining);
            }
        }
    }
}

// Sort inventory by revenue in descending order
void sortByRevenue(struct Item inventory[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int max = i;

        for (int j = i + 1; j < count; j++)
        {
            if (inventory[j].revenue > inventory[max].revenue)
            {
                max = j;
            }
        }

        if (max != i)
        {
            struct Item temp = inventory[i];
            inventory[i] = inventory[max];
            inventory[max] = temp;
        }
    }
}

// Print daily bill summary
void printSummary(const struct Item inventory[], int count)
{
    float total = 0;

    printf("\nDAILY BILL SUMMARY\n");

    printf("\n%-15s %-12s %-12s\n",
           "Item", "Stock", "Revenue");

    for (int i = 0; i < count; i++)
    {
        printf("%-15s %-12d Rs. %.2f\n",
               inventory[i].name,
               inventory[i].stock,
               inventory[i].revenue);

        total += inventory[i].revenue;
    }

    printf("\nTotal Revenue = Rs. %.2f\n", total);
}

int main(void)
{
    // Current date
    struct Date today = {15, 11, 2026};

    // Inventory records
    struct Item inventory[4] =
    {
        {
            101, "Juice", 30.0f, 10, 0.0f,
            PACKAGED,
            {.expiry = {16, 11, 2026}}
        },

        {
            102, "Sandwich", 50.0f, 8, 0.0f,
            COOKED,
            {.prepared = {9, 30}}
        },

        {
            103, "Chips", 20.0f, 15, 0.0f,
            PACKAGED,
            {.expiry = {25, 11, 2026}}
        },

        {
            201, "Combo Meal", 70.0f, 0, 0.0f,
            COMBO,
            {.combo = {2, {101, 102}}}
        }
    };

    int count = 4;

    printf("COLLEGE CANTEEN INVENTORY SYSTEM\n");

    // Check expiry dates
    checkExpiry(inventory, count, today);

    // Normal sales
    printf("\nRECORDING SALES\n");

    recordSale(inventory, count, 101, 2);

    recordSale(inventory, count, 102, 1);

    // Combo sale
    recordSale(inventory, count, 201, 2);

    // Test insufficient stock
    recordSale(inventory, count, 103, 20);

    // Sort according to revenue
    sortByRevenue(inventory, count);

    // Print final summary
    printSummary(inventory, count);

    return 0;
}
