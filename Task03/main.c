
#include <stdio.h>

// Type of sensor reading
enum kind
{
    TEMPERATURE,
    HUMIDITY,
    STATUS
};

// Structure containing all three fields
struct packet
{
    float celsius;
    int percent;
    char status[8];
};

// Tagged union structure
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

// Function to display the valid packet member
void show(const struct reading *r)
{
    // TODO 1: Use switch to print the valid union member

    switch (r->type)
    {
        case TEMPERATURE:
            printf("Temp %.1f C\n", r->value.celsius);
            break;

        case HUMIDITY:
            printf("Humidity %d %%\n", r->value.percent);
            break;

        case STATUS:
            printf("Status %s\n", r->value.status);
            break;

        default:
            printf("Invalid packet type\n");
    }
}

int main(void)
{
    // Initialise three sensor packets
    struct reading log[3] =
    {
        {TEMPERATURE, {.celsius = 31.5f}},
        {HUMIDITY, {.percent = 68}},
        {STATUS, {.status = "OK"}}
    };

    // Display memory sizes
    printf("sizeof union = %zu, sizeof struct reading = %zu\n",
           sizeof(log[0].value),
           sizeof(log[0]));

    // Display all sensor readings
    for (int i = 0; i < 3; i++)
    {
        show(&log[i]);
    }

    // Misuse experiment
    struct reading wrong;

    wrong.type = TEMPERATURE;
    wrong.value.celsius = 31.5f;

    printf("\nMisuse experiment:\n");

    // Reading an inactive union member
    printf("Temperature stored: %.1f C\n",
           wrong.value.celsius);

    printf("Reading humidity member: %d\n",
           wrong.value.percent);

    // Compare structure memory size
    printf("\nSize of structure with all fields = %zu bytes\n",
           sizeof(struct packet));

    return 0;
}
