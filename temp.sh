# Abort the script at the first error
set -e

# Start
rm -rf *.log

if [ "$1" == "fsanitize" ]; then
	make fsanitize
	./fsanitize.out
else
	make
	./ft.out
fi
