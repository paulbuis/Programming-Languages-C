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

The `printf` function is given a string literal ending in a "newline" character indicated by the "escape sequence" of `\n`

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

This example is much more involved. The `time.h` header file includes definitions of the types `time_t` and `struct tm` as well as the functions `time()`,`localtime()` and `strftime()`

`time()` is given the address of `t` and modifies the value of `t` to hold the number of seconds since the beginning of the epoch (January 1, 1970).

`localtime()` is also given the address of `t` but does not modify it. It returns a `struct tm` describing the equivalent point in time expressed as separate values for year, month, day, hour, minutes, and seconds in the local timezone.

`strftime()` formats the data as a string given a formatting pattern. The formatting pattern chosen here represents the applicable ISO standard.

`printf()` is using the `%s` formatting directive to print out a string.

