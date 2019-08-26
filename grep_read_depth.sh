#!/bin/bash
#################
####This script searches the .vcf file for the scaffold ID, location of the INDELs and the raw read depth associated with it
################

argc=$#
requiredArgc=1

if [ $argc -ne $requiredArgc ]; then
		echo "program.sh <strainNumber>"
			exit 1
	fi

strainNumber=$1

function grepDP {

cat Ar${strainNumber}_ctq_reads_indels.vcf | tr ';' '\n' | grep DP= >> Ar${strainNumber}_read_depth

}

function indelLocations {

awk '{print $1,$2}' Ar${strainNumber}_ctq_reads_indels.vcf >> Ar${strainNumber}_locations

sed "/^#/d" Ar${strainNumber}_locations >> Ar${strainNumber}_indelLocations

}

function putTogether {

pr -m -t Ar${strainNumber}_indelLocations Ar${strainNumber}_read_depth >> Ar${strainNumber}_DP_locations

}

#Main
grepDP
indelLocations
putTogether
