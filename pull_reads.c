#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fill_aligned_sites(char *token, int *aligned_sites, int  sum_len, int m_or_s){
    printf("sum_len %d\n", sum_len);
    int token_iter = 0;
    int strtol_val = strtol(token, &token, 10);
    printf("strtol_val: %d\n", strtol_val);
    for (token_iter = sum_len; token_iter < (strtol_val + sum_len); token_iter++){
	if (m_or_s == 77){
	    aligned_sites[token_iter] = 1;
	    printf("sum_len %d\t token_iter %d\n", sum_len, token_iter);
	    printf("aligned_sites: %d\n", aligned_sites[token_iter]);
        } 
	else if (m_or_s == 83){
	    aligned_sites[token_iter] = 0;
	    printf("sum_len %d\t token_iter %d\n", sum_len, token_iter);
	    printf("aligned_sites: %d\n", aligned_sites[token_iter]);
	}
    }
    printf("sum_len %d\t token_iter %d\n", sum_len, token_iter);
    sum_len = token_iter;
    printf("sum_len %d\t token_iter %d\n", sum_len, token_iter);

    return sum_len;
}

int parse_cigar(char *cigar, int *aligned_sites) {
    printf("%s\n", cigar);

    int cig_len = strlen(cigar);
    printf("cigar len: %d\n", cig_len);
    char *token;
    int sum_len = 0;
    int cig_index = 1;
    int split_flag = 0;
    for (cig_index = 0; cig_index < cig_len; cig_index++){
	printf("cigar char: %s\n", &cigar[cig_index]);
	if (cigar[cig_index] == 77){ // 77 = M
	    printf("splitting by M\n"); 
	    if (!split_flag) {
	        token = strtok(cigar, "M");
		split_flag=1;
		sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 77);
	    } else {
	        token = strtok(NULL, "M");
		sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 77);
	    }
	    printf("token: %s\n", token);
	} else if (cigar[cig_index] == 83) { // 83 = S
	    printf("splitting by S\n"); 
	    if (!split_flag) {
	        token = strtok(cigar, "S");
		split_flag=1;
		sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 83);
	    } else {
	        token = strtok(NULL, "S");
		sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 83);
	    }
	    printf("token: %s\n", token);
	} else if (cigar[cig_index] < 48 || cigar[cig_index] > 57){
	    printf("parsing error. Character in cigar string that is not a number, S or M.\n");
	}
    } 
    return 0;
}

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

    char scaffold[60];
    char read_start[60];
    char cigar[60];
    char read[120];
    char quality[120];

    FILE* file = fopen(fileName, "r"); 
    while (!feof(file)) {
	fscanf(file, "%s %s %s %s %s\n", &scaffold, &read_start, &cigar, &read, &quality);
	printf("size of read: %d\n", strlen(read));
        int read_len = strlen(read);
	int aligned_sites[read_len];
	//printf("cigar: %s\n", cigar);
	parse_cigar(cigar, aligned_sites);
	int i;
	for (i = 0; i < read_len; i++){
	    printf("%d", aligned_sites[i]);
	}	
	printf("\n");
/*	
	printf("scaffold: %s\n", scaffold);
	printf("read_start: %s\n", read_start);
	printf("cigar: %s\n", cigar);
	printf("read: %s\n", read);
	printf("quality: %s\n", quality);
*/
    }
    fclose(file);
    return 0;
}
