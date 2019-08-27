#!/bin/bash

###################################################################################################
# This script uses
###################################################################################################

argc=$#
requiredArgc=4

if [ $argc -ne $requiredArgc ]; then
	echo "./fastqThroughNovoalign.sh <reads1> <reads2> <refFastaFile> <outputBaseName>"
	exit 1
fi

reads1=$1
reads2=$2
refFile=$3
baseName=$4
path=$(pwd)

function Novoindex	{
	if [ -e $refFile.nci ]; then
		echo "Reference file already indexed."
	else
		echo "Indexing reference..."
		${path}/lab4Programs/novoindex $refFile.nci $refFile
		echo "Done indexing."
	fi
}

function Novoalign	{
	echo "Calling novoalign..."
	${path}/lab4Programs/novoalign -f $reads1 $reads2 -d $refFile.nci -o SAM > $baseName.sam
	echo "Done aligning."
}

function SamToBam	{
	echo "Converting sam to bam..."
	${path}/lab4Programs/samtools-0.1.10 view -b -h -S $baseName.sam -o $baseName.bam
	echo "Done converting sam to bam."
}

function SortBam	{
	echo "Sorting bam..."
	${path}/lab4Programs/samtools-0.1.10 sort $baseName.bam $baseName.sorted
	echo "Done sorting bam."
}

function IndexBam	{
	echo "Indexing sorted bam..."
	${path}/lab4Programs/samtools-0.1.10 index $baseName.sorted.bam
	echo "Done indexing sorted bam."
}

function CleanUp	{
	echo "Cleaning up..."
	rm -f $baseName.sam
	rm -f $baseName.bam
	echo "Done cleaning up."	
}

# Main
Novoindex
Novoalign
SamToBam
SortBam
IndexBam
CleanUp
