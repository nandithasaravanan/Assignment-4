Task 1.1 – Diagnose the Design (2 Marks)
The given program uses parallel arrays to store patient information. This design has several weaknesses.

1. Related data is stored in separate arrays
- Patient names, ages, phone numbers, blood pressure and visit dates are stored separately.
- All arrays must use the same index to identify a patient.
- If one array is modified incorrectly, patient information may become mismatched.
2. Incorrect phone number size
- char phone[100][10] cannot safely store a 10-digit phone number as a C string.
- One additional character is required for the null terminator '\0'.
- Therefore, char phone[100][11] is required.
3. Incorrect blood pressure representation
- Blood pressure contains two values: systolic and diastolic.
- Storing both values in one float makes processing and comparison difficult.
- Separate integer fields should be used.
4. Date stored as text
- Storing dates as character strings makes date validation and comparison difficult.
- A nested structure containing day, month and year is a better design.
5. No array capacity check
- The original addPatient() does not check whether count has reached 100.
- Adding more than 100 patients may overwrite memory outside the array.
6. Use of global variables
- Global arrays and variables can be modified by any function.
- This makes debugging and maintenance difficult.
7. Difficulty sorting patients
- Sorting patients by age requires swapping corresponding elements in every parallel array.
- Missing one array during swapping can corrupt patient records.
Task 1.2 – Repair the Design (3 Marks)
The improved design uses an array of structures.
A. Structure design
Three structures are used:
- Date – stores day, month and year.
- BloodPressure – stores systolic and diastolic values.
- Patient – stores all information belonging to one patient.
B. Corrected structure declaration
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


C. Rewritten addPatient() function
The function accepts a pointer to a patient structure. Using the pointer, all patient details can be stored directly in the structure.
void addPatient(struct Patient *p,
                char name[],
                int age,
                char phone[],
                int systolic,
                int diastolic,
                struct Date date)
{
    strcpy(p->name, name);
    p->age = age;
    strcpy(p->phone, phone);

    p->bp.systolic = systolic;
    p->bp.diastolic = diastolic;

    p->visitDate = date;
}


D. Advantages of the repaired design
- All information about one patient is stored together.
- Nested structures organize blood pressure and date information.
- Structure pointers allow functions to modify patient records directly.
- Sorting becomes easier because an entire patient record can be swapped.
- The design is easier to maintain and extend.
Task 1.3 – Design Defence (1 Mark)
The structure-based design is easier to sort because all patient information is stored in one structure. Instead of swapping multiple parallel arrays, the entire patient record can be exchanged. Structures can also be passed to functions using pointers, reducing unnecessary copying. Nested structures organize related information such as blood pressure and dates. This design improves readability, maintainability and extensibility.
Alternative Concept and Complexity Analysis
1. When are parallel arrays preferred?
Parallel arrays may be preferred when:
- Only one particular field is processed frequently.
- Large datasets require efficient cache usage.
- Different fields need independent processing.
- Memory layout must be optimized for numerical operations.
2. Time complexity of sorting
Assume bubble sort is used to sort n patients by age.
Operation	Complexity
Comparisons	O(n²)
Best-case comparisons with optimized bubble sort	O(n)
Swapping complete structures	O(S) per swap
Overall worst-case sorting	O(n²)

Here, S represents the size of one patient structure.
3. Memory comparison
Design	Memory usage
Parallel arrays	Sum of individual field sizes
Array of structures	Sum of field sizes plus padding

Structure padding: The compiler may insert extra bytes between structure members to satisfy memory alignment requirements.
4. Conclusion
Array of structures is preferable for patient records because each patient's information remains together. Parallel arrays may be more efficient when processing one field across a large dataset.
