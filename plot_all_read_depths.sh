#this program will generate a number of ggplot pdfs based on the locations indicated in the files present in the sites_ctj folder. These files indicate locations on the chromosomes that have extremely high read depth
sequence=$1
i=0;
while IFS='' read -r line || [[ -n "$line" ]]; do
    ./print_read_depth.out read_depth_${sequence}_ctq_reads.bam $line > ${i}_${sequence}
    $(pwd)/Rscript $(pwd)/plot_read_depth.R ${i}_${sequence} $line
    mv ${i}_${sequence}_read_depth.pdf read_depth_graphs/$sequence/
    rm ${i}_${sequence}
    i=$((i+1))
done < "../sites_stdev_significant/${sequence}_significant_read_depths_4xstdv"	
