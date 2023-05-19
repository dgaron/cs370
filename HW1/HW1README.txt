README
======

Initiator.c
  It is responsible for:
  1. Setting the seed, whose value is passed as an argument, using srand().
  2. Invoking functions in the Worker.
Worker.h
  It is responsible for implementing the following:
  1. Dynamically allocate and de-allocate a random sized array for each iteration.
  2. Populate elements in the array with random integers.
  3. For each iteration, generate a random integer to be used as a divisor.
  4. For each element in the array, check if the element is divisible, and if so count it.
  5. Calculate the ratio of elements divisible by divisor to elements not divisible by the divisor.
    ---- Number of Divisible Elements /Number of Non-Divisble Elements ----
  6. At the end print the iteration number with maximum number of divisible elements.
  7. Return the average value of the ratio divisible/not_divisible for all iterations to Initiator
Worker.c
  Contains the definitions for the functions declared in Worker.h

C. Answer the following questions (1 point each, select/type the right answer).

  1. What is the main difference between Malloc() and Calloc()?
	Malloc dynamically allocates memory and accepts one parameter.
	Calloc dynamically allocates memory and initializes all bits to 0. It accepts two parameters.

  2. When dynamically allocating an integer array, Malloc takes the number of elements as the input? –     True/False
	False: Malloc takes the size of memory to allocate as an input.

  3. What happens if memory is not properly freed after using dynamic memory allocation?
	The memory will be held and other processes will be unable to use it. The amount of memory avaialable to the 
	system is reduced for no purpose.

  4. What is the purpose of the headerfile Worker.h and Why is Initiator.h not necessary?
	In order to invoke a function in C, the function must first be declared. By providing the
	function declaration without the body (also known as a function prototype) at the top of the
	program, any function may be invoked from anywhere.

	These function declarations are often placed into their own .h file which is inserted using an
	#include directive thereby allowing access to those functions. The functions are then defined
	in the corresponding .c file.

	Initiator.h is not necessary because Initiator.c has only one function: main.

  5. Describe the * and & operators in the context of pointers and references?
	* is the dereference operator. It means "the value at the address contained by this pointer".
	& is the address operator. It means "the address of this variable".
		In C++, when used in an assignment, the variable declared will effectively be an alias
		for the object assigned.
		e.g., 	int num1 = 5;
			int& num1Alias = num1;
			num1Alias += 1;  // Now num1 == 6


VALGRIND OUTPUT: 

charleston:~/cs370$ valgrind Initiator 7
==1433704== Memcheck, a memory error detector
==1433704== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1433704== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==1433704== Command: Initiator 7
==1433704== 
[Initiator]: With seed: 7
[Worker]: Number of iterations is: 77
[Worker]: Iteration with maximum fully divisible elements is 59
[Initiator]: Running ratio: 0.122461
==1433704== 
==1433704== HEAP SUMMARY:
==1433704==     in use at exit: 0 bytes in 0 blocks
==1433704==   total heap usage: 78 allocs, 78 frees, 38,872 bytes allocated
==1433704== 
==1433704== All heap blocks were freed -- no leaks are possible
==1433704== 
==1433704== For lists of detected and suppressed errors, rerun with: -s
==1433704== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
charleston:~/cs370$ vim Worker.c
charleston:~/cs370$ make
gcc -g -Wall -o Initiator Initiator.c Worker.c
charleston:~/cs370$ valgrind Initiator 7
==1433837== Memcheck, a memory error detector
==1433837== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1433837== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==1433837== Command: Initiator 7
==1433837== 
[Initiator]: With seed: 7
[Worker]: Number of iterations is: 77
[Worker]: Iteration with maximum fully divisible elements is 59
[Initiator]: Running ratio: 0.122461
==1433837== 
==1433837== HEAP SUMMARY:
==1433837==     in use at exit: 37,848 bytes in 77 blocks
==1433837==   total heap usage: 78 allocs, 1 frees, 38,872 bytes allocated
==1433837== 
==1433837== LEAK SUMMARY:
==1433837==    definitely lost: 37,848 bytes in 77 blocks
==1433837==    indirectly lost: 0 bytes in 0 blocks
==1433837==      possibly lost: 0 bytes in 0 blocks
==1433837==    still reachable: 0 bytes in 0 blocks
==1433837==         suppressed: 0 bytes in 0 blocks
==1433837== Rerun with --leak-check=full to see details of leaked memory
==1433837== 
==1433837== For lists of detected and suppressed errors, rerun with: -s
==1433837== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
