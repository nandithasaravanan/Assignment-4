Task 2.1 – Identify the Entities (2 Marks)
The Courier Parcel Tracking system contains the following entities:

1. Parcel

Stores the main details of each parcel.
- Parcel ID
- Weight
- Sender details
- Receiver details
- Booking date
- Service type
- Charge
2. Address

Stores the address information of the sender and receiver.
- City
- PIN code
3. Date

Stores the booking date.
- Day
- Month
- Year
4. Sender and Receiver

Each person has:
- Name
- Address
Nested structure relationship
Parcel
Sender
- Name
- Address → City, PIN code

Receiver
- Name
- Address → City, PIN code

Booking Date
- Day
- Month
- Year

- Parcel ID
- Weight
- Service type
- Charge

An array of parcel structures stores all bookings made during the day.
Task 2.2 – Define the Structures (2 Marks)
The following structures are used:

Date structure: Stores day, month and year.

Address structure: Stores city and PIN code.

Parcel structure: Stores parcel details and includes nested address and date structures.

The typedef keyword provides shorter names for structure types.
Task 2.3 – Design the Operations (3 Marks)
A. Sorting parcels by weight
Algorithm: Selection Sort

Pseudocode:
START

FOR i = 0 TO n-2
    min = i

    FOR j = i+1 TO n-1
        IF parcel[j].weight < parcel[min].weight
            min = j
        END IF
    END FOR

    IF min != i
        SWAP parcel[i] AND parcel[min]
    END IF
END FOR

STOP


Explanation:
- Find the parcel with the smallest weight.
- Swap it with the current position.
- Repeat until all parcels are sorted in ascending order.
B. Listing parcels for a given receiver city
Pseudocode:
START

INPUT city

FOR i = 0 TO n-1
    IF parcel[i].to.city == city
        DISPLAY parcel details
    END IF
END FOR

STOP


Explanation:

The program checks the receiver's city for every parcel. If the city matches the requested city, the parcel details are displayed.
Task 2.4 – Access Paths (1 Mark)
The receiver's PIN code of the third parcel can be accessed in two ways.

1. Using array and dot operator:
list[2].to.pincode


2. Using structure pointer and arrow operator:
p->to.pincode


Here, p points to the third parcel.
Alternative Concept and Complexity Analysis
1. Nested structure vs flat structure
Nested structure	Flat structure
Address and date are separate structures.	All fields are directly inside Parcel.
Easier to reuse Address.	Less nesting in access expressions.
Better organization.	Simpler for small fixed records.
Uses nested access operators.	Uses direct field access.

2. Access path comparison
Nested structure:
list[0].to.pincode
list[0].booked.day


Flat structure:
list[0].receiverPincode
list[0].bookingDay


3. Memory analysis
The memory occupied by a parcel is obtained using:
sizeof(struct parcel)


The total memory for an array of n parcels is:
\[
\text{Memory}=n\times sizeof(struct\ parcel)
\]

The compiler may insert padding bytes for memory alignment.
4. Time complexity
Operation	Time complexity
Sorting using selection sort	O(n²)
Finding parcels by city	O(n)
Printing one parcel	O(1)
Accessing a nested field	O(1)

5. Conclusion
Nested structures provide better organization and reusability. They allow sender, receiver, address and date information to be maintained systematically. This design makes the courier tracking system easier to modify and maintain.

SECTION 2 – Correct C Code
File name: main.c

The following program:
- Uses nested structures.
- Uses typedef for simpler declarations.
- Implements TODO 1 using the arrow operator.
- Implements TODO 2 using selection sort.
- Includes a function to list parcels by receiver city.
- Swaps complete parcel structures.
