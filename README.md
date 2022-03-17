![alt text](https://user-images.githubusercontent.com/73280726/158817986-10e63539-900c-4e18-994b-8086d9ab54eb.png)
# ft_container
This school project re-implements following C++ STL containers:
* vector<br />
* map<br />
* stack<br />
* set<br />

## Features
* This project is written in `C++98` (based on school requirement).
* The namespace is `ft` and all containers are tested using `ft::<container>` as opposed to `std::<container>`.
* For each container, all public member functions from C++98 version are re-implemented. Iterators are also re-implemented.
* Both `AVL-Tree` and `Red-Black-Tree` are implemented for `map` and `set`.

## Usage
This program is composed of tests for every public member function for each container. Output is printed out to a log file. Test for each container is timed by a timer to indicate calculation efficiency. <br />

`./run.sh [OPTION]`<br />
`OPTION = "EXTREME" | "CATCH"`<br />

* Without any option: the test runs first for `ft::<container>`, output to `ft.log`; then runs exactly the same way for `std::<container>`, output to `std.log`. At the end, two log files will be compared to indicate difference.
* `EXTREME`: container size up to 100,000 ~ 1 million will be tested in this option.
* `CATCH`: exceptions (from vector) will be tested under this option using `CATCH2` framework
