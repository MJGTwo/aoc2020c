#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

int day1();

int (*functions[])() =
    {
        day1};

int64_t run_day(int8_t day, int8_t samples)
{
    struct timeval time_start, time_end, time_diff;
    int64_t best_elapsed_time = 1000000;

    for (int8_t i = 0; i < samples; i++)
    {
        gettimeofday(&time_start, NULL);
        functions[day - 1]();
        gettimeofday(&time_end, NULL);
        timersub(&time_end, &time_start, &time_diff);
        int64_t elapsed_time = (int64_t)(time_diff.tv_sec * 1000000) + (int64_t)time_diff.tv_usec;
        if (elapsed_time < best_elapsed_time)
        {
            best_elapsed_time = elapsed_time;
        }
    }
    return best_elapsed_time;
}

static void usage(const char *argv0)
{
    printf("Usage: %s [1] [options]\n", argv0);
    puts(
        "Options:\n"
        "\t-h, --help       Show this help text\n"
        "\t-b, --bench      Run 10 times, take best time\n");
}

int main(int argc, char **argv)
{
    int8_t n_samples = 1;
    int8_t day = 0;

    //parse CLI args
    for (int8_t i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            usage(argv[0]);
            return EXIT_SUCCESS;
        }
        else if (strcmp(argv[i], "--bench") == 0 || strcmp(argv[i], "-b") == 0)
        {
            n_samples = 100;
        }
        else if (isdigit(*argv[i]))
        {
            while (isdigit(*argv[i]))
            {
                day = day * 10 + (*argv[i] - '0');
                argv[i]++;
            }
        }
    }

    // run a single day
    if (day > 0)
    {
        int64_t elapsed_time = run_day(day, n_samples);
        printf("Ran in %8lld us\n", elapsed_time);
        return EXIT_SUCCESS;
    }

    int64_t total_time = 0;
    int64_t times[25] = {0};
    for (int8_t day_itr = 1; day_itr <= 25; day_itr++)
    {
        int64_t elapsed_time = run_day(day_itr, n_samples);
        times[day_itr - 1] = elapsed_time;
        total_time += elapsed_time;
    }
}