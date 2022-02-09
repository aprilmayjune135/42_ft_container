#setting

rm -rf ./ft_log.txt ./std_log.txt

if [ "$1" == "fsanitize" ]; then
	make fsanitize
	./fsanitize.out
elif [ "$1" == "catch" ]; then
	make catch
	./catch.out
else
	#make
	#./ft.out
	make standard
	./std.out
fi
