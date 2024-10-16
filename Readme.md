# proth


## background
Inspired by this Numberphile video:
https://www.youtube.com/watch?v=fcVjitaM3LY

This program uses the [GMP Library](https://gmplib.org/) to search for Proth Primes and help solve the Sierpiński problem.

Proth Primes are primes in the form of `k * 2^n + 1`.
A Sierpiński number is a number k where it is impossible to construct a Proth Prime.
The Sierpiński problem asks, "what is the smallest Sierpiński number?". Currently, the smallest **proven** Sierpiński number is 78557.

In the early 2000s, only 17 numbers smaller than 78557 hadn't been proven to NOT be Sierpiński numbers.
Currently, only 5 remain. 
If primes can be found for these 5 k's, then 78557 will be proven to be the smallest Sierpiński number.

The status of the 17 are as follows:

4847 -  prime with n=3321063, discovered October 15, 2005
5359 -  prime with n=5054502, discovered December 6, 2003
10223 - prime with n=31172165, discovered October 31, 2016 (latest discovery)
19249 - prime with n=13018586, discoverd March 26, 2007
21181 - unsolved
22699 - unsolved
24737 - unsolved
27653 - prime with n=9167433, discovered June 8, 2005
28433 - prime with n=7830457, discovered December 30, 2004
33661 - prime with n=7031232, discovered October 17, 2007
44131 - prime with n=995972, discovered December 5, 2002
46157 - prime with n=698207, discovered November 27, 2002
54767 - prime with n=1337287, discovered December 23, 2002
55459 - unsolved
65567 - prime with n=1013803, discovered December 2, 2002
67607 - unsolved
69109 - prime with n=1157446, discovered December 6, 2002

Also See:
http://www.prothsearch.com/sierp.html (The Sierpiński Problem: Definition and Status)
https://www.primegrid.com/forum_thread.php?id=1647 (Seventeen or Bust)


# status
As you may be able to tell from checking the current status of the Sierpiński problem, I was not able to find any new proth primes using this program.

I still had a lot of fun coding this and learning about GMP and primes though!

In the future I would like to make some optimaztions to the program and run it on some dedicated hardware. Who knows, I may still get lucky!

Possible future optimzations:
* Save the latest value of `2^n` so that we can just multiply it by 2 to get `2^(n+1)`, instead of re-calculating it by scratch.
* Use the Fermat primality test to only test probable primes.