all: test_checkediterator

test_checkediterator : test_checkediterator.cpp checkediterator.hpp
	g++ -std=c++11 -g -O0 $< -o $@

