#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_site_matrix_row(long *site_matrix_row, int width, char base) {
  int con_count_index;
  printf("%c: [", base);
  for (con_count_index = 0; con_count_index < width; con_count_index++){
      printf(" %ld ", site_matrix_row[con_count_index]);
  }
  printf("]\n");
}


void print_site_matrix (long *consensus_count_a,
                     long *consensus_count_t,
                     long *consensus_count_c,
                     long *consensus_count_g,
                     int width){
  print_site_matrix_row(consensus_count_a, width, 'A');
  print_site_matrix_row(consensus_count_t, width, 'T');
  print_site_matrix_row(consensus_count_c, width, 'C');
  print_site_matrix_row(consensus_count_g, width, 'G');
}

void print_consensus(long *consensus_count_a,
                     long *consensus_count_t,
                     long *consensus_count_c,
                     long *consensus_count_g,
                     int width) {
  int site_index;
  for (site_index = 0; site_index < width; site_index++) {
    const int aCount = consensus_count_a[site_index];
    const int tCount = consensus_count_t[site_index];
    const int cCount = consensus_count_c[site_index];
    const int gCount = consensus_count_g[site_index];
    if (aCount > tCount && aCount > cCount && aCount > gCount) {
      printf("A");
    } else if (tCount > aCount && tCount > cCount && tCount > gCount) {
      printf("T");
    } else if (cCount > aCount && cCount > tCount && cCount > gCount) {
      printf("C");
    } else if (gCount > aCount && gCount > tCount && gCount > cCount) {
      printf("G");
    } else if (aCount == 0 && tCount == 0 && cCount == 0 && gCount == 0) {
      printf(" ");
      //exit(1);
    } else {
      printf("?");
    }
  }
  printf("\n");
}

int main(int argc, char* argv[])
{
    char const* const file_name = argv[1]; 
    if (file_name == 0) {
      printf("A file must be passed into this program\n");
      return 0;
    }
    char const* const widthString = argv[2];
    if (widthString == 0) {
      printf("A width must be passed into this program\n");
      return 0;
    }
    long width = strtol(widthString, NULL, 10);
    long consensus_count_a[width];
    long consensus_count_t[width];
    long consensus_count_c[width];
    long consensus_count_g[width];
    int con_count_index = 0;
    for (con_count_index = 0; con_count_index < width; con_count_index++) {
      consensus_count_a[con_count_index] = 0;
      consensus_count_t[con_count_index] = 0;
      consensus_count_c[con_count_index] = 0;
      consensus_count_g[con_count_index] = 0;
    }
    
    char read[width+1];
    FILE* file = fopen(file_name, "r"); 
    while (!feof(file)) {
  	  int numberOfItemsMatched = fscanf(file, "%[^\n]%*c", read);
      //int numberOfItemsMatched = fscanf(file, "%s\r", read);
      //printf("%s\n", read);
      int site_index = 0;
      while(read[site_index] != '\0') {
        char site = read[site_index];
        //printf("%d\n", site);
        if (site == 'A' || site == 'a') {
          consensus_count_a[site_index]++;
        } else if (site == 'T' || site == 't'){
          consensus_count_t[site_index]++;
        } else if (site == 'C' || site == 'c') {
          consensus_count_c[site_index]++;
        } else if (site == 'G' || site == 'g') {
          consensus_count_g[site_index]++;
        } else if (site == ' ') {
          // Do nothing
        } else {
          printf("We saw an unexpected character: '%c' %d", site, site);
          exit(1);
        }
        site_index++;
      }
    }

    //printf("%ld\n", consensus_count_g[0]);
    //printf("%ld\n", consensus_count_t[1]);
    //printf("%ld\n", consensus_count_qt[2]);
    print_consensus(consensus_count_a, consensus_count_t, consensus_count_c, consensus_count_g, width);
    //print_site_matrix(consensus_count_a, consensus_count_t, consensus_count_c, consensus_count_g, width);
    return 0;
}
