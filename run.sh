# Abort the script at the first error
set -e

# Color
RESET_COLOR='\033[0m'
BLACK_BOLD='\033[1;30m'
RED_BOLD='\033[1;31m'
GREEN_BOLD='\033[1;32m'
YELLOW_BOLD='\033[1;33m'
BLUE_BOLD='\033[1;34m'
MAGENTA_BOLD='\033[1;35m'
CYAN_BOLD='\033[1;36m'
WHITE_BOLD='\033[1;37m'
RESET_COLOR='\033[0m'
BLACK='\033[0;30m'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'

# Start
rm -rf *.log

if [ "$1" == "fsanitize" ]; then
	make fsanitize
	./fsanitize.out
elif [ "$1" == "catch" ]; then
	make catch
	./catch.out
else
	# define extreme or regular
	if [ "$1" == "extreme" ]; then
		MAKE_FT="make extreme"
		MAKE_STD="make standard_extreme"
		FT_OUT="./ft_extreme.out"
		STD_OUT="./std_extreme.out"
	else
		MAKE_FT="make"
		MAKE_STD="make standard"
		FT_OUT="./ft.out"
		STD_OUT="./std.out"
	fi

	# run ft program
	$MAKE_FT
	echo $MAGENTA_BOLD">> Executing ft program..."$RESET_COLOR
		if [ "$1" == "extreme" ]; then
			./script_helper/extreme_message.sh
		fi
		# calcualte time
		START_TIME_FT=$(date +%s)
		$FT_OUT
		END_TIME_FT=$(date +%s)
		TIME_FT=$(($END_TIME_FT - $START_TIME_FT))
	echo $MAGENTA_BOLD">> Output saved on ft_log.txt..."$RESET_COLOR
	
	# run std program
	$MAKE_STD
	echo $MAGENTA_BOLD">> Executing std program..."$RESET_COLOR
		if [ "$1" == "extreme" ]; then
			./script_helper/extreme_message.sh
		fi
		# calcualte time
		START_TIME_STD=$(date +%s)
		$STD_OUT
		END_TIME_STD=$(date +%s)
		TIME_STD=$(($END_TIME_STD - $START_TIME_STD))
	echo $MAGENTA_BOLD">> Output saved on std_log.txt..."$RESET_COLOR

	# check output
	echo "\n"$MAGENTA_BOLD">> Comparing output..."$RESET_COLOR
	if diff -q ./ft.log ./std.log > /dev/null
	then
		echo $GREEN_BOLD"✅ The files are equal!"$RESET_COLOR
	else
		echo $RED_BOLD"❌ The files are not equal!"$RESET_COLOR
		diff ./ft.log ./std.log > diff.log
	fi

	# check timing
	echo "\n"$MAGENTA_BOLD">> Comparing timing..."$RESET_COLOR
	echo $BLUE_BOLD"Elapsed time for ft.out is $WHITE_BOLD$TIME_FT$BLUE_BOLD seconds."
	echo $BLUE_BOLD"Elapsed time for std.out is $WHITE_BOLD$TIME_STD$BLUE_BOLD seconds."
		# if TIME_STD is 0 second, set it at 1 for next comparison step
		if [ $TIME_STD -eq 0 ]
		then
			TIME_MAX=1
		else
			TIME_MAX=$(($TIME_STD * 20))
		fi
	if [ $TIME_FT -le $TIME_MAX ]
	then
		echo $GREEN_BOLD"✅ Timing meets requirement!"$RESET_COLOR
	else
		echo $RED_BOLD"❌ Timing does NOT meet requirement!"$RESET_COLOR
	fi
fi
