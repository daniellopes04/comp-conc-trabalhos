#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <error.h>
#include <unistd.h>

#define N 1 //Numero de cadeiras
#define C 3 //Numero de clientes

pthread_mutex_t room;
int chairs_occupied = 0;
int chairs[N];
int next_chair = 0;

pthread_t barber;
pthread_t clients[C];
int client_id[C];

void * barber_action();
void * client_action(void *v);

int main() {
	int error_num;
	for (int i = 0; i < N; i++)
		chairs[i] = 0;

	if ((error_num = pthread_mutex_init(&room, NULL)))
		error(1, error_num, "Erro ao inicializar mutex");

	if ((error_num = pthread_create(&barber, NULL, barber_action, NULL)))
		error(1, error_num, "Erro ao inicializar thread");

	for (int i = 0; i < C; i++) {
		client_id[i] = i;
		if ((error_num = pthread_create(&clients[i], NULL, client_action, &client_id[i])))
			error(1, error_num, "Erro ao inicializar thread");
	}

	pthread_join(barber, NULL);
	for (int i = 0; i < C; i++)
		pthread_join(clients[i], NULL);
}

void * barber_action() {
	while (1) {
		printf("O barbeiro esta dormindo...\n");
		while (!chairs_occupied);
		printf("O barbeiro acordou!\n");
		pthread_mutex_lock(&room);
		printf("O barbeiro esta escolhendo o proximo cliente (Mutex travado)\n");

		while (!chairs[next_chair])
			next_chair = (next_chair + 1) % N;
		printf("O barbeiro escolheu o cliente\n");
		chairs[next_chair] = 0;
		next_chair = (next_chair + 1) % N;
		chairs_occupied--;
		printf("O barbeiro esta cortando o cabelo do cliente (Mutex destravado)\n");
		pthread_mutex_unlock(&room);
		sleep(1);
	}
}

void * client_action(void *v) {
	int id = *(int *)v;
	int i;

	while (1) {
		printf("Cliente %d chegou na barbearia\n", id);
		pthread_mutex_lock(&room);

		printf("Cliente %d esta checando a sala de espera (Mutex travado)\n", id);
		if (chairs_occupied < N) {
			printf("A sala de espera nao esta cheia, cliente %d esta procurando uma cadeira\n", id);
			for (i = 0; i < N; i++) {
				if (!chairs[i]) {
					printf("Cliente %d encontrou uma cadeira vazia\n", id);
					chairs[i] = 1;
					chairs_occupied++;
					break;
				}
			}
			printf("Cliente %d está esperando para ser atendido (Mutex destravado)\n", id);
			pthread_mutex_unlock(&room);
			while(chairs[i]);
		} else {
			printf("Sala de espera cheia, cliente %d foi embora (Mutex destravado)\n", id);
			pthread_mutex_unlock(&room);
		}
		sleep(5);
	}
}
