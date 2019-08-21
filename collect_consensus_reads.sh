high_read_depth_file=$1
bam_file=$2
while read p; do
  echo $p
  var=$(echo $p | awk '{print $2 - $1}')
  if [ "$var" -lt 100 ] ; then
    continue
  fi
  ./consensus_reads.sh $p $bam_file
done <$high_read_depth_file