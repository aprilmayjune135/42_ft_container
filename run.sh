#setting

if [ "$1" == "fsanitize" ]; then
	make fsanitize
	./fsanitize.out
elif [ "$1" == "catch" ]; then
	make catch
	./catch.out
else
	make
	./a.out
fi
