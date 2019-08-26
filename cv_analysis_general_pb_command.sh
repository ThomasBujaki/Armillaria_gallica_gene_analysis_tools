# read in parameters as they are passed in then mix them togeather as the program parses them, stick all of them togeather at the end and run the analysis

no_parameters () {
	#check if the number of parameters entered is correct
	echo "no parameters entered. Printing help statement." 
	pb_help
}

pb_help () {
	echo "See phylobayes 4.1 manual for detailed explanations
General phylobayes analysis look like:
	pb -d <data_file> -options output_base_file_name

Pass options in to this program as listed below:

The phyloBayes analysis options implemented in this program are:
General options (any combination allowed except -t and -T):
	-d <data_file> *required*
	-dc (removes constant sites)
	-t <tree_file> (chain starts at a specified tree, t)
	-T <tree_tile> (chain runs unter topology T)
	-r <outgroup> (roots tree with specified outgroup)
	-s (saves extra parameters for more detailed analyses)
	-f (forces overwrite of exitsting chain file of the same name)
	-x <every> [<until>] (frequency of chain saving)
Prior on branch lengths (only 1):
	-lexp (sets prior on branch lengths to be a product of i.i.d. exponential distributions)
	-lgam (sets prior on branch lengths to be a product of i.i.d. gamma distributions)
	-meanlength <meanlength> (fixes mean of the distributions to the specified value)
Rates across sites (only 1):
	-dgam <n> (specifies n catagoties for the descrete gamma distribution)
	-uni (uniform-rate across site (same as -dgam 1))
	-cgam (uses a continuous gamma distribution rather than a descrete one)
	-ratecat (inferres the distribution of rates across sites non-parametrically)
Relative exchangeabilites (only 1):
	-poi (sets exchangeability rates to 1, F81 model)
	-lg, -wag, -jtt, -mtrev, -mtzoa, -mtart
	-gtr 
	-rr <filename> (specifies exchangeabilites via a file, see manual for how to create the file)
Profile mixture (only 1):
	-dp or -cat (equilibrium frequencies inferred non-parametrically)
	-ncat <n> (a finite mixutre model with n allowed components)
	-catfix <predef> (specifies pre-defines profiles, C20, C30, C40, C50, C60, WLSR5)
	-catfix <filename> (spefies pre-defines profiles from a file)
sections not implemented:
	Matrix miture models (5.1.7)
	Heterotachy (5.1.8)
	Relaxed clock models (5.1.9)
	Prior on divergence times (5.1.10)
Data recoding (only 1):
	-recode <recoding_scheme> (uses one of three, dayhoff6, dayhoff4 or hp) recoding schemes)
	-recode <filename> (uses the recoding schemes found in a file)
Base file name:
	-out <base_file_name>"
	exit 1;
}

parse_parameters () {
	#parse the parameters for illegal entries and create the string that will run the program
	if [ "$1" == "-out" ] ; then
		base_name=$2
		return
	fi	
	parse_general $1 $2 $3 $parameters $base_name
	parse_branch_lengths $1 $2 $parameters $base_name
	parse_rates_over_sites
	parse_exchangeabilites
	parse_mixtures
	parse_data_recoding

}

parse_general () {
	if [ "$1" == "-d" ] ; then
		parameters="$parameters $1 $2"
		shift
		return
	elif [ "$1" == "-dc" ] ; then
		parameters="$parameters $1"
		return
	elif [ "$1" == "-t" -a $parameters != *"-T"*  ] ; then
		parameters="$parameters $1"
		return
	elif [ "$1" == "-T" -a $parameters != *"-t"*  ] ; then
		parameters="$parameters $1"
		return
	elif [ "$1" == "-r"  ] ; then
		parameters="$parameters $1 $2"
		shift
		return
	elif [ "$1" == "-s"  ] ; then
		parameters="$parameters $1"
		return	
	elif [ "$1" == "-f"  ] ; then
		parameters="$parameters $1"
		return
	elif [ "$1" == "-x"  ] ; then
		if [ "$3" != *"-"* ] ; then
			parameters="$parameters $1 $2 $3"
			shift
			shift
		else
			parameters="$parameters $1 $2"
			shift
		fi
		return
	fi
}

parse_branch_lengths () {
	branch_length_conflict $1 $parameters
	if [ "$1" == "-lexp" ] ; then
		parameters="$parameters $1"
		return
	elif [ "$1" == "-lgam" ] ; then
		parameters="$parameters $1"
		return
	elif [ "$1" == "-meanlength" ] ; then
		if [ "$2" == *"-"* ] ; then
			echo "Error, meanlength option invoked but no meanlength given. -meanlength <meanlength>"
			exit 1
		else
			parameters="$parameters $1 $2"
			shift
			return
		fi
	fi 
}

branch_length_conflict () {
	echo $1 $parameters
	if [ "$1" == "-lexp" -a "$parameters" == *"-lgam"* ] ; then
		echo "Error -lexp invoked but -lgam already included, only one branch length prior parameter is allowed. Exiting."
		exit 1
	elif [ "$1" == "-lexp" -a "$parameters" == *"-meanlength"* ] ; then
		echo "Error -lexp invoked but -meanlength already included, only one branch length prior parameter is allowed. Exiting."
		exit 1
	elif [ "$1" == "-lgam" -a "$parameters" == *"-lexp"* ] ; then
		echo "Error -lgam invoked but -lexp already included, only one branch length prior parameter is allowed. Exiting."
		exit 1
	elif [ "$1" == "-lgam" -a "$parameters" == *"-meanlength"* ] ; then
		echo "Error -lgam invoked but -meanlength already included, only one branch length prior parameter is allowed. Exiting."
		exit 1
	elif [ "$1" == "-meanlength" -a "$parameters" == *"-lexp"* ] ; then
		echo "Error -meanlength invoked but -lexp already included, only one branch length prior parameter is allowed. Exiting."
		exit 1
	elif [ "$1" == "-meanlength" -a "$parameters" == *"-lgam"* ] ; then
		echo "Error -meanlength invoked but -lgam already included, only one branch length prior parameter is allowed. Exiting."
		exit 1
	fi
}

parse_rates_over_sites () {
	echo rates across sites
}

parse_exchangeabilites () {
	echo parse_exchangeabilites
}

parse_mixtures () {
	echo parse_frequencies
}

parse_data_recoding () {
	echo data recoding
}

run_pb () {
	echo pb $parameters $base_name 
}

base_name=""
parameters=""

arguments_count=$#
if [ $arguments_count == 0 ]; then
	no_parameters
fi

while (( "$#" )); do
	parse_parameters $1 $2 $3 $parameters $base_name
	shift
done
run_pb $parameters $base_name
