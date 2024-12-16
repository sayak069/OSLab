#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define size 5

sem_t s1,empty,full;
int item=0,p=0,c=0;
int buffer[size];

void* producer(void* i) {
	int id=*(int*)i;
	while(1) {
		sem_wait(&empty);
		sem_wait(&s1);
		printf("producer %d has entered cs\n",id);
		sleep(1);
		int x=item++;
		buffer[p]=x;
		p=(p + 1)%size;
		printf("producer %d produced %d\n",id,x);
		printf("producer %d has left cs\n",id);
		sem_post(&full);
		sem_post(&s1);
	}
	return NULL;
}
void* consumer(void* i) {
	int id=*(int*)i;
	while(1) {
		sem_wait(&full);
		sem_wait(&s1);
		printf("consumer %d has entered cs\n",id);
		sleep(1);
		int x=buffer[c];
		c=(c + 1)%size;
		printf("consumer %d consumed %d\n",id,x);
		printf("consumer %d has left cs\n",id);
		sem_post(&empty);
		sem_post(&s1);
	}
	return NULL;
}
int main() {
	pthread_t pth[10],cth[10];
	int m,n,j;
	int idp[10],idc[10];
	printf("no of producer and consumer: ");
	scanf("%d %d",&m,&n);
	sem_init(&s1,0,1);
	sem_init(&empty,0,size);
	sem_init(&full,0,0);
	for(j=0; j<m; j++) {
		idp[j]=j+1;
		pthread_create(&pth[j],NULL,producer,(void*)&idp[j]);
	}
	for(j=0; j<n; j++) {
		idc[j]=j+1;
		pthread_create(&cth[j],NULL,consumer,(void*)&idc[j]);
	}
	for(j=0; j<m; j++) {
		pthread_join(pth[j],NULL);
	}
	for(j=0; j<n; j++) {
		pthread_join(cth[j],NULL);
	}
	return 0;
}