#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <gmp.h>

#define NUM_DIGITS 1024

void mpz_mper(mpz_t num);

bool inc_mper(char *num);

char tmp_buf[NUM_DIGITS] = "";

uint64_t count = 0;
uint64_t best_count = 0;

uint64_t digit_best_count = 0; //what the best is
mpz_t digit_count; //how many times we've hit the best

clock_t start;

int main(void)
{
    char guess[NUM_DIGITS] = "01";
    mpz_t ans;
    mpz_init(ans);
    mpz_init(digit_count);

    start = clock();

    do
    {
        count = 0;
        mpz_set_str(ans, guess, 10);

        while(mpz_cmp_ui(ans, 9) > 0)
        {
            mpz_mper(ans);
            ++count;
        }

        if(count > best_count)
        {
            clock_t found = clock();
            double time_spent = (double)(found - start) / CLOCKS_PER_SEC;
            best_count = count;
            printf("(%f)\t%lu steps: %s  <------\n", time_spent, count, guess);
        }

        if (count > digit_best_count)
        {
            digit_best_count = count;
            mpz_set_ui(digit_count, 1);
        }
        else if(count == digit_best_count)
        {
            mpz_add_ui(digit_count, digit_count, 1);
        }
    }while(inc_mper(guess));
}

void mpz_mper(mpz_t num)
{
    int sz = gmp_snprintf(tmp_buf, NUM_DIGITS, "%Zd", num);

    if(sz >= NUM_DIGITS)
    {
        printf("\n=== can't fit num in tmp_buf! ===\n\n");
        return;
    }

    mpz_set_ui(num, 1);

    uint_fast16_t i = 0;
    while(tmp_buf[i] != '\0')
    {
        mpz_mul_ui(num, num, tmp_buf[i] - 0x30);
        ++i; 
    }
}


bool inc_mper(char *num)
{
    uint_fast16_t i = 0;

    while(num[i] == '9')
    {
        ++i;

        if(i >= NUM_DIGITS)
        {
            printf("\n=== ran out of digits ===\n\n");
            return false;
        }
    }

    if(num[i] == '\0')
    {
        clock_t found = clock();
        double time_spent = (double)(found - start) / CLOCKS_PER_SEC;
        //printf("(%f)\t%lu digits best: %u\n", time_spent, i+1, best_count);
        
        gmp_printf("(%f) finished %lu digits. %Zd nums with count: %lu\n", time_spent, i, digit_count, digit_best_count); 
        mpz_set_ui(digit_count, 0);
        digit_best_count = 0;

        num[i] = '1';
    }

    char new_num = ++num[i];
    while(i)
    {
        --i;
        num[i] = new_num;
    }

    return true;
}
