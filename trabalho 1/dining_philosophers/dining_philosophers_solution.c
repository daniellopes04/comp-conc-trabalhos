#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define N 5 // number of philosophers

#define LEFT ((ph_num + 0) % N)
#define RIGHT ((ph_num + 1) % N)

sem_t chopsticks[N]; // binary semaphores controling the access to each chopstick
int chopstick_weights[N];

extern int errno;

void *philospher(void *num);
void take_chopstick(int);
void put_chopstick(int);
void test(int);

int phil_num[N];

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main()
{
    int ph_num;
    for (ph_num = 0; ph_num < N; ph_num++) {
        printf("Philosopher %d needs chopsticks %d and %d\n", ph_num + 1, LEFT + 1, RIGHT + 1);
    }

    printf("Dining Philosophers: solution proposal\n");

    int i, retval;
    pthread_t thread_id[N]; // each thread will simulate the behavior of one philosopher

    for (i = 0; i < N; i++)
    {
        retval = sem_init(&chopsticks[i], 0, 1);
        printf("(%d %d)\n", retval, errno);
    }

    for (i = 0; i < N; i++)
    {
        phil_num[i] = (N - i + 1) % N; // shuffling philosophers creation order
        printf("Created philosopher %d\n", phil_num[i] + 1);
        pthread_create(&thread_id[i], NULL, philospher, &phil_num[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}

void *philospher(void *num)
{
    int i = *((int*)num);
    printf("Philosopher %d is thinking\n", i + 1);
    while (1)
    {
        take_chopstick(i);
        printf(ANSI_COLOR_GREEN "Philosopher %d is eating\n" ANSI_COLOR_RESET, i + 1);
        sleep(0);
        put_chopstick(i);
    }
}

int max(int a, int b){
    if (a > b)
        return a;
    return b;
}

void take_chopstick(int ph_num)
{
    int retval1;

    //Philospher takes highest-numbered chopstick first.
    int first = max(LEFT, RIGHT);
    int second = (LEFT+RIGHT - first);
    
    printf("Philosopher %d is Hungry and waits for chopstick %d\n", ph_num + 1, first+1);
    retval1 = sem_wait(&chopsticks[first]);
    
    printf("Philosopher %d got chopstick %d (%d %d)\n", ph_num + 1, first + 1, retval1, errno);

    sleep(1);


    printf("Philosopher %d now waits for chopstick %d\n", ph_num + 1, second + 1);
    retval1 = sem_wait(&chopsticks[second]);

    printf("Philosopher %d took chopstick %d and %d (%d %d)\n", ph_num + 1, LEFT + 1, RIGHT + 1, retval1, errno);

}

void put_chopstick(int ph_num)
{
    printf("Philosopher %d putting chopstick %d and %d down\n", ph_num + 1, LEFT + 1, RIGHT + 1);
    printf("Philosopher %d is thinking\n", ph_num + 1);
    sem_post(&chopsticks[LEFT]);
    sleep(1);
    sem_post(&chopsticks[RIGHT]);
    sleep(1);
}