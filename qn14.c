#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

sem_t wrt;
pthread_mutex_t mutex;
int item=0,rcount=0;

void* writer(void* i){
    int id=*(int*)i;
    while(1){
        sem_wait(&wrt);
        printf("writer %d has entered cs\n",id);
        sleep(1);
        item=rand()%100;
        printf("writer %d wrote %d\n",id,item);
        printf("writer %d left cs\n",id);
        sem_post(&wrt);
    }
    return NULL;
}
void* reader(void* i){
    int id=*(int*)i;
    while(1){
        pthread_mutex_lock(&mutex);
        rcount++;
        if(rcount==1){
            sem_wait(&wrt);
        }
        pthread_mutex_unlock(&mutex);
        printf("reader %d has entered cs\n",id);
        sleep(1);
        printf("reader %d read %d\n",id,item);
        printf("reader %d left cs\n",id);
        pthread_mutex_lock(&mutex);
        rcount--;
        if(rcount==0){
            sem_post(&wrt);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main(){
   int m,n;
   printf("no of writer and reader: ");
   scanf("%d %d",&m,&n);
   pthread_t wth[10],rth[10];
   int idw[10],idr[10];
   sem_init(&wrt,0,1);
   for(int i=0;i<m;i++){
       idw[i]=i+1;
       pthread_create(&wth[i],NULL,writer,(void*)&idw[i]);
   }
   for(int i=0;i<n;i++){
       idr[i]=i+1;
       pthread_create(&rth[i],NULL,reader,(void*)&idr[i]);
   }
   for(int i=0;i<m;i++){
       pthread_join(wth[i],NULL);
   }
   for(int i=0;i<n;i++){
       pthread_join(rth[i],NULL);
   }
   return 0;
}