#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define NUM_POINTS 1000000
#define NUM_THREADS 4

typedef struct
{
    int points_in_circle;
} ThreadData;

void *monte_carlo(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    data->points_in_circle = 0;

    unsigned int seed = (unsigned int)pthread_self();
    srand(seed);

    for (int i = 0; i < NUM_POINTS / NUM_THREADS; i++)
    {
        double x = ((double)rand() / RAND_MAX) * 2.0 - 1.0; 
        double y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;

        if (x * x + y * y <= 1.0)
        { 
            data->points_in_circle++;
        }
    }

    return NULL;
}


int main()
{
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int total_points_in_circle = 0;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, monte_carlo, (void *)&thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
        total_points_in_circle += thread_data[i].points_in_circle;
    }


    double pi_estimate = 4.0 * total_points_in_circle / (double)(NUM_POINTS);
    printf("Estimated value of pi: %f\n", pi_estimate);

    return 0;
}
