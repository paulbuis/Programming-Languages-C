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
