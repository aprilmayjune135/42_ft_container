#setting

if [ "$1" == "fsanitize" ]; then
	make fsanitize
	EXECUTABLE=./fsanitize.out
elif [ "$1" == "catch" ]; then
	make catch
	EXECUTABLE=./catch.out
else
	make
	EXECUTABLE=./a.out
fi

$EXECUTABLE
