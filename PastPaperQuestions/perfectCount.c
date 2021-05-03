//Function is_perfect returns true if a number is perfect (the sum of all its factors), with signature: int is_perfect(int_n);
//It returns 1 if n is perfect, and 0 otherwise.
//Using this function, write a multi-threaded C program to count the number of perfect numbers in the interval 1…N.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int count;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int is_perfect(int num){
    int loop,sum=0;
  
    for(loop=1; loop<num; loop++){
        if(num%loop==0)
            sum+=loop;
    }
     
    if(sum==num)
        return 1; /*Perfect Number*/
    else
        return 0; /*Not Perfect Number*/
}

void *checkPerf(void *n){
    int perf = is_perfect((int)n);

    if(perf){
            pthread_mutex_lock(&m);
            count++;
            pthread_mutex_unlock(&m);
    }

    pthread_exit(NULL);
}

int main(){
    int N;
    printf("Enter N.\n");
    scanf("%d",&N);

    pthread_t threads[N];
    long rc;

    for(int n=1; n<=N; n++){
    	
        rc = pthread_create(&threads[n-1], NULL, checkPerf, (void *)n);
        if(rc){
            printf("Error return code from pthread_create(): %ld\n", rc);
            exit(-1);
        }
    }

    for(int n=1; n<=N; n++){
        pthread_join(threads[n-1], NULL);
    }

    printf("Total count = %d\n", count);

    return 0;
}
