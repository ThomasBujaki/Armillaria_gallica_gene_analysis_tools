#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program does not handle insertions or deletions the way it should. 
Currently it does not provide a offset if there is a deletion it just assumes
that the location the read is found in is correct. It would be very difficult to manage
insertions sa that would require a offsetting of all other reads by the size of that
insertion. Currently it assumes that indels are infrequent enough to not be have
a major effect on the file output.

Also I treat H in cigar strings the same way I do S*/

int fill_aligned_sites(char *token, int *aligned_sites, int  sum_len, int m_or_s) {
    int token_iter = 0;
    int strtol_val = strtol(token, &token, 10);
    for (token_iter = sum_len; token_iter < (strtol_val + sum_len); token_iter++) {
    if (m_or_s == 'M') {
        aligned_sites[token_iter] = 1;
    } else if (m_or_s == 'S') {
        aligned_sites[token_iter] = 0;
    }
    }
    sum_len = token_iter;
    return sum_len;
}

int parse_cigar(char *cigar, int *aligned_sites) {
    int cig_len = strlen(cigar);
    char *token;
    int sum_len = 0;
    int cig_index = 1;
    int split_flag = 0;
    for (cig_index = 0; cig_index < cig_len; cig_index++) {
        if (cigar[cig_index] == 'M') {
            if (!split_flag) {
                token = strtok(cigar, "M");
            split_flag = 1;
            sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 'M');
            } else {
                token = strtok(NULL, "M");
                sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 'M');
            }
        } else if (cigar[cig_index] == 'S') {
            if (!split_flag) {
                token = strtok(cigar, "S");
                split_flag = 1;
                sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 'S');
            } else {
                token = strtok(NULL, "S");
                sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 'S');
            }
        } else if (cigar[cig_index] == 'I') {
            if (!split_flag) {
                token = strtok(cigar, "I");
                split_flag = 1;
                sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 'M');
            } else {
                token = strtok(NULL, "I");
                sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 'M');
            }
        } else if (cigar[cig_index] == 'D') { 
            if (!split_flag) {
                token = strtok(cigar, "D");
                split_flag = 1;
                //printf("D: %s\n", token);
            } else {
                token = strtok(NULL, "D");
                //printf("D: %s\n", token);
            }
        } else if (cigar[cig_index] == 'H') {
            if (!split_flag) {
                token = strtok(cigar, "H");
                split_flag = 1;
                //sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 'S');
            } else {
                token = strtok(NULL, "H");
                //sum_len = fill_aligned_sites(token, aligned_sites, sum_len, 'S');
            }
        } else if (cigar[cig_index] < 48 || cigar[cig_index] > 57) {
            printf("parsing error. Character in cigar string that is not a number, S, I, D or M.\n");
            printf("character found: %c\n", cigar[cig_index]);
            return 0;
        }
    }
    return 0;
}

int cut_read_before_range(int *aligned_sites, int arr_len, int read_start, int range_start) {
    int index;
    for (index = 0; index < arr_len; index++) {
        if (read_start + index < range_start) {
            aligned_sites[index] = 0;
        }
    }
    return 0;
}

int cut_read_after_range(int *aligned_sites, int arr_len, int read_start, int range_end) {
    int index;
    for (index = 0; index < arr_len; index++) {
        if (read_start + index > range_end) {
            aligned_sites[index] = 0;
        }
    }
    return 0;
}

int find_start_index(int *aligned_sites, int arr_len) {
    int index;
    for (index = 0; index < arr_len; index++) {
        if (aligned_sites[index] == 1) {
            return index;
        }
    }
    return -1;
}
int find_end_index(int *aligned_sites, int arr_len) {
    int index;
    for (index = arr_len - 1; index >= 0; index--) {
        if (aligned_sites[index] == 1) {
            return index;
        }
    }
    return -1;
}

void print_target_substring(char *read, int *aligned_sites, int arr_len, int indent_level) {
    int index;
    for (index = 0; index < indent_level; index++) {
        printf(" ");
    }
    for (index = 0; index < arr_len; index++) {
        if (aligned_sites[index] == 1) {
                printf("%c", read[index]);
        }
    }
    printf("\n");
}

/*void manage_clipping(){

}*/

int main(int argc, char* argv[])
{
    char const* const fileName = argv[1];
    if (argv[1] == 0) {
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
    char read[150];
    char quality[150];

    int previous_indent = 0;

    FILE* file = fopen(fileName, "r");
    while (!feof(file)) {
        fscanf(file, "%s %s %s %s %s\n", scaffold, read_start, cigar, read, quality);
        int read_len = strlen(read);
        int aligned_sites[read_len];
	    parse_cigar(cigar, aligned_sites);
        cut_read_before_range(aligned_sites, read_len, atoi(read_start), start_position);
        cut_read_after_range(aligned_sites, read_len, atoi(read_start), end_position);
        int start_index = find_start_index(aligned_sites, read_len);
        int end_index = find_end_index(aligned_sites, read_len);
//	int indent_level = find_indent_level(read_start);
//	printf("start index: %d\t end index %d\n", start_index, end_index);
//	printf("cigar %s, %c\n", cigar, read[end_index]);
        int indent_level = atoi(read_start )- start_position > 0 ? atoi(read_start) - start_position : 0 ;
        print_target_substring(read, aligned_sites, read_len, indent_level);
/*	int i;
	for (i = 0; i < read_len; i++){
	    printf("%c", read[i]);
	}	
	printf("\n");
	for (i = 0; i < read_len; i++){
	    printf("%d", aligned_sites[i]);
	}	
	printf("\n"); */
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
