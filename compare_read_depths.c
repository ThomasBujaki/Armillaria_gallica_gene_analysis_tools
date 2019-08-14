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
    int const line_num = 0;
    char const* const ref_file = argv[1];
    char const* const comp_file = argv[2];
    char scaffold_r[60], scaffold_c[60];
    char location_r[60], location_c[60];
    char read_depth_r[60], read_depth_c[60];

    FILE* r_file = fopen(ref_file, "r");
    FILE* c_file = fopen(comp_file, "r");

    while (!feof(r_file) && !feof(c_file)) {
        fscanf(r_file, "%s %s %s", scaffold_r, location_r, read_depth_r);
        fscanf(c_file, "%s %s %s", scaffold_c, location_c, read_depth_c);
        // printf("%s %s %s\n", scaffold_r, location_r, read_depth_r);
        // printf("%s %s %s\n", scaffold_c, location_c, read_depth_c);
        int reference_read_depth = atoi(read_depth_r);
        int comparison_read_depth = atoi(read_depth_c);
        if (abs(reference_read_depth - comparison_read_depth) > 100) {
            printf("read depth difference at location %d/%d: %d\n", atoi(location_c), atoi(location_r), reference_read_depth - comparison_read_depth);
        }
    }

    fclose(r_file);
    fclose(c_file);
    return 0;

}