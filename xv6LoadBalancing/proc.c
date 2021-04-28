#include "types.h"
#include "defs.h"
#include <stdio.h>
#include "proc.h"

#define NCPU 1

struct cpu cpus[NCPU];
int ncpu;

void printstate(enum procstate pstate){ // DO NOT MODIFY
  switch(pstate) {
    case UNUSED   : printf("UNUSED");   break;
    case EMBRYO   : printf("EMBRYO");   break;
    case SLEEPING : printf("SLEEPING"); break;
    case RUNNABLE : printf("RUNNABLE"); break;
    case RUNNING  : printf("RUNNING");  break;
    case ZOMBIE   : printf("ZOMBIE");   break;
    default       : printf("????????");
  }
}

struct proc *p;
struct cpu *c = cpus;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <limits.h>
#define arraySize (sizeof(ptable.proc)/sizeof(ptable.proc[0]))
int array[arraySize];

void scheduler(void){
    int runnableFound;
    c->proc = 0;
    runnableFound = 1 ;

    int i=0;
    int j, minRuns;
    
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
        array[i] = 0;
        i++;
    }
    
    while(runnableFound){
        runnableFound = 0;
        
        minRuns = INT_MAX;
        j=0;
        for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
            if(p->state == RUNNABLE && minRuns>array[j])
                minRuns = array[j];
            j++;
        }
        
        i=-1;
        for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
            i++;
            
            if(p->state != RUNNABLE || minRuns != array[i]){
                continue;
            }

            array[i]++;
            
            runnableFound = 1;
            c->proc = p;
            p->state = RUNNING;
            swtch(p);
            c->proc = 0;
            break;
        }
    }
  printf("No RUNNABLE process!\n");
}
