#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[])
{
    if (argv[1] == 0) {
        printf("A file to seach through must be passed into this program.\n");
        printf("./find_high_read_depths.c <read_depth_file> <scaffold_average> <total_locations>\n");
        return 0;
    } else if (argv[2] == 0) {
        printf("The average for the read depth of this scaffold must be passed in.\n");
        printf("./find_high_read_depths.c <read_depth_file> <scaffold_average> <total_locations>\n");
        return 0;
    } else if (argv[3] == 0) {
        printf("The total number of locations for this scaffold must be passed in .\n");
        printf("./find_high_read_depths.c <read_depth_file> <scaffold_average> <total_locations>\n");
        return 0;
    } 
    char const* const file_name = argv[1]; 
    char *a = argv[2], *b = argv[3];
    double scaffold_average = atof(a);
    double total_locations = atof(b);

    char scaffold[60];
    int location = 0, read_depth = 0;
    double sum_squares = 0;
    double std_dev = 0;
    int num_below_significant = 11, sig_location_start = 0, sig_location_end = 0;

    FILE* file = fopen(file_name, "r");
    while (!feof(file)) {
        fscanf(file, "%s %d %d\n", scaffold, &location, &read_depth);
        sum_squares = sum_squares + ((read_depth - scaffold_average) * (read_depth - scaffold_average));
        //printf("scaffold: %s, location: %d, read_depth: %d, sums of squares: %f\n", scaffold, location, read_depth, sum_squares);
    }
    std_dev = sum_squares / total_locations;
    //printf("standard dev^2: %f\n", std_dev);
    std_dev = sqrtf(std_dev);
    //printf(" standard dev: %f\n", std_dev);
    fclose(file);
    FILE* file2 = fopen(file_name, "r");
    while (!feof(file2)) {
        fscanf(file, "%s %d %d\n", scaffold, &location, &read_depth);
        if (read_depth > scaffold_average + 5 * std_dev) {
            //printf("1scaffold: %s, location: %d, read_depth: %d, avg+stdev: %f\n", scaffold, location, read_depth, scaffold_average + std_dev);
            num_below_significant = 0;
            if (!sig_location_start) {
                sig_location_start = location;
            }
        } else if (num_below_significant < 10){
            //printf("2scaffold: %s, location: %d, read_depth: %d, avg+stdev: %f\n", scaffold, location, read_depth, scaffold_average + std_dev);
            num_below_significant++;
        } else if (num_below_significant == 10) {
            sig_location_end = location - 10;
            //printf("Region of significant read depth found! Locations: %d - %d | width: %d\n", sig_location_start, sig_location_end, sig_location_end - sig_location_start);
            printf("%s\t%d\t%d\n", scaffold, sig_location_start, sig_location_end);
            num_below_significant = 11;
            sig_location_start = 0;
            sig_location_end = 0;
        }

    }
    fclose(file2);

    return 0;
}