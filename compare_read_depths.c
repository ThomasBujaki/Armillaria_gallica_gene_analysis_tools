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
    char old_scaffold[60] = "scaffold_1";
    char location_r[60], location_c[60];
    char read_depth_r[60], read_depth_c[60];
    int prev_same_scaffold_val = 1;
    int count = 1;
    FILE* r_file = fopen(ref_file, "r");
    FILE* c_file = fopen(comp_file, "r");
    if (!feof(r_file) && !feof(c_file)) {
        fscanf(r_file, "%s %s %s", scaffold_r, location_r, read_depth_r);
        fscanf(c_file, "%s %s %s", scaffold_c, location_c, read_depth_c);
    }
    

    while (!feof(r_file) && !feof(c_file)) {
        // iterate over the lines of a file and look for the locations that match up, 
        // if one file ends before the other one keep the loop going so that I capture all the positions possible
        // if one is ahead of the other then do not do the next fscanf until they are equal of the other is above the first one
        int reference_read_depth = atoi(read_depth_r);
        int comparison_read_depth = atoi(read_depth_c);
        int compare_loc = atoi(location_c);
        int reference_loc = atoi(location_r);
        int same_scaffold = !strcmp(scaffold_c, scaffold_r);
        
        if ((reference_loc == compare_loc) && same_scaffold) {
            printf("read depth at %s, location %d / %d: %d\n", scaffold_c, compare_loc, reference_loc, reference_read_depth - comparison_read_depth);
            fscanf(r_file, "%s %s %s", scaffold_r, location_r, read_depth_r);
            fscanf(c_file, "%s %s %s", scaffold_c, location_c, read_depth_c);
            count++;

        } else if ((reference_loc > count && same_scaffold) && (compare_loc > count && same_scaffold)) {
            printf("read depth at %s, location %d / %d: %d\n", scaffold_c, count, count, 0);
            count++;
        } else if (reference_loc < compare_loc && same_scaffold) {
            //printf("refenece ahead of compairison\n");
            printf("read depth at %s, location %d / %d: %d\n", scaffold_r, count, reference_loc, reference_read_depth);
            fscanf(r_file, "%s %s %s", scaffold_r, location_r, read_depth_r);
            count++;
        } else if (reference_loc > compare_loc && same_scaffold) {
            //printf("compairison ahead of refenece\n");
            printf("read depth at %s, location %d / %d: %d\n", scaffold_c, compare_loc, count, -comparison_read_depth);
            fscanf(c_file, "%s %s %s", scaffold_c, location_c, read_depth_c);
            count++;
        } else if (reference_loc > compare_loc && !same_scaffold) {
            //printf("same_scaffold: %d, refernece_loc: %d, compare_loc: %d.\n", same_scaffold, reference_loc, compare_loc);
            printf("read depth at %s, location %d / %d: %d\n", scaffold_r, reference_loc, count, reference_read_depth);
            fscanf(r_file, "%s %s %s", scaffold_r, location_r, read_depth_r);
            count++;
        } else if (reference_loc < compare_loc && !same_scaffold) {
            //printf("same_scaffold: %d, refernece_loc: %d, compare_loc: %d.\n", same_scaffold, reference_loc, compare_loc);
            printf("read depth at %s, location %d / %d: %d\n", scaffold_c, count, compare_loc, -comparison_read_depth);
            fscanf(c_file, "%s %s %s", scaffold_c, location_c, read_depth_c);
            count++;
        } else {
            printf("unexpected case, printing all current information, same_scaffold: %d, refernece_loc: %d, compare_loc: %d.\n", same_scaffold, reference_loc, compare_loc);
            return 0;
        }

        if (prev_same_scaffold_val != same_scaffold && same_scaffold) {
            //printf("new scaffold\n");
            count = 1;
        } else if (strcmp(old_scaffold, scaffold_r) && strcmp(old_scaffold, scaffold_c)) {
            //printf("new %s %s\n", old_scaffold, scaffold_r);
            strcpy(old_scaffold, scaffold_r);
            //printf("new %s %s\n", old_scaffold, scaffold_r);
            count = 1;
        }
        prev_same_scaffold_val = same_scaffold;

    }

    fclose(r_file);
    fclose(c_file);
    return 0;

}