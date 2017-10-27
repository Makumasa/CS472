"make" or "make all" will build all the programs for this homework.

"make" followed by the name of the program will build just that program.

The program "my_frexp" is the solution to Part 1. It runs both frexp() and my
version of frexp on a series of test values (many of which are edge cases) and
prints their output side by side.

The program "ops_test" is used to show the validity of the software floating
point operations written for Part 2. It takes in two doubles as command line
arguments ,runs my software floating point operations with these two values
as operands, and prints the results. These software floating point functions 
do not properly handle denormalized values.

The program "ops_timing" runs both the regular floating point operations and the
software ones implemented by me a huge number of times and calculates the number
of nanoseconds required to run each using getrusage(). 

The program "interpret_64" is the solution to Part 3. It generates a random 
64-bit value using the Mersenne Twister and interprets these bits as a double,
as a long, and as 8 characters and prints the results.
