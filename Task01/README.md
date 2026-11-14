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
