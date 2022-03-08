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

rm -rf *.log

if [ "$1" == "fsanitize" ]; then
	make fsanitize
	./fsanitize.out
elif [ "$1" == "catch" ]; then
	make catch
	./catch.out
else
	# run ft program
	make
	echo $MAGENTA_BOLD">> Executing ft.out..."$RESET_COLOR
	START_TIME_FT=$(date +%s)
	./ft.out
	END_TIME_FT=$(date +%s)
	TIME_FT=$(($END_TIME_FT - $START_TIME_FT))
	echo $MAGENTA_BOLD">> Output saved on ft_log.txt..."$RESET_COLOR
	
	# run std program
	make standard
	echo $MAGENTA_BOLD">> Executing std.out..."$RESET_COLOR
	START_TIME_STD=$(date +%s)
	./std.out
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
