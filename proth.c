#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <gmp.h>


bool is_prime(mpz_t p);
bool is_prime2(mpz_t p);

clock_t start;


//ints for is_prime test
mpz_t t_exp;
mpz_t t_p1;
mpz_t t_p2;
mpz_t t_p3;
mpz_t t;


int main(void)
{
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

    //start = clock();


    //proth number is k*2^n+1
    //check where k is 19
    mpz_set_ui(k, 46157);

    //calc 2^n
    mpz_set_ui(base, 2);

    for(unsigned long int n = 698200; ; n++)
    {
        mpz_pow_ui(exp, base, n);

        //p=k*2^n
        mpz_mul(p, k, exp);
        //p+=1
        mpz_add_ui(p, p, 1);

        gmp_printf("(n=%d)\n%Zd\n\n", n, p);
        if(is_prime2(p) == true)
        {
            printf(" <--- prime\n");
            return 1;
        }
        printf("\n");
    }
    
    //free p
    mpz_clear(p);
}

bool is_prime(mpz_t p)
{
    //exponent is (p-1)/2
    //printf("exp\n");
    mpz_sub_ui(t_exp, p, 1);
    mpz_divexact_ui(t_exp, t_exp, 2);
    unsigned long int ui_exp = mpz_get_ui(t_exp);

    //printf("pow1\n");
    mpz_pow_ui(t, t_p1, ui_exp);
    mpz_add_ui(t, t, 1);
    //printf("div1\n");
    if(mpz_divisible_p(t, p) != 0)
        return true;

    //printf("pow2\n");
    mpz_pow_ui(t, t_p2, ui_exp);
    mpz_add_ui(t, t, 1);
    //printf("div2\n");
    if(mpz_divisible_p(t, p) != 0)
        return true;

    //printf("pow3\n");
    mpz_pow_ui(t, t_p3, ui_exp);
    mpz_add_ui(t, t, 1);
    //printf("div3\n");
    if(mpz_divisible_p(t, p) != 0)
        return true;

    return false;
}

bool is_prime2(mpz_t p)
{
    //exponent is (p-1)/2
    printf("exp\n");
    mpz_sub_ui(t_exp, p, 1);
    mpz_divexact_ui(t_exp, t_exp, 2);

    printf("pow1\n");
    mpz_powm(t, t_p1, t_exp, p);
    mpz_add_ui(t, t, 1);
    printf("cmp1\n");
    if(mpz_cmp(t, p) == 0)
        return true;

    printf("pow2\n");
    mpz_powm(t, t_p2, t_exp, p);
    mpz_add_ui(t, t, 1);
    printf("cmp2\n");
    if(mpz_cmp(t, p) == 0)
        return true;

    printf("pow3\n");
    mpz_powm(t, t_p3, t_exp, p);
    mpz_add_ui(t, t, 1);
    printf("cmp3\n");
    if(mpz_cmp(t, p) == 0)
        return true;

    return false;
}
