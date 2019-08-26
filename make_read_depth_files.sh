path=$1
bam_file=$2
/share/data/public/jm/samtools-1.3.1/samtools depth ${path}/$bam_file > /share/data/public/Directed_Studies_Summer_2019/Ar_strains_read_depth/read_depth_$bam_file
