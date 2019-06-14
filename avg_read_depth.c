#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

long double get_avg(long double prev_avg, int x, int n){
    return (prev_avg * n + x) / (n + 1);
}


int main(int argc, char* argv[])
{
    char const* const fileName = argv[1]; 
    if (argv[1] == 0) {
	printf("A file must be passed into this program\n");
    	return 0;
    } else if (argv[2] == 0) {
	printf("please pass in the scaffold to be searched\n");
	return 0;
    } 

    char *search_scaffold = argv[2];
    long int scaffold = 0, location = 0, read_depth = 0, count = 0;
    long double avg_read_depth = 0, prev_avg = 0;
    FILE* file = fopen(fileName, "r"); 
    while (!feof(file)) { 
        fscanf(file, "%s %ld %ld", &scaffold, &location, &read_depth);    
	if (!strcmp((char*)&scaffold, search_scaffold)) {
	    avg_read_depth = get_avg(avg_read_depth, read_depth, count);
	    count += 1;
	} 

    } 
    printf("scaffold: %s, count: %d, total avg read depth: %Lf\n", search_scaffold, count, avg_read_depth);
    fclose(file);
    
    return 0;
}
