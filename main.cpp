#include <bits/stdc++.h>
#include <pthread.h>

volatile int semafor;
volatile int mysliwi;
volatile int kucharze;
volatile int zwierzyna;
volatile int pozywienie;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* polowanie(void* arg)
{
    int atak = rand()%6;
    int obr  = rand()%6;
    if (atak > obr) zwierzyna++;

    pthread_mutex_lock(&mutex1);
    if (pozywienie > 0) pozywienie--;
    else 				mysliwi--;
    pthread_mutex_unlock(&mutex1);

    semafor--;
	return 0;
}

void* pieczenie(void* arg)
{
    pthread_mutex_lock(&mutex2);
    if (zwierzyna > 0)
    {
        zwierzyna--;
        pozywienie += rand()%6 + 1;
    }
    pthread_mutex_unlock(&mutex2);

    pthread_mutex_lock(&mutex1);
    if (pozywienie > 0) pozywienie--;
    else				kucharze--;
    pthread_mutex_unlock(&mutex1);

    semafor--;
	return 0;
}

int main (int argc, char* argv[])
{
    srand(time(NULL));

    mysliwi    = atoi(argv[1]);
    kucharze   = atoi(argv[2]);
    zwierzyna  = atoi(argv[3]);
    pozywienie = atoi(argv[4]);
    printf("Stan poczatkowy:\nMysliwi    - %d\nKucharze   - %d\nZwierzyna  - %d\nPozywienie - %d\n\n", mysliwi, kucharze, zwierzyna, pozywienie);

    for (int i=1; i<365 && mysliwi+kucharze; i++)
    {
        for (int j=mysliwi; j>0; j--)
        {
            semafor++;
            pthread_t t;
            pthread_create(&t, NULL, polowanie, NULL);
        }
        for (int j=kucharze; j>0; j--)
        {
            semafor++;
            pthread_t t;
            pthread_create(&t, NULL, pieczenie, NULL);
        }
        while(semafor);
        printf("Stan na dzien %d:\nMysliwi    - %d\nKucharze   - %d\nZwierzyna  - %d\nPozywienie - %d\n\n", i, mysliwi, kucharze, zwierzyna, pozywienie);
    }

	return 0;
}
