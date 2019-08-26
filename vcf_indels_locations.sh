#Author: Kassandra Dickson
#Date: June 2019
##############
#### This script takes out the first two columns of the .vcf file : scaffold number and the location of the indel
##############


#!/bin/bash

argc=$#
requiredArgc=1

if [ $argc -ne $requiredArgc ]; then
	echo "./program.sh <strainNumber>"
	exit 1
fi

strainNumber=$1


function indelLocation {

bcftools query -f '%CHROM %POS \n' Ar${strainNumber}_ctq_reads_indels.vcf > Ar${strainNumber}_indel_locations.csv

}

#Main
indelLocation
