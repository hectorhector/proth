#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <time.h>

#include <gmp.h>

/* the real test */
//#define K_CONST 21181
//#define N_CONST 44200000

/* recent find (k=46157, n=698207)*/
//#define K_CONST 46157
//#define N_CONST 698206

/* searching for k=301, n=7360 */
#define K_CONST 301
#define N_CONST 6500

mpz_t t_exp;
mpz_t t_p1;
mpz_t t_p2;
mpz_t t_p3;
mpz_t t;

time_t start;
time_t end;

int main(void)
{
    time(&start);

    mpz_t exp;
    mpz_t p;
    mpz_t k;
    mpz_t base;

    mpz_init(p);

    mpz_init(k);
    mpz_init(exp);
    mpz_init(base);

    mpz_init(t_exp);
    mpz_init(t_p1);
    mpz_init(t_p2);
    mpz_init(t_p3);
    mpz_init(t);

    //first 3 primes
    mpz_set_ui(t_p1, 2);
    mpz_set_ui(t_p2, 3);
    mpz_set_ui(t_p3, 5);

    //proth number is k*2^n+1
    mpz_set_ui(k, K_CONST);

    //two is our base
    mpz_set_ui(base, 2);

    unsigned long int n = N_CONST;
    while (1)
    {
        printf("(n=%llu)\n", n);

        //calc 2^n
        mpz_pow_ui(exp, base, n);

        //p=k*2^n
        mpz_mul(p, k, exp);
        //p+=1
        mpz_add_ui(p, p, 1);

        //prime check exponent is (p-1)/2
        mpz_sub_ui(t_exp, p, 1);
        mpz_divexact_ui(t_exp, t_exp, 2);

        //printf("prime check a=2\n");
        mpz_powm(t, t_p1, t_exp, p);
        mpz_add_ui(t, t, 1);
        //printf("cmp1\n");
        if(mpz_cmp(t, p) == 0)
        {
            printf("prime with a=2!\n");
            break;
        }

        //printf("prime check a=3\n");
        mpz_powm(t, t_p2, t_exp, p);
        mpz_add_ui(t, t, 1);
        //printf("cmp2\n");
        if(mpz_cmp(t, p) == 0)
        {
            printf("prime with a=3!\n");
            break;
        }

        //printf("prime check a=5\n");
        mpz_powm(t, t_p3, t_exp, p);
        mpz_add_ui(t, t, 1);
        //printf("cmp3\n");
        if(mpz_cmp(t, p) == 0)
        {
            printf("prime with a=5!\n");
            break;
        }

        n++;
    }
    
    //proth number is k*2^n+1
    gmp_printf("%Zd*2^%llu+1 is prime!\n", k, n);

    //free
    mpz_clear(p);

    mpz_clear(k);
    mpz_clear(exp);
    mpz_clear(base);

    mpz_clear(t_exp);
    mpz_clear(t_p1);
    mpz_clear(t_p2);
    mpz_clear(t_p3);
    mpz_clear(t);

    time(&end);
    printf("total time: %f seconds\n", difftime(end, start));
}
