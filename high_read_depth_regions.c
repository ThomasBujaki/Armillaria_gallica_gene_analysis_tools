#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argv[1] == 0) {
        printf("The reference file must be passed into this program.\n");
        printf("./compare_read_depths.out <reference_file> <compairison_file>.\n");
        return 0;
    } else if (argv[2] == 0) {
        printf("A compairison file must be passed into this program.\n");
        printf("./compare_read_depths.out <reference_file> <compairison_file>.\n");
        return 0;
    }