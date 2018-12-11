std = c++11

ifeq ($(debug),1)
	dbg_flags = -g -ggdb
else
	dbg_flags = -O4 -s -g
endif


%: %.cpp
	c++ -Wall -Wextra -Wshadow -Wno-unused-result -Wno-unused-value -std=$(std) $(dbg_flags) $^ -lm -lglog -o $@

