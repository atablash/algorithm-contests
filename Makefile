%: %.cpp
	g++ -Wall -Wextra -Wshadow -Wno-unused-result -std=c++11 -O2 -s -lm $^ -o $@