%: %.cpp
	c++ -Wall -Wextra -Wshadow -Wno-unused-result -Wno-unused-value -std=c++17 -O4 -s -g -ggdb $^ -lm -lglog -o $@

