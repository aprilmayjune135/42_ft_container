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
	make
	echo $MAGENTA_BOLD"Executing ft.out..."$RESET_COLOR
	./ft.out
	echo $MAGENTA_BOLD"Output saved on ft_log.txt..."$RESET_COLOR
	make standard
	echo $MAGENTA_BOLD"Executing std.out..."$RESET_COLOR
	./std.out
	echo $MAGENTA_BOLD"Output saved on std_log.txt..."$RESET_COLOR
	echo "\n"$MAGENTA_BOLD"Comparing output..."$RESET_COLOR
	if diff -q ./ft.log ./std.log > /dev/null
	then
		echo $GREEN_BOLD"The files are equal!"$RESET_COLOR
	else
		echo $RED_BOLD"The files are not equal!"$RESET_COLOR
		diff ./ft.log ./std.log > diff.log
	fi
fi
