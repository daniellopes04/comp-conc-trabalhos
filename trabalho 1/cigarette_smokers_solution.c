/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/***********************************************************
 * Cigarette smokers solution
 ***********************************************************/


#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
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
    pthread_t agent_thread;        // thread that will simulate the agent

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
    
    for (i = 0; i< N; i++)
            sem_wait(&ingredients[i]);

    pthread_create(&agent_thread, NULL, agent, NULL);

    for (i = 0; i < N; i++)
    {
        smoker_num[i] = i;
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
        for (int i = 0; i< N; i++)
            sem_wait(&smokers[i]);
        puts_ingredients();
        //printf(ANSI_COLOR_GREEN "Agent put ingredients on the table\n" ANSI_COLOR_RESET);
        for (int i = 0; i< N; i++)
            sem_post(&smokers[i]);
        sleep(1);
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
    
    printf("%d  %d ",r1+1,r2+1);
    printf(ANSI_COLOR_GREEN "Agent put ingredients on the table\n" ANSI_COLOR_RESET);
    sem_wait(&smokers[3 - r1 - r2]);
;}

void *smoker(void *num)
{
    int i = *((int*)num);
    printf("Smoker %d is waiting\n", i + 1);
    while (1)
    {
        smoke(i+1);
        printf(ANSI_COLOR_GREEN "Smoker %d is smoking\n" ANSI_COLOR_RESET, i + 1);
        sleep(4);
        finishes_smoking(i+1);
        sem_post(&smokers[i]);
    }
}

void smoke(int smoker_num)
{
    int retval1, retval2;

    // waiting for ingredients
    printf("Smoker %d waits for ingredients\n", smoker_num);
    switch(smoker_num){
        case(TOBACCO):
            while(1){
                if (sem_wait(&ingredients[PAPER-1]))
                    printf("Error! %d", errno);
                if (sem_trywait(&ingredients[MATCHES-1])){
                    printf("Error! %d", errno);
                    sem_post(&ingredients[PAPER-1]);
                    sleep(1);
                }
                else
                    break;
            }
            break;

        case(PAPER):
            while(1){
                if (sem_wait(&ingredients[TOBACCO-1]))
                    printf("Error! %d", errno);
                if (sem_trywait(&ingredients[MATCHES-1])){
                    printf("Error! %d", errno);
                    sem_post(&ingredients[TOBACCO-1]);
                    sleep(1);
                }
                else
                    break;
            }
            break;

        case(MATCHES):
            while (1){
                if (sem_wait(&ingredients[TOBACCO-1]))
                    printf("Error! %d", errno);
                if (sem_trywait(&ingredients[PAPER-1])){
                    printf("Error! %d", errno);
                    sem_post(&ingredients[TOBACCO-1]);
                    sleep(1);
                }
                else
                    break;
            }
            break;

        default:
            break;
    }
    
    // got ingredients
    printf("Smoker %d got ingredients (%d %d %d)\n", smoker_num, retval1, retval2, errno);
    sleep(1);

}

void finishes_smoking(int smoker_num)
{
    printf(ANSI_COLOR_RED "Smoker %d putting ingredients down\n" ANSI_COLOR_RESET, smoker_num );
    printf("Smoker %d is waiting\n", smoker_num);
    
    switch(smoker_num){
        case(TOBACCO):
            break;

        case(PAPER):
            break;

        case(MATCHES):
            break;

        default:
            break;
    }
}
