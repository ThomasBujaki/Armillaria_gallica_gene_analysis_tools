for i in Ar109 Ar119 Ar142 Ar159 Ar170 Ar174 Ar175 Ar176 Ar179 Ar188 Ar194 Ar196 Ar201 Ar213 Ar73 ; do
    for j in {1..319} ; do 
        grep -P "scaffold_${j}\t[1-9]" ../read_depth_files/read_depth_${i}_ctq_reads.bam > temp
        var1=$(awk '{print $9}' ../average_read_depths/${i}_scaffold_${j}_avg_read_depth | cut -d"," -f1)
        var2=$(awk '{print $4}' ../average_read_depths/${i}_scaffold_${j}_avg_read_depth | cut -d"," -f1)
        echo $i $j $var1 $var2
        ./find_high_read_depths.out temp $var1 $var2 >> ../read_depth_files/${i}_significant_read_depths_4xstdv
        rm temp
    done
done
