#ifndef TEST_SRC_HPP
#define TEST_SRC_HPP

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

void create_processes();

void grandchild();
void child();
void parent();



void priority(int n_jobs, Job* jobs);
void priority_rr(int n_jobs, Job* jobs, int time_slice);

typedef void (*Operation)();
typedef struct job
{
    int idx;
    int time;
    int priority;
    Operation run_job;
} Job;

int jobcmp(const void* a, const void* b);
void job0(int time);
void job1(int time);
void job2(int time);
void create_jobs(int* n_jobs, Job** jobs);

#endif
