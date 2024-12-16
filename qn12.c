#include <stdio.h>
#include<pthread.h>
#include<unistd.h>
int cnt=0;
pthread_mutex_t mutex1;
void* func(void* arg){
    int id=*(int*)arg;
    pthread_mutex_lock(&mutex1);
    printf("Thread %d: Lock acquired.\n", id);
    printf("thread %d;before modification=%d\n",id,cnt);
    int temp=cnt;
    temp++;
    sleep(1);
    cnt=temp;
    printf("thread %d;after modification=%d\n",id,cnt);
    pthread_mutex_unlock(&mutex1);
     printf("Thread %d: Lock released.\n\n", id);
}
int main()
{
    pthread_t th[5];
    int ids[5];
    printf("initial value=%d\n",cnt);
    for(int i=0;i<5;i++){
        ids[i]=i+1;
        pthread_create(&th[i],NULL,&func,(void*)&ids[i]);
    }
    for(int i=0;i<5;i++){
        pthread_join(th[i],NULL);
    }
    printf("final value=%d\n",cnt);
    return 0;
}