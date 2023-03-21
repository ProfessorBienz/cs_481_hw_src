#include "src.hpp"

int my_rand_ctr;
long* my_rand_vals;

// Initialize Queue Methods
void queue_init(queue_t& queue)
{
    node_t* head = (node_t*)malloc(sizeof(node_t));
    head->next = NULL;
    queue.head = head;
    queue.tail = head;
    queue.size = 0;
}

int queue_empty(queue_t& queue)
{
    return (queue.size == 0);
}

void queue_add(queue_t& queue, pthread_t thread)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->thread = thread;
    queue.tail->next = new_node;
    queue.size++; 
}

pthread_t queue_remove(queue_t& queue)
{
    node_t* front_thread = queue.head->next;
    queue.head->next = front_thread->next;
    if (front_thread == queue.tail) 
        queue.tail = queue.head;
    queue.size--;
    pthread_t thread = front_thread->thread;
    free(front_thread);
    return thread;
}

void queue_destroy(queue_t& queue)
{
    free(queue.head);
}


// Compute PI Helper
double pthread_compute_pi(int num_threads, int num_samples)
{
    calc_t* pi_calc = (calc_t*)malloc(sizeof(calc_t));
    pi_calc->global_sum = 0;
    pi_calc->global_n_samples = num_samples;
    pi_calc->global_n_threads = num_threads;

    pthread_t* threads = (pthread_t*)malloc(num_threads*sizeof(pthread_t));
    thread_data_t* thread_data = (thread_data_t*)malloc(num_threads*sizeof(thread_data_t));

    init(&(pi_calc->lock));
    rand_init(num_samples);

    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].pi_calc = pi_calc;
        thread_data[i].thread_id = i;
        pthread_create(&(threads[i]), NULL, compute_pi, &(thread_data[i]));
    }
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    free(threads);
    free(thread_data);

    rand_destroy();

    destroy(&(pi_calc->lock));
    
    return 4.0 * pi_calc->global_sum / (1.0*num_samples);
}

// Thread Safe Random Value Generator 
void rand_init(int global_n)
{
    my_rand_ctr = 0;
    my_rand_vals = (long*)malloc(2*global_n*sizeof(long));

    srand(time(NULL));
    for (int i = 0; i < 2*global_n; i++)
        my_rand_vals[i] = rand();
}

void rand_destroy()
{
    free(my_rand_vals);
}

int thread_rand()
{
    // Atomically update to avoid two threads grabbing same random value
    int idx = __sync_fetch_and_add(&my_rand_ctr, 1);
    return my_rand_vals[idx];
}
