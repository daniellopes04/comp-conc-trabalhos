/***********************************************************
 * Cigarette smokers solution
 ***********************************************************/


#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define N 3             // number of smokers

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"


// The ingredients are numbered like the following:
#define     TOBACCO     1
#define     PAPER       2
#define     MATCHES     3

// The smokers are numbered like the following:
//      1: Smoker who has tobacco
//      2: Smoker who has paper
//      3: Smoker who has matches

sem_t smokers[N];       // binary semaphores simulating each smoker's behavior
sem_t ingredients[N];   // binary semaphores controling the access to each ingredient

extern int errno;

void *agent(void);
void puts_ingredients(void);
void *smoker(void *num);
void smoke(int);
void finishes_smoking(int);
void test(int);

int smoker_num[N];      // number of each smoker

int main()
{
    printf("Cigarette Smokers: working example 1\n");

    int i, retval;
    pthread_t thread_id[N]; // each thread will simulate the behavior of one smoker
    pthread_t agent;        // thread that will simulate the agent

    for (i = 0; i < N; i++)
    {
        retval = sem_init(&smokers[i], 0, 1);
        printf("(%d %d)\n", retval, errno);
    }

    for (i = 0; i < N; i++)
    {
        retval = sem_init(&ingredients[i], 0, 1);
        printf("(%d %d)\n", retval, errno);
    }

    pthread_create(&agent, NULL, agent, NULL);

    for (i = 0; i < N; i++)
    {
        printf("Created smoker %d\n", smoker_num[i] + 1);
        pthread_create(&thread_id[i], NULL, smoker, &smoker_num[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}

void *agent(void)
{ 
    printf("Agent is waiting to put ingredients on the table\n");
    while (1)
    {
        puts_ingredients();
        printf(ANSI_COLOR_GREEN "Agent put ingredients on the table\n" ANSI_COLOR_RESET);
        sleep(0);
    }
}

void puts_ingredients(void)
{
    int r1, r2;

    r1 = rand() % N;
    r2 = rand() % N;
    
    while (r2 == r1)
        r2 = rand() % N;

    sem_post(&ingredients[r1]);
    sem_post(&ingredients[r2]);
}

void *smoker(void *num)
{
    int i = *((int*)num);
    printf("Smoker %d is waiting\n", i + 1);
    while (1)
    {
        smoke(i);
        printf(ANSI_COLOR_GREEN "Smoker %d is smoking\n" ANSI_COLOR_RESET, i + 1);
        sleep(0);
        finishes_smoking(i);
    }
}

void smoke(int smoker_num)
{
    int retval1, retval2;

    // waiting for ingredients
    printf("Smoker %d waits for ingredients\n", smoker_num + 1);
    switch(smoker_num){
        case(1):
            retval1 = sem_wait(&ingredients[PAPER]);
            retval2 = sem_wait(&ingredients[MATCHES]);
            break;

        case(2):
            retval1 = sem_wait(&ingredients[TOBACCO]);
            retval2 = sem_wait(&ingredients[MATCHES]);
            break;

        case(3):
            retval1 = sem_wait(&ingredients[TOBACCO]);
            retval2 = sem_wait(&ingredients[PAPER]);
            break;

        default:
            break;
    }
    
    // got ingredients
    printf("Smoker %d got ingredients (%d %d %d)\n", smoker_num + 1, retval1, retval2, errno);

    sleep(1);

}

void finishes_smoking(int smoker_num)
{
    printf("Smoker %d putting ingredients down\n", smoker_num + 1);
    printf("Smoker %d is waiting\n", smoker_num + 1);
    
    switch(smoker_num){
        case(1):
            sem_post(&ingredients[PAPER]);
            sleep(1);
            sem_post(&ingredients[MATCHES]);
            sleep(1);
            break;

        case(2):
            sem_post(&ingredients[TOBACCO]);
            sleep(1);
            sem_post(&ingredients[MATCHES]);
            sleep(1);
            break;

        case(3):
            sem_post(&ingredients[TOBACCO]);
            sleep(1);
            sem_post(&ingredients[PAPER]);
            sleep(1);
            break;

        default:
            break;
    }
}
