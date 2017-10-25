#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXTHREADS 4

long LARGESTRETVAL = 0; // largest return value
long LARGESTARG = 0;    // largest argument value
long nthreads;

void *sum_local(void *arg);

int main(int argc, char **argv)
{
    alarm(60);
    printf("Test before variables.\n");
    long i, myid[MAXTHREADS], result = 0;
    pthread_t tid[MAXTHREADS];

    printf("argc : %d \n", argc);
    printf("argv[0] : %s \n", argv[0]);
    printf("argv[1] : %s \n", argv[1]);
    printf("argv[2] : %s \n", argv[2]);

    if (argc != 3) {
        printf("Usage: %s <nthreads> \n", argv[0]);
        exit(-1);
    }

    nthreads   = atoi(argv[1]);
    //log_nelems = atoi(argv[2]);
    //nelems = (1L << log_nelems);

   /* if  ((nelems % nthreads) != 0 || (log_nelems > 31)) {
        printf("error: invalid nelems\n");
        exit(-1);
    }
    nelems_per_thread = nelems / nthreads;*/

    for (i = 0; i < nthreads; i++) {
        myid[i] = i;
        //printf("test: %ld\n",i);
        pthread_create(&tid[i], NULL, sum_local, &myid[i]);
    }
    for (i = 0; i < nthreads; i++)
        pthread_join(tid[i], NULL);

    // for (i = 0; i < nthreads; i++)
        //    result += psum[i];
    //if (result != (nelems * (nelems-1))/2)
       // printf("error: result=%ld\n", result);


    printf("Largest return code: %ld, argument: %ld\n", LARGESTRETVAL, LARGESTARG);

    exit(0);
}

void *sum_local(void *arg)
{
    long myid = *((long *)arg);
    long i, start, end, nelems_per_thread, sum = 0;
    switch(nthreads)
    {
        case 1:
                nelems_per_thread = 100;
                start = 1;
                end  = 101;
                break;
        case 2:
                nelems_per_thread = 50;
                start = (myid * nelems_per_thread)+1 ;
                end = (start + nelems_per_thread);
                break;
        case 3:
                nelems_per_thread = 33;
                start = (myid * nelems_per_thread) +1;
                if(myid == 2) {
                        end = (start + nelems_per_thread) + 1;
                }else {
                        end = (start + nelems_per_thread);
                }
                break;
        case 4:
                nelems_per_thread = 25;
                start = (myid * nelems_per_thread) + 1;
                end = (start + nelems_per_thread);
                break;
        default:
                break;
    }

    //long start = myid * nelems_per_thread;
    //long end = start + nelems_per_thread;
    for (i = start; i < end; i++) {
        sum += i;
        //printf("%ld\n",i);
        long retCode = p4test(i);
        if(retCode > LARGESTRETVAL){
                LARGESTRETVAL = retCode;
                LARGESTARG = i;
        }
    }

    //psum[myid] = sum;
    return NULL;
}
                                                             
