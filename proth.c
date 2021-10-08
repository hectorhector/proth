#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <pthread.h>
#include <time.h>

#include <gmp.h>

/* the real test (max complete n=36576908*/
//#define K_CONST 21181
//#define N_CONST 44200000
//#define N_CONST 36576908

/* recent find (k=46157, n=698207)*/
//#define K_CONST 46157
//#define N_CONST 698203

/* searching for k=301, n=7360 */
#define K_CONST 301
#define N_CONST 6500

#define NUM_CORES 6

static void * proth_thread(void *arg);

//mutex protected, thread safe n
unsigned long int n_val = N_CONST;
pthread_mutex_t n_lock;
pthread_mutex_t found_lock;

int main(void)
{
    time_t start;
    time_t end;
    time(&start);

    //array to keep track of the thread id's
    pthread_t thread_ids[NUM_CORES];

    //create the mutexes
    pthread_mutex_init(&n_lock, NULL);
    pthread_mutex_init(&found_lock, NULL);

    //create the threads
    for(int i = 0; i < NUM_CORES; i++)
    {
        pthread_create(&thread_ids[i], NULL, &proth_thread, NULL);
    }

    //lock main thread until prime is found
    pthread_mutex_lock(&found_lock);
    pthread_mutex_lock(&found_lock);

    //destroy the threads
    for(int i = 0; i < NUM_CORES; i++)
    {
        pthread_cancel(thread_ids[i]);
    }

    //destroy the mutexes
    pthread_mutex_destroy(&n_lock);
    pthread_mutex_destroy(&found_lock);

    time(&end);
    printf("total time: %f seconds\n", difftime(end, start));
}

unsigned long get_n()
{
    pthread_mutex_lock(&n_lock);
    unsigned long n = n_val;
    n_val++;
    pthread_mutex_unlock(&n_lock);
    return n;
}

static void * proth_thread(void *arg) 
{
    //proth number is p=k*2^n+1
    unsigned long int n;

    // variables to calculate the proth number: p=k*2^n+1
    mpz_t proth;    // the proth number
    mpz_t p_minus1; // the proth number minus 1
    mpz_t k;        // k
    mpz_t two;      // 2
    mpz_t two_n;    // 2^n

    // variables to test the primality: t = a^((p-1)/2) % p
    mpz_t t;
    mpz_t a1;
    mpz_t a2;
    mpz_t a_exp;

    //initialize the variables
    mpz_init(proth);
    mpz_init(p_minus1);
    mpz_init(k);
    mpz_init(two);
    mpz_init(two_n);
    mpz_init(t);
    mpz_init(a1);
    mpz_init(a2);
    mpz_init(a_exp);

    mpz_set_ui(a1, 3);
    mpz_set_ui(a2, 5);

    //proth number is p=k*2^n+1
    //set the k constant
    mpz_set_ui(k, K_CONST);
    //set two=2 
    mpz_set_ui(two, 2);

    while (1)
    {
        //get the thread-safe n
        n = get_n();
        printf("(n=%lu)\n", n);

        //Step 1: Caluclate the Proth Number
        //calc exp=2^n
        mpz_pow_ui(two_n, two, n);
        //calc p=k*2^n
        mpz_mul(p_minus1, k, two_n);
        //calc p=k*2^n+1 (this is our proth number)
        mpz_add_ui(proth, p_minus1, 1);

        //Step 2: Check if the Proth Number is Prime
        //the prime check exponent is (p-1)/2
        mpz_divexact_ui(a_exp, p_minus1, 2);

        //printf("prime check a=3\n");
        mpz_powm(t, a1, a_exp, proth);
        mpz_add_ui(t, t, 1);
        if(mpz_cmp(t, proth) == 0)
        {
            printf("prime with a=3!\n");
            break;
        }

        //printf("prime check a=5\n");
        mpz_powm(t, a2, a_exp, proth);
        mpz_add_ui(t, t, 1);
        if(mpz_cmp(t, proth) == 0)
        {
            printf("prime with a=5!\n");
            break;
        }
    }
    
    //proth number is k*2^n+1
    gmp_printf("%Zd*2^%llu+1 is prime!\n", k, n);

    //free
    mpz_clear(proth);
    mpz_init(p_minus1);
    mpz_clear(k);
    mpz_clear(two);
    mpz_clear(two_n);
    mpz_clear(t);
    mpz_clear(a1);
    mpz_clear(a2);
    mpz_clear(a_exp);

    FILE *fp = fopen("proth_file", "w");
    fprintf(fp, "%lu\n", n);
    fclose(fp);

    pthread_mutex_unlock(&found_lock);

    return NULL;
}
