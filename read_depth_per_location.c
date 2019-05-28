#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char const* const fileName = argv[1]; 
    if (argv[1] == 0){
	printf("A file must be passed into this program\n");
    	return 0;
    } else if (argv[2] == 0) {
	printf("please pass in the scaffold to be searched\n");
	return 0;
    } else if (argv[3] == 0) {
	printf("please pass in the starting position of the search\n");
	return 0;
    } else if (argv[4] == 0) {
	printf("please pass in the ending position of the search\n");
	return 0;
    } 
    char *search_scaffold = argv[2];
    char *a = argv[3], *b = argv[4];
    int start_position = strtol(a, &a, 10);
    int end_position = strtol(b, &b, 10);

    long int scaffold = 0, location = 0, read_depth = 0;
    int graph_range_start = start_position > 500 ? start_position - 500 : 1;
    int graph_range_end = end_position + 500;
    int graph_range_index = graph_range_end - graph_range_start ;
    int read_depth_values[graph_range_end - graph_range_start];
    
    FILE* file = fopen(fileName, "r"); 
    while (!feof(file)) { 
        fscanf(file, "%s %d %d", &scaffold, &location, &read_depth);    
	if (!strcmp((char*)&scaffold, search_scaffold) && location == graph_range_end - graph_range_index) {
	    read_depth_values[graph_range_end - graph_range_start - graph_range_index] = read_depth;
	    printf("scaffold: %s\t location: %d\t arr val: %d\t read depth: %d\n", &scaffold, graph_range_end - graph_range_index, graph_range_end - graph_range_start - graph_range_index, read_depth_values[graph_range_end - graph_range_start - graph_range_index]);
	    graph_range_index -= 1;
	    if (graph_range_index < 0){
		break;
	    }
	} else if (!strcmp((char*)&scaffold, search_scaffold) && location >= graph_range_end - graph_range_index) {
	    while (location >= graph_range_end - graph_range_index) {
		if (location == graph_range_end - graph_range_index) {
		    read_depth_values[graph_range_end - graph_range_start - graph_range_index] = read_depth;
		} else {
		    read_depth_values[graph_range_end - graph_range_start - graph_range_index] = 0;
		}
		printf("scaffold: %s\t location: %d\t arr val: %d\t read depth: %d\n", &scaffold, graph_range_end - graph_range_index, graph_range_end - graph_range_start - graph_range_index, read_depth_values[graph_range_end - graph_range_start - graph_range_index]);
		graph_range_index -= 1;
    		if (graph_range_index < 0){
		    break;
		}
	    }
    	}
    	if (graph_range_index < 0){
	    break;
	}
    } 
    
	// just do search for graph_range_start value now, if it does not exist set the read_depth value to 0, if it does then start counting up from there in the file to the graph_range_end value, save these values to an array	
    
    fclose(file);
    
    return 0;
}
