#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char const* const fileName = argv[1];
    if (fileName == 0) {
	printf("A file must be passed into this program\n");
    printf("./GC_per_X.out <fasta_file> <chunk_size>\n");
    	return 0;
    }
    char const* const chunk_size = argv[2];
    if (chunk_size == 0) {
        printf("A chunk size must be passed into this program\n");
        printf("./GC_per_X.out <fasta_file> <chunk_size>\n");
        return 0;
    }

    long int chunk_val = strtol(chunk_size, NULL, 10);
    char read[600];
    int count = 0;
    FILE* file = fopen(fileName, "r");
    int site_index;
    int count_a = 0, count_t = 0, count_c = 0, count_g = 0, chunk_num = 1;
while (!feof(file)) {
    fscanf(file, "%s\n", read);
    site_index = 0;
    while(read[site_index] != '\0') {
        if(count == chunk_val) {
           printf("Chunk num: %d A: %d T: %d C: %d G:%d\n", chunk_num, count_a, count_t, count_c, count_g);
           printf("Chunk: %d GC content: %f\n", chunk_num, (((float)count_c + (float)count_g) / (float)count) * 100);
           count = 0;
           count_a = 0;
           count_t = 0;
           count_c = 0;
           count_g = 0;
           chunk_num++;
        }
        char site = read[site_index];
        if (site == 'A') {
            count_a++;
            count++;
        } else if (site == 'T') {
            count_t++;
            count++;
        } else if (site == 'C') {
            count_c++;
            count++;
        } else if (site == 'G') {
            count_g++;
            count++;
        } else {
          // Do Nothing
        }
        site_index++;
    }
}
    printf("Total size of final chunk: %d. Chunk num: %d A: %d T: %d C: %d G:%d\n", count, chunk_num, count_a, count_t, count_c, count_g);
    printf("Chunk: %d GC content: %f\n", chunk_num, (((float)count_c + (float)count_g) / (float)count) * 100);

    fclose(file);
    return 0;
}
