Stage 1 – Interpret the Problem (2 Marks)
1. Identify the entities
The canteen system contains three main types of items.
Entity	Description	Data required
Packaged item	Items with expiry dates	Name, price, stock, expiry date
Cooked item	Food prepared in the canteen	Name, price, stock, preparation time
Combo meal	Combination of up to three items	Name, price, component item IDs

2. Identify the data and rules
Data required:
1. Item ID
2. Item name
3. Item price
4. Available stock
5. Item type
6. Expiry date or preparation time or combo components
7. Quantity sold
8. Revenue generated
Rules:
- Packaged items must have a valid expiry date.
- Cooked items must store their preparation time.
- Combo meals can contain a maximum of three items.
- Stock must never become negative.
- A sale must be rejected if sufficient stock is unavailable.
- Items expiring within two days must generate a warning.
- The daily bill summary must be sorted by revenue in descending order.
3. Testable requirements
Requirement	Expected result
Normal sale	Stock decreases
Sale exceeds stock	Sale rejected
Combo sale	Component stocks decrease
Expiry within two days	Warning displayed
Revenue calculation	Quantity × price
Daily summary	Highest revenue appears first

Stage 2 – Propose the Data Model (2 Marks)
We use an array of structures to store the canteen inventory.
1. Nested structures
Date structure

Stores the expiry date of packaged items.
struct Date
{
    int day;
    int month;
    int year;
};


Preparation time structure

Stores the preparation time of cooked items.
struct Time
{
    int hour;
    int minute;
};


2. Tagged union
A tagged union stores only the information relevant to the item's type.
enum ItemType
{
    PACKAGED,
    COOKED,
    COMBO
};


The union contains:
- Expiry date for packaged items.
- Preparation time for cooked items.
- Component IDs for combo meals.
3. Array of structures
struct Item inventory[100];


This stores a maximum of 100 canteen items.

Each array element represents one complete inventory record.
Stage 3 – Identify the Critical Design Decisions (2 Marks)
1. Safe stock updates
Before recording a sale:
1. Check whether the item exists.
2. Check whether sufficient stock is available.
3. For combo meals, check the stock of every component.
4. Deduct stock only after all checks pass.
5. Update the revenue.
This prevents negative stock and partial transactions.
2. Expiry checking
Use a nested date structure.
struct Date expiry;


Compare the expiry date with the current date.

If the difference is between zero and two days, display an expiry warning.
3. Static and global variables
- Inventory should remain available throughout the canteen program.
- Daily revenue must be maintained while sales are recorded.
- These can be stored in main() and passed to functions using pointers.
- Global variables are not necessary for this design.
- Static variables are unnecessary unless a function must retain its own state between calls.
4. Revenue sorting
Use selection sort to arrange inventory records according to their revenue in descending order.
Stage 4 – Design the Structures and Functions (4 Marks)
1. Structure definitions
struct Date
{
    int day, month, year;
};

struct Time
{
    int hour, minute;
};

enum ItemType
{
    PACKAGED,
    COOKED,
    COMBO
};


Main item structure:
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


2. Function prototypes
void displayItem(const struct Item *item);

int recordSale(
    struct Item inventory[],
    int count,
    int id,
    int quantity
);

void checkExpiry(
    const struct Item inventory[],
    int count,
    struct Date today
);

void sortByRevenue(
    struct Item inventory[],
    int count
);

void printSummary(
    const struct Item inventory[],
    int count
);


These functions use structure pointers or array parameters to access inventory records without unnecessary copying.
3. Pseudocode – Recording a sale
START

Read item ID and quantity

Search for the item

IF item does not exist
    Display "Item not found"
ELSE
    IF item is a combo
        Check stock of all components
    ELSE
        Check available stock
    END IF

    IF stock is sufficient
        Deduct the required stock
        Calculate revenue
        Update item revenue
        Display sale successful
    ELSE
        Display insufficient stock
    END IF
END IF

STOP


4. Pseudocode – Expiry warning
START

FOR each item in inventory

    IF item type is PACKAGED

        Calculate days remaining until expiry

        IF days remaining is between 0 and 2
            Display expiry warning
        END IF

    END IF

END FOR

STOP


5. Pseudocode – Revenue sorting
START

FOR i = 0 to n-2

    Find item with highest revenue

    IF highest revenue is greater than current revenue
        Swap the complete structures
    END IF

END FOR

STOP


Alternative Concept and Complexity Analysis
Array of structures vs linked list
Operation	Array of structures	Linked list
Add item	O(n) if shifting or finding a position	O(1) at head
Remove item	O(n)	O(1) if node is already located
Search item	O(n)	O(n)
Access by index	O(1)	O(n)
Memory	Contiguous allocation	Separate nodes and pointers

Extra memory in linked lists:

Each node requires an additional pointer to connect it to the next node.
Advantages of linked lists
- Dynamic memory allocation.
- Easy insertion and deletion.
- No fixed array capacity.
Advantages of arrays
- Faster indexed access.
- Better memory locality.
- No additional pointer storage.
- Easier to sort using array-based algorithms.
Conclusion: An array of structures is suitable for a small college canteen because the inventory is relatively limited and frequent indexed access is useful. A linked list is preferable when inventory size changes frequently.
