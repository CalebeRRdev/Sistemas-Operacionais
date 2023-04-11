#include<stdio.h>
#include<pthread.h>

void *thread_func(void *arg){
    printf("Ola Mundo!\n");
    return NULL;
}


void *thread_func1(void *arg){
    printf("Boa noite!\n");
    return NULL;
}

int main(){
    pthread_t thread_id;
    pthread_create(&thread_id,NULL,thread_func,NULL);
    pthread_join(thread_id,NULL);
    pthread_create(&thread_id,NULL,thread_func1,NULL);
    pthread_join(thread_id,NULL);
    return 0;
}
