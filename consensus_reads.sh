# this program will take in a bam file, and a region which the reads will be taken from.

reads_start=$1
reads_end=$2
scaffold_num=$3
bam_file=$4

samtools view -o temp ${bam_file}  scaffold_${scaffold_num}:${reads_start}-${reads_end}
awk '{print $3,$4,$6,$10,$11}' temp > temp2



