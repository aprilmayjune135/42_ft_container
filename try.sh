# Abort the script at the first error
set -e

rm -f ./try.out
clang++ -std=c++17 -Wall -Wextra -Werror -pedantic -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-unused-local-typedef tryBST.cpp -o try.out
./try.out