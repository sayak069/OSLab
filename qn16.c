#include <stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define p 5
sem_t chopstick[p];
void* dinphil(void* a){
    int i=*(int*)a;
    while(1){
        printf("philosopher %d is thinking\n",i);;
        sleep(1);
        sem_wait(&chopstick[i]);
        sem_wait(&chopstick[(i+1)%p]);
        printf("philosopher %d is holding chopsticks %d and %d\n",i,i,(i+1)%p);
        printf("philosopher %d is eating\n",i);
        sleep(1);
        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i+1)%p]);
        printf("philosopher %d is leaving the chopsticks\n",i);
    }
    return NULL;
}
int main()
{
    int j,ids[p];
    pthread_t philo[p];
    for(j=0;j<p;j++){
        sem_init(&chopstick[j],0,1);
        ids[j]=j;
    }
    for(j=0;j<p;j++){
        pthread_create(&philo[j],NULL,&dinphil,(void*)&ids[j]);
    }
    for(j=0;j<p;j++){
        pthread_join(philo[j],NULL);
    }
    return 0;
}