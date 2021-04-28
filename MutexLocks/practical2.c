
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "cond.c"


int pnum;  // number updated when producer runs.
int csum;  // sum computed using pnum when consumer runs.
int prevcon;	// consumer had the lock previously
int prevpro;	// producer had the lock previously

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cvcon;		// consumer's condition variable
pthread_cond_t cvpro;		// producer's condition variable


int (*pred)(int); // predicate indicating if pnum is to be consumed

int produceT() {
  scanf("%d",&pnum); // read a number from stdin
  return pnum;
}

void *Produce(void *a) {
  int p;
  p=1;

  while (p) {  
    	pthread_mutex_lock(&m);	//aquire lock IF FIRST OR IF FOLLOWING CONSUMER THREAD
    	while(prevcon != 1){
    		pthread_cond_wait(&cvpro, &m);
    	}
    	printf("@P-READY\n");
    	p = produceT();
    	printf("@PRODUCED %d\n",p);
    	prevcon = 0;
    	prevpro = 1;		//tells consumer, the producer just had the lock
    	pthread_cond_signal(&cvcon);
    	pthread_mutex_unlock(&m);	//unlock and give consumer access
  }
  printf("@P-EXIT\n");
  pthread_exit(NULL);
}


int consumeT() {
  if ( pred(pnum) ) { csum += pnum; }
  return pnum;
}

void *Consume(void *a) {
  int p;

  p=1;
  while (p) {
    	pthread_mutex_lock(&m);		//aquire lock IF FOLLOWING PRODUCER THREAD
    	while(prevpro != 1){
    		pthread_cond_wait(&cvcon, &m);
    	}
    	printf("@C-READY\n");
	p = consumeT();
	printf("@CONSUMED %d\n",csum);
    	prevpro = 0;
    	prevcon = 1;			//tells producer, the consumer just had the lock
    	pthread_cond_signal(&cvpro);
    	pthread_mutex_unlock(&m);		//unlock and give producer access
  }
  printf("@C-EXIT\n");
  pthread_exit(NULL);
}


int main (int argc, const char * argv[]) {
  // the current number predicate
  static pthread_t prod,cons;
	long rc;

  pred = &cond1;
  if (argc>1) {
    if      (!strncmp(argv[1],"2",10)) { pred = &cond2; }
    else if (!strncmp(argv[1],"3",10)) { pred = &cond3; }
  }


  pnum = 999;
  csum=0;
  prevcon = 1;	//allow producer to get lock
  srand(time(0));

  
  printf("cvcon initializing.\n");
 	rc = pthread_cond_init(&cvcon, NULL);
	if (rc) {
			printf("Error initializing conditional variable.\n");
			exit(-1);
		}  
  printf("cvpro initializing.\n");
 	rc = pthread_cond_init(&cvpro, NULL);
	if (rc) {
			printf("Error initializing conditional variable.\n");
			exit(-1);
		}  
  printf("@P-CREATE\n");
 	rc = pthread_create(&prod,NULL,Produce,(void *)0);
	if (rc) {
			printf("@P-ERROR %ld\n",rc);
			exit(-1);
		}
  printf("@C-CREATE\n");
 	rc = pthread_create(&cons,NULL,Consume,(void *)0);
	if (rc) {
			printf("@C-ERROR %ld\n",rc);
			exit(-1);
		}

  printf("@P-JOIN\n");
  pthread_join( prod, NULL);
  printf("@C-JOIN\n");
  pthread_join( cons, NULL);


  printf("@CSUM=%d.\n",csum);

  return 0;
}
