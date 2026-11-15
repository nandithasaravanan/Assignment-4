Task 5.1 – Four Implementations (3 Marks)
1. Automatic local variable
An automatic variable is created whenever a function is called and destroyed when the function returns.
int auto_token(void)
{
    int token = 1000;
    return ++token;
}


Output:
1001 1001 1001


Explanation: The variable is recreated every time the function is called. Therefore, it always starts from 1000 and returns 1001.
2. Static local variable
A static local variable retains its value between function calls.
int next_token(void)
{
    static int token = 1000;
    return ++token;
}


Output:
1001 1002 1003


Explanation: The variable is initialized only once and retains its updated value throughout the program execution.
3. Global variable using extern
A global variable can be shared between multiple source files using the extern keyword.

global_counter.c
int global_counter = 1000;

int next_global_token(void)
{
    return ++global_counter;
}


main.c
extern int global_counter;
int next_global_token(void);


Output:
1001 1002 1003


Explanation: The global variable is shared between source files. Its value remains available throughout the program execution.
4. Register variable
A register variable requests the compiler to store a frequently used variable in a CPU register, if possible.
for (register int i = 0; i < 3; i++)
{
    printf("%d ", i);
}


Output:
0 1 2


Explanation: The register variable is used as a loop counter. Its scope is limited to the loop block, and it does not maintain a token count between function calls.
Task 5.2 – Change the Requirement (2 Marks)
The hostel mess now requires two independent counters:
- Vegetarian tokens starting from 1001.
- Non-vegetarian tokens starting from 1001.
The counters must not interfere with each other.
Implementation	Modification required
Automatic	Use separate variables, but automatic local counters still reset on each call
Static	Create two separate static counters or separate functions
Global with extern	Create two global counters and share their declarations using extern
Register	Use separate loop variables, but register alone cannot maintain a persistent token count

Better solution:

Use a pointer-based counter function.
int next_token_for(int *counter)
{
    return ++(*counter);
}


Call it using separate counters:
int veg = 1000;
int nonveg = 1000;

printf("%d\n", next_token_for(&veg));
printf("%d\n", next_token_for(&nonveg));


Output:
1001
1001


Each counter maintains its own value independently.
Task 5.3 – Compare the Storage Classes (2 Marks)
Feature	Automatic	Static local	Global / extern	Register
Scope	Block	Block	File or external linkage	Block
Lifetime	Function/block execution	Entire program	Entire program	Block execution
Default initial value	Indeterminate	Zero	Zero	Indeterminate
Retains value between calls	No	Yes	Yes	No
Accidental modification	Local	Possible within scope	Higher risk due to shared access	Local

Why is taking the address of a register variable not allowed?
A register variable is intended to be accessed directly rather than through its memory address.

Therefore, C does not allow the address operator (&) to be applied to a variable declared with the register storage-class specifier.

Example:
register int i = 10;

// printf("%p", (void *)&i);  // Not allowed


The compiler may ignore the request to use a CPU register, but the restriction on taking its address still applies.
Alternative Concept and Complexity Analysis
1. Using a pointer-based counter
Instead of storing the counter inside the function, the caller maintains the counter and passes its address.
int next_token(int *counter)
{
    return ++(*counter);
}


2. Time complexity
Method	Time complexity per token
Automatic	O(1)
Static	O(1)
Global	O(1)
Register loop variable	O(1) per iteration
Pointer-based counter	O(1)

3. Space complexity
- Automatic: One local integer per active function call.
- Static: One persistent integer for the function.
- Global: One persistent integer for the program.
- Register: One loop variable.
- Pointer-based: One integer for each independent counter, plus a pointer argument.
4. Advantages of pointer-based counters
- Supports multiple independent counters.
- Avoids unnecessary global variables.
- Makes the function reusable.
- Gives the caller control over the counter's lifetime.
- Prevents different counters from accidentally sharing the same value.
Conclusion: Static variables are useful when a function must remember its previous value. Global variables allow sharing across source files, while pointer-based counters provide better flexibility when multiple independent counters are required
