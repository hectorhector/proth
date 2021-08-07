#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <gmp.h>



int main(void)
{
    mpz_t p;
    mpz_t exp;
    mpz_t base;
    mpz_t rop;

    mpz_init(p);
    mpz_init(exp);
    mpz_init(base);
    mpz_init(rop);

    mpz_set_ui(base, 5);
    mpz_set_ui(exp, (13-1)/2);
    mpz_set_ui(p, 13);

    mpz_powm(rop, base, exp, p);

    gmp_printf("%Zd\n", rop);

    mpz_clear(p);
    mpz_clear(exp);
    mpz_clear(base);
    mpz_clear(rop);
}
