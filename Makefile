%: %.cpp
	g++ -Wall -Wextra -Wshadow -Wno-unused-result -std=c++17 -O3 -s -lm -g -ggdb $^ -o $@

