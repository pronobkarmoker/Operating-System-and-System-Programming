#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3
#define ARRAY_SIZE 1000

// Global variables to store statistical values
double average = 0;
int minimum_value = INT_MAX;
int maximum_value = INT_MIN;

// Structure to pass data to thread function
typedef struct
{
    int *numbers;
    int size;
} ThreadData;

// Function to calculate average
void *calculate_average(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    double sum = 0;
    for (int i = 0; i < data->size; i++)
    {
        sum += data->numbers[i];
    }
    average = sum / data->size;
    pthread_exit(NULL);
}

// Function to find maximum value
void *find_maximum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    for (int i = 0; i < data->size; i++)
    {
        if (data->numbers[i] > maximum_value)
        {
            maximum_value = data->numbers[i];
        }
    }
    pthread_exit(NULL);
}

// Function to find minimum value
void *find_minimum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    for (int i = 0; i < data->size; i++)
    {
        if (data->numbers[i] < minimum_value)
        {
            minimum_value = data->numbers[i];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    // Read numbers from command line arguments
    int numbers[ARRAY_SIZE];
    int num_count = argc - 1;
    for (int i = 1; i < argc; i++)
    {
        numbers[i - 1] = atoi(argv[i]);
    }

    pthread_t threads[NUM_THREADS];
    ThreadData data = {numbers, num_count};

    // Create threads
    pthread_create(&threads[0], NULL, calculate_average, &data);
    pthread_create(&threads[1], NULL, find_maximum, &data);
    pthread_create(&threads[2], NULL, find_minimum, &data);

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Output statistical values
    printf("The average value is %.2f\n", average);
    printf("The minimum value is %d\n", minimum_value);
    printf("The maximum value is %d\n", maximum_value);

    return 0;
}
