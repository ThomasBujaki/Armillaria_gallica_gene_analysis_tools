# this program will take in a bam file, and a region which the reads will be taken from.

argc=$#
requiredArgc=4
path=$(pwd)
if [ $argc -ne $requiredArgc ]; then
        echo "./consensus_reads.sh <location_start> <location_end> <scaffold_number> <bam_file>"
        exit 1
fi


reads_start=$1
reads_end=$2
scaffold_num=$3
bam_file=$4
reads_diff=$(expr $reads_end - $reads_start + 1)
samtools view -o temp ${bam_file}  scaffold_${scaffold_num}:${reads_start}-${reads_end}
awk '{print $3,$4,$6,$10,$11}' temp > temp2
./a.out temp2 scaffold_${scaffold_num} ${reads_start} ${reads_end} > temp_reads
rm temp
rm temp2
./average_reads.out temp_reads $reads_diff
rm temp_reads

