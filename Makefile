std = c++17

# debug by default
ifeq ($(release),1)
	dbg_flags = -O3
else ifeq ($(release), 2)
	dbg_flags = -O3 -pg
else
	dbg_flags = -g -ggdb -rdynamic -D_GLIBCXX_CONCEPT_CHECKS -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL
endif


%: %.cpp
	g++ -Wall -Wextra -Wshadow -Wfatal-errors -std=$(std) $(dbg_flags) $^ -lm -o $@

