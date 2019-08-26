#!/bin/bash

for ((i=0; i<319; i++)); do

	Rscript readdepth_vs_indel_his.R $i
done

