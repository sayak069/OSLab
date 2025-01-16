#include<stdio.h>
#include<pthread.h>
#define max 100

int m1[max][max],m2[max][max],res[max][max],m,n;
pthread_mutex_t mutex;

void* input_mtx(void* arg){
    printf("enter no of rows and cols: ");
    scanf("%d %d",&m,&n);
    printf("enter mtx 1: ");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&m1[i][j]);
        }
    }
    printf("enter mtx 2: ");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&m2[i][j]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* add(void* arg){
    pthread_mutex_lock(&mutex);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            res[i][j]=m1[i][j]+m2[i][j];
        }
    }
    printf("result matrix\n");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d ",res[i][j]);
        }
        printf("\n");
    }
}

int main(){
    pthread_t t1,t2;
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_lock(&mutex);
    pthread_create(&t1,NULL,input_mtx,NULL);
    pthread_create(&t2,NULL,add,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}