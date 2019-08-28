for i in Ar119 Ar142 Ar159 Ar170 Ar174 Ar175 Ar176 Ar179 Ar188 Ar194 ; do #Ar196 Ar201 Ar213 Ar73 ; do
    for j in {1..319} ; do 
        grep -P "scaffold_${j} [0-9]" ../read_depth_compair/Ar109_vs_${i}_no0 > temp
        var1=$(awk '{print $9}' ../average_read_depths/Ar109_vs_${i}_scaffold_${j}_avg_read_depth | cut -d"," -f1)
        var2=$(awk '{print $4}' ../average_read_depths/Ar109_vs_${i}_scaffold_${j}_avg_read_depth | cut -d"," -f1)
        echo $i $j $var1 $var2
        ./find_high_read_depths.out temp $var1 $var2 >> ../read_depth_diffs/Ar109_vs_${i}_significant_read_depths_5xstdv
        rm temp
    done
done
