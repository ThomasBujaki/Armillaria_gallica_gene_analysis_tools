#!/bin/bash
########
## This find the indels from a specific strain of Ar given the ctq_reads.bam file against the reference genome
#########


argc=$#
requiredArgc=1

if [ $argc -ne $requiredArgc ]; then
	        echo "program.sh <strainNumber>"
		        exit 1
	fi

strainNumber=$1

function mpileup {

samtools mpileup -d 250 -m 1 -E --BCF --output-tags DP,AD,ADF,SP -f Armga1_AssemblyScaffolds.fasta -o Ar${strainNumber}_ctq_reads_indels.bcf Ar${strainNumber}_ctq_reads.bam
}

function indexing {
bcftools index  Ar${strainNumber}_ctq_reads_indels.bcf
}

function call {
bcftools call --skip-variants snps --multiallelic-caller --variants-only  -O v Ar${strainNumber}_ctq_reads_indels.bcf -o Ar${strainNumber}_ctq_reads_indels.vcf
}

#Main
mpileup
indexing
call




