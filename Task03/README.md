Task 3.1 – Structure or Union? (3 Marks)
The weather station sends three types of sensor values:
1. Temperature – float
2. Humidity – int
3. Status – char[8]
A. Structure design
A structure stores all three members simultaneously.
struct packet
{
    float celsius;
    int percent;
    char status[8];
};


Disadvantage:
- All three members occupy memory even though only one value is required.
- This wastes memory when thousands of packets are stored.
B. Tagged union design
A tagged union stores only one value at a time. An enum identifies which member is currently valid.
enum kind
{
    TEMPERATURE,
    HUMIDITY,
    STATUS
};

struct reading
{
    enum kind type;

    union
    {
        float celsius;
        int percent;
        char status[8];
    } value;
};


Advantages:
- Saves memory.
- Stores only one sensor value at a time.
- The type tag identifies the valid member.
- Suitable for memory-limited weather stations.
Conclusion: The tagged union is better because the weather station stores exactly one kind of value per packet.
Task 3.2 – Predict the Size (2 Marks)
For a typical 64-bit GCC system:
A. Union size
Member	Size
float celsius	4 bytes
int percent	4 bytes
char status[8]	8 bytes

The union size is determined by its largest member.
\[
sizeof(union)=8\ bytes
\]

B. Structure size
Member	Size
enum kind type	4 bytes
Union value	8 bytes
Total	12 bytes

\[
sizeof(struct\ reading)=4+8=12\ bytes
\]

The union requires 4-byte alignment. The structure size is already a multiple of 4, so no additional trailing padding is required.
C. Why not 4 + 4 + 4 + 8?
A union shares the same memory location among all its members. Therefore, its members are not added together.

Only the largest member determines the union's storage requirement, subject to alignment.
Task 3.3 – Implement and Test (3 Marks)
The program uses a switch statement to identify the active union member.
- TEMPERATURE: Prints temperature.
- HUMIDITY: Prints humidity.
- STATUS: Prints status text.
The show() function uses the type tag to access only the valid union member.
Task 3.4 – Misuse Experiment (1 Mark)
If temperature is stored and the humidity member is read afterward, the program interprets the same memory using a different data type.

For example:
- Stored temperature: 31.5
- Read as integer: 1107034112 on a typical IEEE-754 system with 32-bit integers.
This is not the actual humidity value.

Explanation: A union shares memory between its members. Reading an inactive member reinterprets the stored representation and can produce an unexpected or implementation-dependent result. Therefore, the type tag must always be checked before accessing a member.
Alternative Concept and Complexity Analysis
1. Tagged union vs separate arrays
Tagged union	Separate arrays
Stores different packet types in one array.	Stores each packet type separately.
Uses one union per packet.	Uses separate storage for each type.
Easy to maintain a common packet log.	Efficient when processing one type repeatedly.
Requires checking the type tag.	Requires tracking the corresponding array.

2. Tagged union vs void pointer with malloc
Feature	Tagged union	Dynamic allocation
Memory allocation	Fixed-size	Dynamic
Access time	O(1)	O(1) after dereferencing
Memory overhead	Type tag and union	Pointer, allocator metadata and allocated storage
Memory management	Simple	Requires malloc and free
Safety	Tag identifies valid member	Requires correct type tracking

3. Time complexity
Operation	Complexity
Create a packet	O(1)
Read a packet	O(1)
Identify packet type	O(1)
Print a packet	O(1)

4. Conclusion
Tagged unions are suitable for memory-constrained systems because they allow multiple data types to share memory. The type tag ensures that the correct member is accessed, reducing memory wastage and improving storage efficiency.
