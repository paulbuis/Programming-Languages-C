# Programming-Languages-C
Intro exercises in C for BSU Programming Languages Course

##Kata 0 - Say something

### Level 0: Just say "Hello"

```C
#include <stdio.h>

int main(int argc, char** argv) {
    printf("Hello World\n");
    return 0;
}
```

This example shows the basic structure of a C program. Declarations of functions and types in the "standard I/O" library are made available to the compiler via the `#include` pre-processor directive.

The program begins in the function named `main` which, by convention, returns an integer exit status, with 0 indicating a normal exit.

The [`printf`](http://www.tutorialspoint.com/c_standard_library/c_function_printf.htm) function is given a string literal ending in a "newline" character indicated by the "escape sequence" of `\n`


    gcc -o kata0 kata0-0.c
    ./kata0-0

Use the above gcc command line to compile and link the kata0-0.c source file, creating a new kata0-0 executable.
To run an executable located in the current directory in a standard Linux system, prefix the name of the executable with ./


### Level 1: Print the time of day

```C
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv) {
    time_t t;
    struct tm timeDateStruct;
    char timeDateString[128];
    int timeDateStringSize;
    time(&t);
    timeDateStruct = *localtime(&t);
    timeDateStringSize = 
        strftime(timeDateString, 128, "%FT%T%z", &timeDateStruct); 
    printf("ISO 8601 date/time is %s\n", timeDateString);
    return 0;
}
```

This example is much more involved. The [`time.h`](http://www.tutorialspoint.com/c_standard_library/time_h.htm) header file includes definitions of the types `time_t` and `struct tm` as well as the functions `time()`,`localtime()` and `strftime()`

`time()` is given the address of `t` and modifies the value of `t` to hold the number of seconds since the beginning of the epoch (January 1, 1970).

`localtime()` is also given the address of `t` but does not modify it. It returns a `struct tm` describing the equivalent point in time expressed as separate values for year, month, day, hour, minutes, and seconds in the local timezone.

`strftime()` formats the data as a string given a formatting pattern. The formatting pattern chosen here represents the applicable ISO standard.

`printf()` is using the `%s` formatting directive to print out a string.

## Kata 1: Compute the average of 3 numbers using console I/O

```C
#include <stdio.h>

double average(int, int, int);
int read(int*, int*, int*);

int main(int argc, char** argv) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) == 3) {
        printf("Average: %f\n", average(a, b, c));
    }
    else {
        printf("Error reading input values");
    }
    return 0;
}

double average(int x, int y, int z) {
    return (x+y+z)/3.0;
}

int read(int *px, int *py, int* pz) {
    int scanCount = scanf("%d", px);
    if (scanCount != 1) return 0;
    scanCount = scanf("%d", py);
    if (scanCount != 1) return 1;
    scanCount = scanf("%d", pz);
    if (scanCount != 1) return 2;
    return 3;
}
```

Here we see how to write functions in the same file as `main()`. Functions must be declared before they are used. Here we insert the function declarations as "prototypes" before `main()` and the function definitions after `main()`. It is also legal to have the function definitions also serve as function declarations by locating them in the file before their first use.

The `scanf()` function, like the `printf()` function is "[varadic](https://en.wikipedia.org/wiki/Variadic_function)," meaning it takes a variable number of arguments. Both of them use the same set of [formatting directives](https://en.wikipedia.org/wiki/Printf_format_string). Here, we read in three integers in decimal format from standard input and write out a floating point number to standard outuput. Since `scanf()` must modify values, it is given the addresses of the variables it needs to modify. `scanf()` prints out the number of values it read in, which should be 3 in this case. C library functions normally return status information which needs to be checked.

The function `average()` illustrates "mixed mode" arithmetic where the type of the sum is automatically "promoted" to the type `double` which is the type of the numeric literal `3.0`

The `read()` function could theoretically be used instead of the call to `scanf()` in `main()`. Depending on the implementation of the I/O library, even having a function with the name `read` could be a problem. Under the hood, `scanf()` will indirectly call an OS function which is also called `read`. C does not allow two functions with the same name in the same program (function name "overloading"). Languages like C++ and Java do allow function overloading and distinguish between same-name functions based on the number and type of their arguments. The GNU C compiler (GCC) and its standard library "GlibC" are structured to avoid this problem for this particular function name.

## Kata 2: Finding Average of Arbitrary Size Sequence of Integers

### Level 0: Using a growing array with indices

#### Main Program Source Code

```C
#include <stdio.h>
#include "intseq.h"

struct intSeq readInts();
double average(struct intSeq);

int main(int argc, char** argv) {
    struct intSeq seq = readInts();

    double a = average(seq);
    printf("Average: %f\n", average(seq));

    return 0;
}

struct intSeq readInts() {
    struct intSeq seq = newIntSeq();
    int count = 0;
    int value;
    char buffer[128];
    while (fgets(buffer, 128, stdin) != NULL) {
        if (sscanf(buffer, "%d", &value) != 1) {
            break;
        }
        intSeqAdd(&seq, value);
    }
    return seq;
}

double average(struct intSeq seq) {
    int index;
    int sum = 0;
    for (index = 0; index < seq.length; index++) {
        sum += seq.data[index];
    }
    return ((double)sum)/seq.length;
}
```



#### intseq.h Header File

```C
struct intSeq {
    int length;
    int capacity;
    int* data;
};

extern struct intSeq newIntSeq();

extern void intSeqAdd(struct intSeq* pis, int newValue);
```



#### intseq.c Separately Compiled Source File
```C
#include <stdlib.h>
#include "intseq.h"

struct intSeq newIntSeq() {
    struct intSeq seq;
    seq.length = 0;
    seq.capacity = 4;
    seq.data = (int*)malloc(4*sizeof(int));
    return seq;
}

void intSeqAdd(struct intSeq* pis, int newValue) {
    int* newData;
    int index;
    if (pis->length == pis->capacity - 1) {
        newData = (int*)malloc(2 * pis->capacity * sizeof(int));
        pis->capacity *= 2;
        for (index = 0; index < pis->length; index++) {
            newData[index] = pis->data[index];
        }
        free(pis->data);
        pis->data = newData;
    }

    pis->data[pis->length++] = newValue;
}
```

Here we use the standard technique of growing an [dynamic array](https://en.wikipedia.org/wiki/Dynamic_array) by exponentially increasing the capacity. This gives worst case performance of O(N) since the array ocassionally needs to be copied. However, on average it takes only constant time as can be shown with [amortized analysis](https://en.wikipedia.org/wiki/Amortized_analysis). Memory is allocated off the [heap](https://en.wikipedia.org/wiki/Memory_management) with [malloc](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation) and returned to the heap for recycling with free. C does not support [Garbage Collection](https://en.wikipedia.org/wiki/Garbage_collection_(computer_science)) or [Automatic Reference Counting](https://en.wikipedia.org/wiki/Automatic_Reference_Counting) leading to many memory management errors in C programs.

For faster copying of large chunks of contiguous data, the loop can be replaced with the line

```C
        memcpy(newData, pis->data, pis->length*sizeof(int));
```

Using `memcpy()` would also require a `#include <string.h>` directive at the beginning of the file. [memcpy](http://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm) is typically implemented in assembly language to optimize for pointer alignment and the optimum number of bytes to move per instruction. On a 64-bit machine, for example, it might be faster to move 8 byte chunks of data than smaller chunks.

#### Makefile

```
CC=gcc
CCFLAGS=-O3

all: kata2-0 kata2-1

kata2-0: kata2-0.o intseq.o
	$(CC) $(CCFLAGS) kata2-0.o intseq.o -o kata2-0

intseq.o: intseq.c intseq.h
kata2-0.o: kata2-0.c intseq.h

clean:
	rm -f kata2-0 *.o
```

### Level 1: Using a growing array with pointers

Replace the `average()` function from the Level 0 version of this kata with:

```C
double average(struct intSeq seq) {
    int sum = 0;
    int *p = seq.data;
    int *pEnd = seq.data + seq.length;
    while  (p < pEnd) {
        sum += *p;
        p++;
    }
    return ((double)sum)/seq.length;
}
```

Note that the syntax `a[i]` is "syntactic sugar" for `*(a+i)` since arrays are represented by a pointer to their start. Pointer addition is automatically scaled by the size of the array elements. This code does pointer arithmetic and pointer comparison. Note that since arrays do not know their own length in C, there is no way for the compiler to automatically do bounds checking on the index. If the C code were not run through an optimizer, this code might be marginally faster than the code using indexed arrays. An optimizer would probably also unroll and vectorize the loop generating inhumanly complex code.

## Kata 3: Factiorial Function

### Level 0: Recursive Implementation

```C
#include <stdio.h>

double factorial(unsigned int n) {
    if (n == 0) {
       return 1.0;
    }
    return n*factorial(n-1);
}


int main(int argc, char** argv) {
    printf(" 10!= %20g\n", factorial(10));
    printf(" 20!= %20g\n", factorial(20));
    printf(" 40!= %20g\n", factorial(40));
    printf(" 80!= %20g\n", factorial(80));
    printf("160!= %20g\n", factorial(160));
    printf("200!= %20g\n", factorial(200));
    return 0;
}
```

### Level 1: Non-recursive Implementation

```C
#include <stdio.h>

double factorial(unsigned int n) {
    double result = n;
    while (n > 1) {
        result *= --n;
    }
    return result;
}


int main(int argc, char** argv) {
    printf(" 10!= %20g\n", factorial(10));
    printf(" 20!= %20g\n", factorial(20));
    printf(" 40!= %20g\n", factorial(40));
    printf(" 80!= %20g\n", factorial(80));
    printf("160!= %20g\n", factorial(160));
    printf("200!= %20g\n", factorial(200));
    return 0;
}
```

As in many languages that imitate C, the syntax `a *= b` is simply shorthand for `a = a * b`

Note carefully that `--n` ("pre-decrement:" decrement, then use decremented value) is very different than `n--` ("post decrement:" use undecremented value, then decrement). To avoid confusion, I normally only use the increment/decrement operators when they are isolated, not as part of a more complex expression.

## Kata 2: Fibonacci Function

### Level 0: Recursive Implementation

```C
#include <stdio.h>

long unsigned fib(unsigned int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n-1) + fib(n-2);
}


int main(int argc, char** argv) {
    printf("fib( 0)= %12lu\n", fib(0));
    printf("fib( 1)= %12lu\n", fib(1));
    printf("fib( 2)= %12lu\n", fib(2));
    printf("fib( 3)= %12lu\n", fib(3));
    printf("fib( 4)= %12lu\n", fib(4));
    printf("fib( 5)= %12lu\n", fib(5));
    printf("fib(10)= %12lu\n", fib(10));
    printf("fib(30)= %12lu\n", fib(30));
    printf("fib(40)= %12lu\n", fib(40));
    printf("fib(50)= %12lu\n", fib(50));
    return 0;
}
```
### Level 1: Non-Recursive Implementation

```C
#include <stdio.h>

long unsigned fib(unsigned int n) {
    long unsigned a = 0;
    long unsigned b = 1;
    long unsigned t;
    unsigned int i;
    if (n <= 1) {
        return n;
    }
    for (i=0; i<n; i++) {
	t = a;
        a = b;
	b += t;
    }
   
    return a;
}


int main(int argc, char** argv) {
    printf("fib( 0)= %20lu\n", fib(0));
    printf("fib( 1)= %20lu\n", fib(1));
    printf("fib( 2)= %20lu\n", fib(2));
    printf("fib( 3)= %20lu\n", fib(3));
    printf("fib( 4)= %20lu\n", fib(4));
    printf("fib( 5)= %20lu\n", fib(5));
    printf("fib(10)= %20lu\n", fib(10));
    printf("fib(30)= %20lu\n", fib(30));
    printf("fib(40)= %20lu\n", fib(40));
    printf("fib(50)= %20lu\n", fib(50));

    printf("fib(90)= %20lu\n", fib(90));
    printf("fib(93)= %20lu\n", fib(93));
    printf("fib(94)= %20lu\n", fib(94));

   
    return 0;
}
