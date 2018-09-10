#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5 //Numero de cadeiras

pthread_mutex_t room;
pthread_t barber;
pthread_t customer;
sem_t seats;

int main() {
	int error = pthread_mutex_init(&room, NULL);
	if(error) exit(1);
	error = sem_init(&seats, 0, N);
	if(error) exit(1);
}

void barber_action() {}
