Task 4.1 – Locate the Defects (2 Marks)
The given program contains two major defects.

Defect 1: Passing structure by value
void addInterest(struct account a, float rate)


- The structure is passed by value.
- A copy of the original structure is created.
- Changes made to a.balance affect only the local copy.
- Therefore, the original account balance remains unchanged.
Defect 2: Incorrect pointer member access
printf("%d %f\n", p.number, p.balance);


Here, p is a structure pointer.

The dot operator (.) is used for structure variables, not structure pointers.

Correct syntax:
printf("%d %.2f\n", p->number, p->balance);


The arrow operator (->) accesses structure members through a pointer.
Task 4.2 – Construct Evidence (2 Marks)
To prove the first defect, print the addresses of the structure.
- &a inside the pass-by-value function gives the address of the local copy.
- &list[i] inside main() gives the address of the original structure.
These addresses will be different.

After changing the function to accept a structure pointer, both addresses will be the same.

This proves that the pointer refers to the original structure.
Task 4.3 – Repair the Program (2 Marks)
Use a structure pointer and the arrow operator.

Correct function:
void addInterest(struct account *a, float rate)
{
    a->balance = a->balance +
                 a->balance * rate / 100;
}


Function call:
addInterest(&list[i], 4);


The address operator (&) passes the address of the original structure.

The arrow operator (->) modifies its balance directly.
Task 4.4 – Prevent Recurrence (1 Mark)
When should structures be passed by value?
- When the structure is small.
- When the original data should not be modified.
- When an independent copy is required.
When should structures be passed by pointer?
- When the function needs to modify the original structure.
- When copying large structures would be inefficient.
- When multiple functions need access to the same structure.
When should const pointers be used?
Use a constant pointer to a constant structure:
void display(const struct account *a)


This allows the function to access the structure without modifying its members.
Alternative Concept and Complexity Analysis
1. Passing by value vs passing by pointer
Feature	Pass by value	Pass by pointer
Data passed	Complete structure	Structure address
Original modified	No	Yes
Copying	Structure copy	No structure copy
Memory overhead	Higher	Lower
Suitable for	Small structures	Large structures

2. Time complexity
Let \(n\) represent the number of accounts.
- Pass by value: \(O(n)\)
- Pass by pointer: \(O(n)\)
Both approaches require one operation per account.

However, passing by value copies the structure, whereas passing by pointer passes only its address.
3. Memory calculation
For the given structure:
struct account
{
    int number;
    float balance;
};


On a typical system:
- Integer = 4 bytes
- Float = 4 bytes
- Structure = 8 bytes
For each function call:
- Pass by value: approximately 8 bytes for the argument copy and another 8 bytes if a modified structure is returned.
- Pass by pointer: 8 bytes for the pointer on a typical 64-bit system.
Actual stack usage depends on the compiler and optimization.

Conclusion: Passing a structure by pointer is more efficient when modifying existing records because it avoids unnecessary structure copying.
